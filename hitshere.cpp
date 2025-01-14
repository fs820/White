//----------------------------------------
//
//�|���S���\������[hitshere.cpp]
//Author fuma sato
//
//----------------------------------------

#include"hitshere.h"
#include"player.h"
#include"Dog.h"
#include"Crow.h"
#include"particle.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHitShere = NULL;//�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffHitShere = NULL;//�C���f�b�N�X�o�b�t�@�̃|�C���^
HitShere g_aHitShere[HITSHERE_MAX];

//----------------------
//�|���S���̏���������
//----------------------
void InitHitShere(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	VERTEX_3D* pVtx;//���_���|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX_HS,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHitShere,
		NULL
	);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * INDEX_HS_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffHitShere,
		NULL
	);

	int nCntHitShere, nCntHitShere2;
	for (nCntHitShere = 0; nCntHitShere < HITSHERE_MAX; nCntHitShere++)
	{
		g_aHitShere[nCntHitShere].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aHitShere[nCntHitShere].scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aHitShere[nCntHitShere].nLife = 0;
		g_aHitShere[nCntHitShere].Master = MAX;
		g_aHitShere[nCntHitShere].bUse = false;
	}
	//1��

	g_pVtxBuffHitShere->Lock(0, 0, (void**)&pVtx, 0);

	//�ɒ��_
	pVtx[0].pos = D3DXVECTOR3(0.0f, HITSHERE_RADIUS, 0.0f);

	D3DXVECTOR3 npos = D3DXVECTOR3(0.0f, HITSHERE_RADIUS, 0.0f), dpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	npos = npos - dpos;
	D3DXVec3Normalize(&npos, &npos);
	pVtx[0].nor = npos;

	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	for (nCntHitShere = 0; nCntHitShere < HITSHERE_VNUM - 1; nCntHitShere++)
	{//1������Z���̃��[�v
		for (nCntHitShere2 = 0; nCntHitShere2 < HITSHERE_HNUM + 1; nCntHitShere2++)
		{//1������X���̃��[�v

			//�~�`�̊p�x
			float fangleH = (360.0f / HITSHERE_HNUM) * nCntHitShere2 * (D3DX_PI / 180.0f), fangleV = (HITSHERE_ANG / HITSHERE_VNUM) * (nCntHitShere + 1) * (D3DX_PI / 180.0f);

			//���W�ݒ�
			pVtx[nCntHitShere * (HITSHERE_HNUM + 1) + nCntHitShere2 + 1].pos = D3DXVECTOR3(sinf(fangleH) * sinf(fangleV) * HITSHERE_RADIUS, cosf(fangleV) * HITSHERE_RADIUS, cosf(fangleH) * sinf(fangleV) * HITSHERE_RADIUS);

			//nor
			D3DXVECTOR3 npos = D3DXVECTOR3(sinf(fangleH) * sinf(fangleV) * HITSHERE_RADIUS, cosf(fangleV) * HITSHERE_RADIUS, cosf(fangleH) * sinf(fangleV) * HITSHERE_RADIUS), dpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			npos = npos - dpos;
			D3DXVec3Normalize(&npos, &npos);
			pVtx[nCntHitShere * (HITSHERE_HNUM + 1) + nCntHitShere2 + 1].nor = npos;

			//�J���[
			pVtx[nCntHitShere * (HITSHERE_HNUM + 1) + nCntHitShere2 + 1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

			//�e�N�X�`��
			pVtx[nCntHitShere * (HITSHERE_HNUM + 1) + nCntHitShere2 + 1].tex = D3DXVECTOR2(0.0f,0.0f);
		}
	}

	//�ɒ��_
	pVtx[VT_MAX_HS - 1].pos = D3DXVECTOR3(0.0f, -HITSHERE_RADIUS, 0.0f);

	npos = D3DXVECTOR3(0.0f, -HITSHERE_RADIUS, 0.0f), dpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	npos = npos - dpos;
	D3DXVec3Normalize(&npos, &npos);
	pVtx[VT_MAX_HS - 1].nor = npos;

	pVtx[VT_MAX_HS - 1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

	pVtx[VT_MAX_HS - 1].tex = D3DXVECTOR2(0.0f,0.0f);

	g_pVtxBuffHitShere->Unlock();

	WORD* pIdx;
	int nIdx[INDEX_HS_NUM];
	g_pIdxBuffHitShere->Lock(0, 0, (void**)&pIdx, 0);

	pIdx[0] = 0;
	nIdx[0] = 0;
	for (nCntHitShere = 1; nCntHitShere < HITSHERE_HNUM + 2; nCntHitShere++)
	{//FAN����
		pIdx[nCntHitShere] = nCntHitShere;
		nIdx[nCntHitShere] = nCntHitShere;
	}
	for (nCntHitShere = HITSHERE_HNUM + 2; nCntHitShere < INDEX_HS_NUM - (HITSHERE_VNUM - 2) * 2 - HITSHERE_HNUM; nCntHitShere++)
	{//HSRIP����
		if ((nCntHitShere - (HITSHERE_HNUM + 2)) % (((HITSHERE_HNUM + 1) * 2)) == 0 && (nCntHitShere - (HITSHERE_HNUM + 2)) != 0)
		{//�k�ރ|���S��
			//�C���f�b�N�X�w��
			pIdx[nCntHitShere - 2 + (((nCntHitShere - (HITSHERE_HNUM + 2)) / ((HITSHERE_HNUM + 1) * 2)) * 2)] = (HITSHERE_HNUM + 1) - (HITSHERE_HNUM + 1) * (((nCntHitShere - (HITSHERE_HNUM + 2)) - 1) % 2) + (VT_MAX_HS - (HITSHERE_HNUM + 3)) - (((nCntHitShere - (HITSHERE_HNUM + 2)) - 1) / 2);
			nIdx[nCntHitShere - 2 + (((nCntHitShere - (HITSHERE_HNUM + 2)) / ((HITSHERE_HNUM + 1) * 2)) * 2)] = (HITSHERE_HNUM + 1) - (HITSHERE_HNUM + 1) * (((nCntHitShere - (HITSHERE_HNUM + 2)) - 1) % 2) + (VT_MAX_HS - (HITSHERE_HNUM + 3)) - (((nCntHitShere - (HITSHERE_HNUM + 2)) - 1) / 2);

			//�C���f�b�N�X�w��
			pIdx[nCntHitShere - 1 + (((nCntHitShere - (HITSHERE_HNUM + 2)) / ((HITSHERE_HNUM + 1) * 2)) * 2)] = (HITSHERE_HNUM + 1) - (HITSHERE_HNUM + 1) * ((nCntHitShere - (HITSHERE_HNUM + 2)) % 2) + (VT_MAX_HS - (HITSHERE_HNUM + 3)) - ((nCntHitShere - (HITSHERE_HNUM + 2)) / 2);
			nIdx[nCntHitShere - 1 + (((nCntHitShere - (HITSHERE_HNUM + 2)) / ((HITSHERE_HNUM + 1) * 2)) * 2)] = (HITSHERE_HNUM + 1) - (HITSHERE_HNUM + 1) * ((nCntHitShere - (HITSHERE_HNUM + 2)) % 2) + (VT_MAX_HS - (HITSHERE_HNUM + 3)) - ((nCntHitShere - (HITSHERE_HNUM + 2)) / 2);
		}

		//�C���f�b�N�X�w��
		pIdx[nCntHitShere + (((nCntHitShere - (HITSHERE_HNUM + 2)) / ((HITSHERE_HNUM + 1) * 2)) * 2)] = (HITSHERE_HNUM + 1) - (HITSHERE_HNUM + 1) * ((nCntHitShere - (HITSHERE_HNUM + 2)) % 2) + (VT_MAX_HS - (HITSHERE_HNUM + 3)) - ((nCntHitShere - (HITSHERE_HNUM + 2)) / 2);
		nIdx[nCntHitShere + (((nCntHitShere - (HITSHERE_HNUM + 2)) / ((HITSHERE_HNUM + 1) * 2)) * 2)] = (HITSHERE_HNUM + 1) - (HITSHERE_HNUM + 1) * ((nCntHitShere - (HITSHERE_HNUM + 2)) % 2) + (VT_MAX_HS - (HITSHERE_HNUM + 3)) - ((nCntHitShere - (HITSHERE_HNUM + 2)) / 2);
	}

	for (nCntHitShere = 1; nCntHitShere < HITSHERE_HNUM + 2; nCntHitShere++)
	{//FAN����
		pIdx[INDEX_HS_NUM - nCntHitShere] = VT_MAX_HS - (HITSHERE_HNUM + 2) + (nCntHitShere - 1);
		nIdx[INDEX_HS_NUM - nCntHitShere] = VT_MAX_HS - (HITSHERE_HNUM + 2) + (nCntHitShere - 1);
	}
	pIdx[INDEX_HS_NUM - (HITSHERE_HNUM + 2)] = VT_MAX_HS - 1;
	nIdx[INDEX_HS_NUM - (HITSHERE_HNUM + 2)] = VT_MAX_HS - 1;

	g_pIdxBuffHitShere->Unlock();
}

//-------------------
//�|���S���I������
//-------------------
void UninitHitShere(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffHitShere != NULL)
	{
		g_pVtxBuffHitShere->Release();
		g_pVtxBuffHitShere = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffHitShere != NULL)
	{
		g_pIdxBuffHitShere->Release();
		g_pIdxBuffHitShere = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateHitShere(void)
{
	int nCntHitShere;
	for (nCntHitShere = 0; nCntHitShere < HITSHERE_MAX; nCntHitShere++)
	{//���̐�
		if (g_aHitShere[nCntHitShere].bUse)
		{//�g�p���Ă���
			TriggerShere(nCntHitShere);

			g_aHitShere[nCntHitShere].nLife--;
			if (g_aHitShere[nCntHitShere].nLife <= 0)
			{
				g_aHitShere[nCntHitShere].bUse = false;
			}
		}
	}
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawHitShere(void)
{
#ifdef _DEBUG

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntHitShere;
	for (nCntHitShere = 0; nCntHitShere < HITSHERE_MAX; nCntHitShere++)
	{
		if (g_aHitShere[nCntHitShere].bUse)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aHitShere[nCntHitShere].mtxWorld);

			//�傫���̔��f
			D3DXMatrixScaling(&mtxScale, g_aHitShere[nCntHitShere].scale.x, g_aHitShere[nCntHitShere].scale.y, g_aHitShere[nCntHitShere].scale.z);
			D3DXMatrixMultiply(&g_aHitShere[nCntHitShere].mtxWorld, &g_aHitShere[nCntHitShere].mtxWorld, &mtxScale);

			//�ʒu�̌v�Z
			D3DXMatrixTranslation(&mtxTrans, g_aHitShere[nCntHitShere].pos.x, g_aHitShere[nCntHitShere].pos.y, g_aHitShere[nCntHitShere].pos.z);
			D3DXMatrixMultiply(&g_aHitShere[nCntHitShere].mtxWorld, &g_aHitShere[nCntHitShere].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aHitShere[nCntHitShere].mtxWorld);

			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffHitShere, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffHitShere);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//�Ƀ|���S���̕`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLEFAN,//�^�C�v
				0,
				0,
				HITSHERE_HNUM + 2,//���_��
				0,
				HITSHERE_HNUM//�|���S���̌�
			);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				0,
				0,
				VT_MAX_HS - (HITSHERE_HNUM + 2) * 2,//���_��
				HITSHERE_HNUM + 2,
				POLYGON_HS_NUM - HITSHERE_HNUM * 2//�|���S���̌�
			);

			//�Ƀ|���S���̕`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLEFAN,//�^�C�v
				0,
				0,
				HITSHERE_HNUM + 2,//���_��
				INDEX_HS_NUM - (HITSHERE_HNUM + 2),
				HITSHERE_HNUM//�|���S���̌�
			);
		}
	}

#endif
}

//----------
//�ݒ�
//----------
void SetHitShere(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int Life, MASTER Master)
{
	int nCntHitShere;
	for (nCntHitShere = 0; nCntHitShere < HITSHERE_MAX; nCntHitShere++)
	{//���̐�
		if (!g_aHitShere[nCntHitShere].bUse)
		{//�g�p���Ă��Ȃ�
			//�L����
			g_aHitShere[nCntHitShere].pos = pos;
			g_aHitShere[nCntHitShere].scale = scale;
			g_aHitShere[nCntHitShere].nLife = Life;
			g_aHitShere[nCntHitShere].Master = Master;
			g_aHitShere[nCntHitShere].bUse = true;
			break;
		}
	}
}

//--------------------------
//�����蔻��
//--------------------------
void TriggerShere(int Indx)
{
	switch (g_aHitShere[Indx].Master)
	{
	case PLAYER:
		Dog* pDog;
		Crow* pCrow;
		pDog = GetDog();
		pCrow = GetCrow();
		for (int nCntDog = 0; nCntDog < MAX_DOG; nCntDog++, pDog++)
		{
			float Space = sqrtf((pDog->pos.x - g_aHitShere[Indx].pos.x) * (pDog->pos.x - g_aHitShere[Indx].pos.x) + (pDog->pos.y - g_aHitShere[Indx].pos.y) * (pDog->pos.y - g_aHitShere[Indx].pos.y) + (pDog->pos.z - g_aHitShere[Indx].pos.z) * (pDog->pos.z - g_aHitShere[Indx].pos.z));
			if (Space < DOG_SIZE * 0.5f + g_aHitShere[Indx].scale.x)
			{
				Space = (DOG_SIZE * 0.5f + g_aHitShere[Indx].scale.x) - Space;
				D3DXVECTOR3 Hitvec = pDog->pos - g_aHitShere[Indx].pos;
				D3DXVec3Normalize(&Hitvec, &Hitvec);
				pDog->move += Hitvec * Space;
				pDog->nLife -= DAMEGE;
				SetParticle(g_aHitShere[Indx].pos + Hitvec * g_aHitShere[Indx].scale.x, g_aHitShere[Indx].scale * 0.02f);
			}
		}
		for (int nCntCrow = 0; nCntCrow < MAX_CROW; nCntCrow++, pCrow++)
		{
			float Space = sqrtf((pCrow->pos.x - g_aHitShere[Indx].pos.x) * (pCrow->pos.x - g_aHitShere[Indx].pos.x) + (pCrow->pos.y - g_aHitShere[Indx].pos.y) * (pCrow->pos.y - g_aHitShere[Indx].pos.y) + (pCrow->pos.z - g_aHitShere[Indx].pos.z) * (pCrow->pos.z - g_aHitShere[Indx].pos.z));
			if (Space < DOG_SIZE * 0.5f + g_aHitShere[Indx].scale.x)
			{
				Space = (DOG_SIZE * 0.5f + g_aHitShere[Indx].scale.x) - Space;
				D3DXVECTOR3 Hitvec = pCrow->pos - g_aHitShere[Indx].pos;
				D3DXVec3Normalize(&Hitvec, &Hitvec);
				pCrow->move += Hitvec * Space;
				pCrow->nLife -= DAMEGE;
				SetParticle(g_aHitShere[Indx].pos + Hitvec * g_aHitShere[Indx].scale.x, g_aHitShere[Indx].scale * 0.02f);
			}
		}
		break;
	case ENEMY:
		Player* pPlayer;
		pPlayer = GetPlayer();

		float Space = sqrtf((pPlayer->pos.x - g_aHitShere[Indx].pos.x) * (pPlayer->pos.x - g_aHitShere[Indx].pos.x) + (pPlayer->pos.y - g_aHitShere[Indx].pos.y) * (pPlayer->pos.y - g_aHitShere[Indx].pos.y) + (pPlayer->pos.z - g_aHitShere[Indx].pos.z) * (pPlayer->pos.z - g_aHitShere[Indx].pos.z));
		if (Space < PLAYER_SIZE * 0.5f + g_aHitShere[Indx].scale.x)
		{
			Space = (PLAYER_SIZE * 0.5f + g_aHitShere[Indx].scale.x) - Space;
			D3DXVECTOR3 Hitvec = pPlayer->pos - g_aHitShere[Indx].pos;
			D3DXVec3Normalize(&Hitvec, &Hitvec);
			pPlayer->move += Hitvec * Space;
			pPlayer->nLife -= DAMEGE;
			SetParticle(g_aHitShere[Indx].pos + Hitvec * g_aHitShere[Indx].scale.x, g_aHitShere[Indx].scale * 0.02f);
		}
		break;
	}
}