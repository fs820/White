//----------------------------------------
//
//�|���S���\������[wall.cpp]
//Author fuma sato
//
//----------------------------------------

#include"wall.h"
#include"camera.h"
#include"player.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;//�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;
Wall g_aWall[WALL_MAX];

//----------------------
//�|���S���̏���������
//----------------------
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	VERTEX_3D* pVtx;//���_���|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		WALL_TEX,
		&g_pTextureWall
	);

	int nCntWall;
	for (nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].bAlpha = false;
		g_aWall[nCntWall].bUse = false;
	}
	//1��


	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < 2; nCntWall++)
	{
		//���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(-WALL_WIDTH * 0.5f, WALL_HEIGHT, WALL_Z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(WALL_WIDTH * 0.5f, WALL_HEIGHT, WALL_Z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(-WALL_WIDTH * 0.5f, 0.0f, -WALL_Z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(WALL_WIDTH * 0.5f, 0.0f, -WALL_Z * 0.5f);

		//nor
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - nCntWall * (1.0f - WALL_ALPHA));
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - nCntWall * (1.0f - WALL_ALPHA));
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - nCntWall * (1.0f - WALL_ALPHA));
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - nCntWall * (1.0f - WALL_ALPHA));

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(WALL_WIDTH/ WALL_WIDTH_DEF, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, WALL_HEIGHT / WALL_HEIGHT_DEF);
		pVtx[3].tex = D3DXVECTOR2(WALL_WIDTH / WALL_WIDTH_DEF, WALL_HEIGHT / WALL_HEIGHT_DEF);

		pVtx += VT_MAX;
	}

	g_pVtxBuffWall->Unlock();
}

//-------------------
//�|���S���I������
//-------------------
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateWall(void)
{
	//�����蔻��
	CollisionWall();
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntWall;
	for (nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse && !g_aWall[nCntWall].bAlpha)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//�ʒu�̌v�Z
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			//�|���S���̕`��
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				0,//�n�܂�̔ԍ�
				2//�|���S���̌�
			);
		}
	}
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawAlphaWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntWall;
	for (nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse && g_aWall[nCntWall].bAlpha)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//�ʒu�̌v�Z
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			//�|���S���̕`��
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				VT_MAX,//�n�܂�̔ԍ�
				2//�|���S���̌�
			);
		}
	}
}

//----------
//�ݒ�
//----------
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntWall;
	for (nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		if (!g_aWall[nCntWall].bUse)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].bAlpha = false;
			g_aWall[nCntWall].bUse = true;
			break;
		}
	}

	for (nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		if (!g_aWall[nCntWall].bUse)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].rot.y += D3DX_PI;
			//���K��
			if (g_aWall[nCntWall].rot.y > D3DX_PI)
			{
				g_aWall[nCntWall].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aWall[nCntWall].rot.y < -D3DX_PI)
			{
				g_aWall[nCntWall].rot.y += D3DX_PI * 2.0f;
			}
			g_aWall[nCntWall].bAlpha = true;
			g_aWall[nCntWall].bUse = true;
			break;
		}
	}
}

//-----------------
//���擾
//-----------------
Wall* GetWall(void)
{
	return &g_aWall[0];
}

//----------------------
//�����蔻��
//----------------------
void CollisionWall(void)
{
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3 aPos[2] = {}, Wallvec = {}, Posvec = {}, PosOldvec = {}, movevec = {}, Norvec = {}, Dovec = {}, Hit = {};
	int nCntWall;
	float WallCross, PosCross;
	for (nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{//�ǂ̐�
		if (g_aWall[nCntWall].bUse && !g_aWall[nCntWall].bAlpha)
		{//�g���Ă��铧���łȂ���
			aPos[0] = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH * 0.5f * sinf(g_aWall[nCntWall].rot.y + D3DX_PI * -0.5f), g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z + WALL_WIDTH * 0.5f * cosf(g_aWall[nCntWall].rot.y + D3DX_PI * -0.5f));
			aPos[1] = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH * 0.5f * sinf(g_aWall[nCntWall].rot.y + D3DX_PI * 0.5f), g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z + WALL_WIDTH * 0.5f * cosf(g_aWall[nCntWall].rot.y + D3DX_PI * 0.5f));
			Wallvec = aPos[1] - aPos[0];//�ǂ̃x�N�g��
			Posvec = pPlayer->pos - aPos[0];//�ǂɑ΂���v���C���[�̃x�N�g��
			PosOldvec = pPlayer->posOld - aPos[0];//�ǂɑ΂���v���C���[�̋��x�N�g��
			movevec = pPlayer->pos - pPlayer->posOld;//�v���C���[�̈ړ��x�N�g��
			if ((Wallvec.z * Posvec.x) - (Wallvec.x * Posvec.z) <= WALL_COLL_SPASE && (Wallvec.z * PosOldvec.x) - (Wallvec.x * PosOldvec.z) >= WALL_COLL_SPASE && pPlayer->pos.y < g_aWall[nCntWall].pos.y + WALL_HEIGHT && pPlayer->pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y > g_aWall[nCntWall].pos.y)
			{//�ǂ̊O��
				WallCross = (Wallvec.z * movevec.x) - (Wallvec.x * movevec.z);
				PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
				PosCross /= WallCross;
				if (PosCross >= -0.01f&& PosCross < 1.01f)
				{
					Hit = aPos[0] + Wallvec * PosCross;
					movevec = pPlayer->pos - Hit;//�v���C���[�̈ړ��x�N�g��
					Norvec = D3DXVECTOR3(Wallvec.z, Wallvec.y, -Wallvec.x);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
					pPlayer->pos += Dovec * 1.95f;
				}
			}
		}
	}
}