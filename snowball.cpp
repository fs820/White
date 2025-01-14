//----------------------------------------
//
//�|���S���\������[snowball.cpp]
//Author fuma sato
//
//----------------------------------------

#include"snowball.h"
#include"hitshere.h"
#include"game.h"
#include"stage.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSnowBall = NULL;//�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSnowBall = NULL;//�C���f�b�N�X�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSnowBall[2] = { NULL };
SnowBall g_aSnowBall[SNOWBALL_MAX];

//----------------------
//�|���S���̏���������
//----------------------
void InitSnowBall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	VERTEX_3D* pVtx;//���_���|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX_SB,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSnowBall,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		SNOWBALL_TEX,
		&g_pTextureSnowBall[0]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		SNOWBALL_TEX2,
		&g_pTextureSnowBall[1]
	);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * INDEX_SB_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSnowBall,
		NULL
	);

	int nCntSnowBall, nCntSnowBall2;
	for (nCntSnowBall = 0; nCntSnowBall < SNOWBALL_MAX; nCntSnowBall++)
	{
		g_aSnowBall[nCntSnowBall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSnowBall[nCntSnowBall].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSnowBall[nCntSnowBall].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSnowBall[nCntSnowBall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSnowBall[nCntSnowBall].scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSnowBall[nCntSnowBall].bUse = false;
	}
	//1��

	g_pVtxBuffSnowBall->Lock(0, 0, (void**)&pVtx, 0);

	//�ɒ��_
	pVtx[0].pos = D3DXVECTOR3(0.0f, SNOWBALL_RADIUS, 0.0f);

	D3DXVECTOR3 npos = D3DXVECTOR3(0.0f, SNOWBALL_RADIUS, 0.0f), dpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	npos = npos - dpos;
	D3DXVec3Normalize(&npos, &npos);
	pVtx[0].nor = npos;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2((float)(((((SNOWBALL_RADIUS + SNOWBALL_RADIUS) * D3DX_PI) / SNOWBALL_WIDTH_DEF) / SNOWBALL_HNUM)), (float)((((SNOWBALL_RADIUS + SNOWBALL_RADIUS) * D3DX_PI * 0.5f) / SNOWBALL_HEIGHT_DEF) / SNOWBALL_VNUM));

	for (nCntSnowBall = 0; nCntSnowBall < SNOWBALL_VNUM - 1; nCntSnowBall++)
	{//1������Z���̃��[�v
		for (nCntSnowBall2 = 0; nCntSnowBall2 < SNOWBALL_HNUM + 1; nCntSnowBall2++)
		{//1������X���̃��[�v

			//�~�`�̊p�x
			float fangleH = (360.0f / SNOWBALL_HNUM) * nCntSnowBall2 * (D3DX_PI / 180.0f), fangleV = (SNOWBALL_ANG / SNOWBALL_VNUM) * (nCntSnowBall + 1) * (D3DX_PI / 180.0f);

			//���W�ݒ�
			pVtx[nCntSnowBall * (SNOWBALL_HNUM + 1) + nCntSnowBall2 + 1].pos = D3DXVECTOR3(sinf(fangleH) * sinf(fangleV) * SNOWBALL_RADIUS, cosf(fangleV) * SNOWBALL_RADIUS, cosf(fangleH) * sinf(fangleV) * SNOWBALL_RADIUS);

			//nor
			D3DXVECTOR3 npos = D3DXVECTOR3(sinf(fangleH) * sinf(fangleV) * SNOWBALL_RADIUS, cosf(fangleV) * SNOWBALL_RADIUS, cosf(fangleH) * sinf(fangleV) * SNOWBALL_RADIUS), dpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			npos = npos - dpos;
			D3DXVec3Normalize(&npos, &npos);
			pVtx[nCntSnowBall * (SNOWBALL_HNUM + 1) + nCntSnowBall2 + 1].nor = npos;

			//�J���[
			pVtx[nCntSnowBall * (SNOWBALL_HNUM + 1) + nCntSnowBall2 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`��
			pVtx[nCntSnowBall * (SNOWBALL_HNUM + 1) + nCntSnowBall2 + 1].tex = D3DXVECTOR2((float)(((((SNOWBALL_RADIUS + SNOWBALL_RADIUS) * D3DX_PI) / SNOWBALL_WIDTH_DEF) / SNOWBALL_HNUM) * nCntSnowBall2), (float)((((SNOWBALL_RADIUS + SNOWBALL_RADIUS) * D3DX_PI * 0.5f) / SNOWBALL_HEIGHT_DEF) / SNOWBALL_VNUM) * nCntSnowBall);
		}
	}

	//�ɒ��_
	pVtx[VT_MAX_SB - 1].pos = D3DXVECTOR3(0.0f, -SNOWBALL_RADIUS, 0.0f);

	npos = D3DXVECTOR3(0.0f, -SNOWBALL_RADIUS, 0.0f), dpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	npos = npos - dpos;
	D3DXVec3Normalize(&npos, &npos);
	pVtx[VT_MAX_SB - 1].nor = npos;

	pVtx[VT_MAX_SB - 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[VT_MAX_SB - 1].tex = D3DXVECTOR2((float)(((((SNOWBALL_RADIUS + SNOWBALL_RADIUS) * D3DX_PI) / SNOWBALL_WIDTH_DEF) / SNOWBALL_HNUM)), (float)((((SNOWBALL_RADIUS + SNOWBALL_RADIUS) * D3DX_PI * 0.5f) / SNOWBALL_HEIGHT_DEF) / SNOWBALL_VNUM));

	g_pVtxBuffSnowBall->Unlock();

	WORD* pIdx;
	int nIdx[INDEX_SB_NUM];
	g_pIdxBuffSnowBall->Lock(0, 0, (void**)&pIdx, 0);

	pIdx[0] = 0;
	nIdx[0] = 0;
	for (nCntSnowBall = 1; nCntSnowBall < SNOWBALL_HNUM + 2; nCntSnowBall++)
	{//FAN����
		pIdx[nCntSnowBall] = nCntSnowBall;
		nIdx[nCntSnowBall] = nCntSnowBall;
	}
	for (nCntSnowBall = SNOWBALL_HNUM + 2; nCntSnowBall < INDEX_SB_NUM - (SNOWBALL_VNUM - 2) * 2 - SNOWBALL_HNUM; nCntSnowBall++)
	{//SBRIP����
		if ((nCntSnowBall - (SNOWBALL_HNUM + 2)) % (((SNOWBALL_HNUM + 1) * 2)) == 0 && (nCntSnowBall - (SNOWBALL_HNUM + 2)) != 0)
		{//�k�ރ|���S��
			//�C���f�b�N�X�w��
			pIdx[nCntSnowBall - 2 + (((nCntSnowBall - (SNOWBALL_HNUM + 2)) / ((SNOWBALL_HNUM + 1) * 2)) * 2)] = (SNOWBALL_HNUM + 1) - (SNOWBALL_HNUM + 1) * (((nCntSnowBall - (SNOWBALL_HNUM + 2)) - 1) % 2) + (VT_MAX_SB - (SNOWBALL_HNUM + 3)) - (((nCntSnowBall - (SNOWBALL_HNUM + 2)) - 1) / 2);
			nIdx[nCntSnowBall - 2 + (((nCntSnowBall - (SNOWBALL_HNUM + 2)) / ((SNOWBALL_HNUM + 1) * 2)) * 2)] = (SNOWBALL_HNUM + 1) - (SNOWBALL_HNUM + 1) * (((nCntSnowBall - (SNOWBALL_HNUM + 2)) - 1) % 2) + (VT_MAX_SB - (SNOWBALL_HNUM + 3)) - (((nCntSnowBall - (SNOWBALL_HNUM + 2)) - 1) / 2);

			//�C���f�b�N�X�w��
			pIdx[nCntSnowBall - 1 + (((nCntSnowBall - (SNOWBALL_HNUM + 2)) / ((SNOWBALL_HNUM + 1) * 2)) * 2)] = (SNOWBALL_HNUM + 1) - (SNOWBALL_HNUM + 1) * ((nCntSnowBall - (SNOWBALL_HNUM + 2)) % 2) + (VT_MAX_SB - (SNOWBALL_HNUM + 3)) - ((nCntSnowBall - (SNOWBALL_HNUM + 2)) / 2);
			nIdx[nCntSnowBall - 1 + (((nCntSnowBall - (SNOWBALL_HNUM + 2)) / ((SNOWBALL_HNUM + 1) * 2)) * 2)] = (SNOWBALL_HNUM + 1) - (SNOWBALL_HNUM + 1) * ((nCntSnowBall - (SNOWBALL_HNUM + 2)) % 2) + (VT_MAX_SB - (SNOWBALL_HNUM + 3)) - ((nCntSnowBall - (SNOWBALL_HNUM + 2)) / 2);
		}

		//�C���f�b�N�X�w��
		pIdx[nCntSnowBall + (((nCntSnowBall - (SNOWBALL_HNUM + 2)) / ((SNOWBALL_HNUM + 1) * 2)) * 2)] = (SNOWBALL_HNUM + 1) - (SNOWBALL_HNUM + 1) * ((nCntSnowBall - (SNOWBALL_HNUM + 2)) % 2) + (VT_MAX_SB - (SNOWBALL_HNUM + 3)) - ((nCntSnowBall - (SNOWBALL_HNUM + 2)) / 2);
		nIdx[nCntSnowBall + (((nCntSnowBall - (SNOWBALL_HNUM + 2)) / ((SNOWBALL_HNUM + 1) * 2)) * 2)] = (SNOWBALL_HNUM + 1) - (SNOWBALL_HNUM + 1) * ((nCntSnowBall - (SNOWBALL_HNUM + 2)) % 2) + (VT_MAX_SB - (SNOWBALL_HNUM + 3)) - ((nCntSnowBall - (SNOWBALL_HNUM + 2)) / 2);
	}

	for (nCntSnowBall = 1; nCntSnowBall < SNOWBALL_HNUM + 2; nCntSnowBall++)
	{//FAN����
		pIdx[INDEX_SB_NUM - nCntSnowBall] = VT_MAX_SB - (SNOWBALL_HNUM + 2) + (nCntSnowBall - 1);
		nIdx[INDEX_SB_NUM - nCntSnowBall] = VT_MAX_SB - (SNOWBALL_HNUM + 2) + (nCntSnowBall - 1);
	}
	pIdx[INDEX_SB_NUM - (SNOWBALL_HNUM + 2)] = VT_MAX_SB - 1;
	nIdx[INDEX_SB_NUM - (SNOWBALL_HNUM + 2)] = VT_MAX_SB - 1;

	g_pIdxBuffSnowBall->Unlock();
}

//-------------------
//�|���S���I������
//-------------------
void UninitSnowBall(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureSnowBall[nCnt] != NULL)
		{
			g_pTextureSnowBall[nCnt]->Release();
			g_pTextureSnowBall[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSnowBall != NULL)
	{
		g_pVtxBuffSnowBall->Release();
		g_pVtxBuffSnowBall = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffSnowBall != NULL)
	{
		g_pIdxBuffSnowBall->Release();
		g_pIdxBuffSnowBall = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateSnowBall(void)
{
	int nCntSnowBall;
	for (nCntSnowBall = 0; nCntSnowBall < SNOWBALL_MAX; nCntSnowBall++)
	{
		if (g_aSnowBall[nCntSnowBall].bUse)
		{
			g_aSnowBall[nCntSnowBall].rot.z += 0.1f;

			g_aSnowBall[nCntSnowBall].move.y += GRAVITY;

			g_aSnowBall[nCntSnowBall].posOld = g_aSnowBall[nCntSnowBall].pos;

			g_aSnowBall[nCntSnowBall].pos += g_aSnowBall[nCntSnowBall].move;

			CollisionStage(NULL);

			//�ړ��ʂ̍X�V(����)
			g_aSnowBall[nCntSnowBall].move.x += (0.0f - g_aSnowBall[nCntSnowBall].move.x) * 0.1f;
			g_aSnowBall[nCntSnowBall].move.z += (0.0f - g_aSnowBall[nCntSnowBall].move.z) * 0.1f;

			SetHitShere(g_aSnowBall[nCntSnowBall].pos, g_aSnowBall[nCntSnowBall].scale * SNOWBALL_RADIUS, 2, PLAYER);
		}
	}
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawSnowBall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntSnowBall;
	for (nCntSnowBall = 0; nCntSnowBall < SNOWBALL_MAX; nCntSnowBall++)
	{
		if (g_aSnowBall[nCntSnowBall].bUse)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aSnowBall[nCntSnowBall].mtxWorld);

			//�傫���̔��f
			D3DXMatrixScaling(&mtxScale, g_aSnowBall[nCntSnowBall].scale.x, g_aSnowBall[nCntSnowBall].scale.y, g_aSnowBall[nCntSnowBall].scale.z);
			D3DXMatrixMultiply(&g_aSnowBall[nCntSnowBall].mtxWorld, &g_aSnowBall[nCntSnowBall].mtxWorld, &mtxScale);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aSnowBall[nCntSnowBall].rot.y, g_aSnowBall[nCntSnowBall].rot.x, g_aSnowBall[nCntSnowBall].rot.z);
			D3DXMatrixMultiply(&g_aSnowBall[nCntSnowBall].mtxWorld, &g_aSnowBall[nCntSnowBall].mtxWorld, &mtxRot);

			//�ʒu�̌v�Z
			D3DXMatrixTranslation(&mtxTrans, g_aSnowBall[nCntSnowBall].pos.x, g_aSnowBall[nCntSnowBall].pos.y, g_aSnowBall[nCntSnowBall].pos.z);
			D3DXMatrixMultiply(&g_aSnowBall[nCntSnowBall].mtxWorld, &g_aSnowBall[nCntSnowBall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSnowBall[nCntSnowBall].mtxWorld);

			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffSnowBall, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffSnowBall);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSnowBall[1]);

			//�Ƀ|���S���̕`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLEFAN,//�^�C�v
				0,
				0,
				SNOWBALL_HNUM + 2,//���_��
				0,
				SNOWBALL_HNUM//�|���S���̌�
			);

			pDevice->SetTexture(0, g_pTextureSnowBall[0]);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				0,
				0,
				VT_MAX_SB - (SNOWBALL_HNUM + 2) * 2,//���_��
				SNOWBALL_HNUM + 2,
				POLYGON_SB_NUM - SNOWBALL_HNUM * 2//�|���S���̌�
			);

			pDevice->SetTexture(0, g_pTextureSnowBall[1]);

			//�Ƀ|���S���̕`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLEFAN,//�^�C�v
				0,
				0,
				SNOWBALL_HNUM + 2,//���_��
				INDEX_SB_NUM - (SNOWBALL_HNUM + 2),
				SNOWBALL_HNUM//�|���S���̌�
			);
		}
	}
}

//----------
//�ݒ�
//----------
void SetSnowBall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	int nCntSnowBall;
	for (nCntSnowBall = 0; nCntSnowBall < SNOWBALL_MAX; nCntSnowBall++)
	{//���̐�
		if (!g_aSnowBall[nCntSnowBall].bUse)
		{//�g�p���Ă��Ȃ�
			//�L����
			g_aSnowBall[nCntSnowBall].pos = pos;
			g_aSnowBall[nCntSnowBall].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aSnowBall[nCntSnowBall].rot = rot;
			g_aSnowBall[nCntSnowBall].scale = scale;
			g_aSnowBall[nCntSnowBall].bUse = true;
			break;
		}
	}
}

//----------------------------
//�擾
//----------------------------
SnowBall* GetSnowBall(void)
{
	return &g_aSnowBall[0];
}

//------------------------------------------------
//�Փ�
//------------------------------------------------
void CollisionSnowBall(D3DXVECTOR3 pos, float Length)
{
	int nCntSnowBall;
	for (nCntSnowBall = 0; nCntSnowBall < SNOWBALL_MAX; nCntSnowBall++)
	{//���̐�
		if (g_aSnowBall[nCntSnowBall].bUse)
		{//�g�p���Ă��Ȃ�
			float Space = sqrtf((pos.x - g_aSnowBall[nCntSnowBall].pos.x) * (pos.x - g_aSnowBall[nCntSnowBall].pos.x) + (pos.y - g_aSnowBall[nCntSnowBall].pos.y) * (pos.y - g_aSnowBall[nCntSnowBall].pos.y) + (pos.z - g_aSnowBall[nCntSnowBall].pos.z) * (pos.z - g_aSnowBall[nCntSnowBall].pos.z));
			if (Space < SNOWBALL_RADIUS * g_aSnowBall[nCntSnowBall].scale.x + Length * 0.5f)
			{
				Space = (SNOWBALL_RADIUS * g_aSnowBall[nCntSnowBall].scale.x + Length * 0.5f) - Space;
				D3DXVECTOR3 Hitvec = g_aSnowBall[nCntSnowBall].pos - pos;
				D3DXVec3Normalize(&Hitvec, &Hitvec);
				g_aSnowBall[nCntSnowBall].move += Hitvec * Space;
				g_aSnowBall[nCntSnowBall].scale.x += Space * 0.01f;
				g_aSnowBall[nCntSnowBall].scale.y += Space * 0.01f;
				g_aSnowBall[nCntSnowBall].scale.z += Space * 0.01f;
			}
		}
	}
}