//----------------------------------------
//
//�|���S���\������[meshwall.cpp]
//Author fuma sato
//
//----------------------------------------

#include"meshwall.h"
#include"player.h"
#include"Dog.h"
#include"Crow.h"
#include"snowball.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;//�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;//�C���f�b�N�X�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;
MeshWall g_aMeshWall[MESHWALL_MAX];

//----------------------
//�|���S���̏���������
//----------------------
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	VERTEX_3D* pVtx;//���_���|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX_MESH_WALL * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		MESHWALL_TEX,
		&g_pTextureMeshWall
	);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * INDEX_NUM_WALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL
	);

	int nCntMeshWall, nCntMeshWall2, nCntMeshWall3;
	for (nCntMeshWall = 0; nCntMeshWall < MESHWALL_MAX; nCntMeshWall++)
	{
		g_aMeshWall[nCntMeshWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntMeshWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntMeshWall].bUse = false;
	}
	//1��


	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMeshWall = 0; nCntMeshWall < 2; nCntMeshWall++)
	{//���b�V���t�B�[���h��
		for (nCntMeshWall2 = 0; nCntMeshWall2 < MESHWALL_YNUM + 1; nCntMeshWall2++)
		{//1������Z���̃��[�v
			for (nCntMeshWall3 = 0; nCntMeshWall3 < MESHWALL_XNUM + 1; nCntMeshWall3++)
			{//1������X���̃��[�v
				//���W�ݒ�
				pVtx[nCntMeshWall2 * (MESHWALL_XNUM + 1) + nCntMeshWall3].pos = D3DXVECTOR3(-MESHWALL_WIDTH * 0.5f + (MESHWALL_WIDTH / MESHWALL_XNUM) * nCntMeshWall3, MESHWALL_HEIGHT - (MESHWALL_HEIGHT / MESHWALL_YNUM) * nCntMeshWall2, MESHWALL_Z);

				//nor
				pVtx[nCntMeshWall2 * (MESHWALL_XNUM + 1) + nCntMeshWall3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				//�J���[
				pVtx[nCntMeshWall2 * (MESHWALL_XNUM + 1) + nCntMeshWall3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f - WALL_ALPHA_MESH) * nCntMeshWall);

				//�e�N�X�`��
				pVtx[nCntMeshWall2 * (MESHWALL_XNUM + 1) + nCntMeshWall3].tex = D3DXVECTOR2(((MESHWALL_WIDTH / MESHWALL_WIDTH_DEF) / MESHWALL_XNUM) * nCntMeshWall3, ((MESHWALL_HEIGHT / MESHWALL_HEIGHT_DEF) / MESHWALL_YNUM) * nCntMeshWall2);
			}
		}
		pVtx += VT_MAX_MESH_WALL;
	}

	g_pVtxBuffMeshWall->Unlock();

	WORD* pIdx;
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntMeshWall = 0; nCntMeshWall < INDEX_NUM_WALL - (MESHWALL_YNUM - 1) * 2; nCntMeshWall++)
	{
		if (nCntMeshWall % ((MESHWALL_XNUM + 1) * 2) == 0 && nCntMeshWall != 0)
		{
			//�C���f�b�N�X�w��
			pIdx[nCntMeshWall - 2 + ((nCntMeshWall / ((MESHWALL_XNUM + 1) * 2)) * 2)] = (MESHWALL_XNUM + 1) - (MESHWALL_XNUM + 1) * ((nCntMeshWall - 1) % 2) + ((nCntMeshWall - 1) / 2);
			//�C���f�b�N�X�w��
			pIdx[nCntMeshWall - 1 + ((nCntMeshWall / ((MESHWALL_XNUM + 1) * 2)) * 2)] = (MESHWALL_XNUM + 1) - (MESHWALL_XNUM + 1) * (nCntMeshWall % 2) + (nCntMeshWall / 2);
		}

		//�C���f�b�N�X�w��
		pIdx[nCntMeshWall + ((nCntMeshWall / ((MESHWALL_XNUM + 1) * 2)) * 2)] = (MESHWALL_XNUM + 1) - (MESHWALL_XNUM + 1) * (nCntMeshWall % 2) + (nCntMeshWall / 2);
	}

	g_pIdxBuffMeshWall->Unlock();
}

//-------------------
//�|���S���I������
//-------------------
void UninitMeshWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateMeshWall(void)
{
	if (GetMode() == MODE_GAME)
	{
		CollisionMeshWall();
	}
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntMeshWall;
	for (nCntMeshWall = 0; nCntMeshWall < MESHWALL_MAX; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse && !g_aMeshWall[nCntMeshWall].bAlpha)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aMeshWall[nCntMeshWall].mtxWorld);

			//�傫���̔��f
			D3DXMatrixScaling(&mtxScale, g_aMeshWall[nCntMeshWall].scale.x, g_aMeshWall[nCntMeshWall].scale.y, g_aMeshWall[nCntMeshWall].scale.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorld, &g_aMeshWall[nCntMeshWall].mtxWorld, &mtxScale);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshWall[nCntMeshWall].rot.y, g_aMeshWall[nCntMeshWall].rot.x, g_aMeshWall[nCntMeshWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorld, &g_aMeshWall[nCntMeshWall].mtxWorld, &mtxRot);

			//�ʒu�̌v�Z
			D3DXMatrixTranslation(&mtxTrans, g_aMeshWall[nCntMeshWall].pos.x, g_aMeshWall[nCntMeshWall].pos.y, g_aMeshWall[nCntMeshWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorld, &g_aMeshWall[nCntMeshWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntMeshWall].mtxWorld);

			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshWall);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				0,
				0,
				VT_MAX_MESH_WALL,//���_��
				0,
				POLYGON_NUM_WALL//�|���S���̌�
			);
		}
	}
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawAlphaMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntMeshWall;
	for (nCntMeshWall = 0; nCntMeshWall < MESHWALL_MAX; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse && g_aMeshWall[nCntMeshWall].bAlpha)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aMeshWall[nCntMeshWall].mtxWorld);

			//�傫���̔��f
			D3DXMatrixScaling(&mtxScale, g_aMeshWall[nCntMeshWall].scale.x, g_aMeshWall[nCntMeshWall].scale.y, g_aMeshWall[nCntMeshWall].scale.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorld, &g_aMeshWall[nCntMeshWall].mtxWorld, &mtxScale);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshWall[nCntMeshWall].rot.y, g_aMeshWall[nCntMeshWall].rot.x, g_aMeshWall[nCntMeshWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorld, &g_aMeshWall[nCntMeshWall].mtxWorld, &mtxRot);

			//�ʒu�̌v�Z
			D3DXMatrixTranslation(&mtxTrans, g_aMeshWall[nCntMeshWall].pos.x, g_aMeshWall[nCntMeshWall].pos.y, g_aMeshWall[nCntMeshWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorld, &g_aMeshWall[nCntMeshWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntMeshWall].mtxWorld);

			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshWall);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				VT_MAX_MESH_WALL,
				0,
				VT_MAX_MESH_WALL,//���_��
				0,
				POLYGON_NUM_WALL//�|���S���̌�
			);
		}
	}
}

//----------
//�ݒ�
//----------
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	int nCntMeshWall;
	for (nCntMeshWall = 0; nCntMeshWall < MESHWALL_MAX; nCntMeshWall++)
	{
		if (!g_aMeshWall[nCntMeshWall].bUse)
		{
			g_aMeshWall[nCntMeshWall].pos = pos;
			g_aMeshWall[nCntMeshWall].rot = rot;
			g_aMeshWall[nCntMeshWall].scale = scale;

			g_aMeshWall[nCntMeshWall].bAlpha = false;
			g_aMeshWall[nCntMeshWall].bUse = true;
			break;
		}
	}

	for (nCntMeshWall = 0; nCntMeshWall < MESHWALL_MAX; nCntMeshWall++)
	{
		if (!g_aMeshWall[nCntMeshWall].bUse)
		{
			g_aMeshWall[nCntMeshWall].pos = pos;
			g_aMeshWall[nCntMeshWall].rot = rot;
			g_aMeshWall[nCntMeshWall].rot.y += D3DX_PI;
			//���K��
			if (g_aMeshWall[nCntMeshWall].rot.y > D3DX_PI)
			{
				g_aMeshWall[nCntMeshWall].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aMeshWall[nCntMeshWall].rot.y < -D3DX_PI)
			{
				g_aMeshWall[nCntMeshWall].rot.y += D3DX_PI * 2.0f;
			}
			g_aMeshWall[nCntMeshWall].scale = scale;
			g_aMeshWall[nCntMeshWall].bAlpha = true;
			g_aMeshWall[nCntMeshWall].bUse = true;
			break;
		}
	}
}

//--------------------------
//���擾
//--------------------------
MeshWall* GetMeshWall(void)
{
	return &g_aMeshWall[0];
}

//----------------------
//�����蔻��
//----------------------
void CollisionMeshWall(void)
{
	Player* pPlayer = GetPlayer();
	Dog* pDog = GetDog();
	Crow* pCrow = GetCrow();
	SnowBall* pSnowBall = GetSnowBall();
	D3DXVECTOR3 aPos[2] = {}, Wallvec = {}, Posvec = {}, PosOldvec = {}, movevec = {}, Norvec = {}, Dovec = {}, Hit = {};
	int nCntWall;
	float WallCross, PosCross;
	for (nCntWall = 0; nCntWall < MESHWALL_MAX; nCntWall++)
	{//�ǂ̐�
		if (g_aMeshWall[nCntWall].bUse && !g_aMeshWall[nCntWall].bAlpha)
		{//�g���Ă��铧���łȂ���
			aPos[0] = D3DXVECTOR3(g_aMeshWall[nCntWall].pos.x + MESHWALL_WIDTH * 0.5f * g_aMeshWall[nCntWall].scale.x * sinf(g_aMeshWall[nCntWall].rot.y + D3DX_PI * -0.5f), g_aMeshWall[nCntWall].pos.y, g_aMeshWall[nCntWall].pos.z + MESHWALL_WIDTH * 0.5f * g_aMeshWall[nCntWall].scale.z * cosf(g_aMeshWall[nCntWall].rot.y + D3DX_PI * -0.5f));
			aPos[1] = D3DXVECTOR3(g_aMeshWall[nCntWall].pos.x + MESHWALL_WIDTH * 0.5f * g_aMeshWall[nCntWall].scale.x * sinf(g_aMeshWall[nCntWall].rot.y + D3DX_PI * 0.5f), g_aMeshWall[nCntWall].pos.y, g_aMeshWall[nCntWall].pos.z + MESHWALL_WIDTH * 0.5f * g_aMeshWall[nCntWall].scale.z * cosf(g_aMeshWall[nCntWall].rot.y + D3DX_PI * 0.5f));

			Wallvec = aPos[1] - aPos[0];//�ǂ̃x�N�g��
			Posvec = pPlayer->pos - aPos[0];//�ǂɑ΂���v���C���[�̃x�N�g��
			PosOldvec = pPlayer->posOld - aPos[0];//�ǂɑ΂���v���C���[�̋��x�N�g��
			movevec = pPlayer->pos - pPlayer->posOld;//�v���C���[�̈ړ��x�N�g��
			if ((Wallvec.z * Posvec.x) - (Wallvec.x * Posvec.z) <= 0.0f && (Wallvec.z * PosOldvec.x) - (Wallvec.x * PosOldvec.z) >= 0.0f && pPlayer->pos.y < g_aMeshWall[nCntWall].pos.y + MESHWALL_HEIGHT * g_aMeshWall[nCntWall].scale.y && pPlayer->pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y > g_aMeshWall[nCntWall].pos.y)
			{//�ǂ̊O��
				WallCross = (Wallvec.z * movevec.x) - (Wallvec.x * movevec.z);
				PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
				PosCross /= WallCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[0] + Wallvec * PosCross;
					movevec = pPlayer->pos - Hit;//�v���C���[�̈ړ��x�N�g��
					Norvec = D3DXVECTOR3(Wallvec.z, Wallvec.y, -Wallvec.x);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
					pPlayer->pos += Dovec * 1.1f;
				}
			}

			pDog = GetDog();
			for (int nCntDog = 0; nCntDog < MAX_DOG; nCntDog++, pDog++)
			{
				if (pDog->bUse)
				{
					Wallvec = aPos[1] - aPos[0];//�ǂ̃x�N�g��
					Posvec = pDog->pos - aPos[0];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = pDog->posOld - aPos[0];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pDog->pos - pDog->posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Wallvec.z * Posvec.x) - (Wallvec.x * Posvec.z) <= 0.0f && (Wallvec.z * PosOldvec.x) - (Wallvec.x * PosOldvec.z) >= 0.0f && pDog->pos.y < g_aMeshWall[nCntWall].pos.y + MESHWALL_HEIGHT * g_aMeshWall[nCntWall].scale.y && pDog->pos.y + pDog->aModel[1].pos.y + pDog->aModel[1].vtxMax.y > g_aMeshWall[nCntWall].pos.y)
					{//�ǂ̊O��
						WallCross = (Wallvec.z * movevec.x) - (Wallvec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= WallCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[0] + Wallvec * PosCross;
							movevec = pDog->pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Wallvec.z, Wallvec.y, -Wallvec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							pDog->pos += Dovec * 1.1f;
						}
					}
				}
			}

			pCrow = GetCrow();
			for (int nCntCrow = 0; nCntCrow < MAX_CROW; nCntCrow++, pCrow++)
			{
				if (pCrow->bUse)
				{
					Wallvec = aPos[1] - aPos[0];//�ǂ̃x�N�g��
					Posvec = pCrow->pos - aPos[0];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = pCrow->posOld - aPos[0];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pCrow->pos - pCrow->posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Wallvec.z * Posvec.x) - (Wallvec.x * Posvec.z) <= 0.0f && (Wallvec.z * PosOldvec.x) - (Wallvec.x * PosOldvec.z) >= 0.0f && pCrow->pos.y < g_aMeshWall[nCntWall].pos.y + MESHWALL_HEIGHT * g_aMeshWall[nCntWall].scale.y && pCrow->pos.y + pCrow->aModel[1].pos.y + pCrow->aModel[1].vtxMax.y > g_aMeshWall[nCntWall].pos.y)
					{//�ǂ̊O��
						WallCross = (Wallvec.z * movevec.x) - (Wallvec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= WallCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[0] + Wallvec * PosCross;
							movevec = pCrow->pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Wallvec.z, Wallvec.y, -Wallvec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							pCrow->pos += Dovec * 1.1f;
						}
					}
				}
			}

			pSnowBall = GetSnowBall();
			for (int nCntSnowBall = 0; nCntSnowBall < SNOWBALL_MAX; nCntSnowBall++, pSnowBall++)
			{
				if (pSnowBall->bUse)
				{
					D3DXVECTOR3 pos = pSnowBall->pos, posOld = pSnowBall->posOld;
					pos.y -= SNOWBALL_RADIUS * pSnowBall->scale.y;
					posOld.y -= SNOWBALL_RADIUS * pSnowBall->scale.y;

					Wallvec = aPos[1] - aPos[0];//�ǂ̃x�N�g��
					Posvec = pos - aPos[0];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec =posOld - aPos[0];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pos - posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Wallvec.z * Posvec.x) - (Wallvec.x * Posvec.z) <= 0.0f && (Wallvec.z * PosOldvec.x) - (Wallvec.x * PosOldvec.z) >= 0.0f && pCrow->pos.y < g_aMeshWall[nCntWall].pos.y + MESHWALL_HEIGHT * g_aMeshWall[nCntWall].scale.y && pCrow->pos.y > g_aMeshWall[nCntWall].pos.y)
					{//�ǂ̊O��
						WallCross = (Wallvec.z * movevec.x) - (Wallvec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= WallCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[0] + Wallvec * PosCross;
							movevec = pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Wallvec.z, Wallvec.y, -Wallvec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							pSnowBall->pos += Dovec * 1.1f;
						}
					}
				}
			}
		}
	}
}