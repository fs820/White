//----------------------------------------
//
//���f���\������[stage.cpp]
//Author fuma sato
//
//----------------------------------------

#include"stage.h"
#include"camera.h"
#include"input.h"
#include"shadow.h"
#include"player.h"
#include"Dog.h"
#include"snowball.h"

//�O���[�o���ϐ��錾
Stage g_aStage[STAGE_MAX] = {};
//----------------------
//�|���S���̏���������
//----------------------
void InitStage(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntStage, nCntTex;
	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		g_aStage[nCntStage].pMesh = NULL;
		g_aStage[nCntStage].pBuffMat = NULL;
		for (nCntTex = 0; nCntTex < TEXTURE_MAX; nCntTex++)
		{
			g_aStage[nCntStage].apTexture[nCntTex] = NULL;
		}
		g_aStage[nCntStage].dwNumMat = 0;
		g_aStage[nCntStage].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].fLength = 0.0f;
		g_aStage[nCntStage].fAngle = 0.0f;
		g_aStage[nCntStage].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aStage[nCntStage].nIdxShadow = -1;
		g_aStage[nCntStage].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].nNumVtx = 0;
		g_aStage[nCntStage].sizeFVF = 0;
		g_aStage[nCntStage].pVtxBuff = NULL;
		g_aStage[nCntStage].bUse = false;
	}
}

//-------------------
//�|���S���I������
//-------------------
void UninitStage(void)
{
	int nCntStage;
	unsigned int nCntTex;
	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		for (nCntTex = 0; nCntTex < g_aStage[nCntStage].dwNumMat; nCntTex++)
		{
			if (g_aStage[nCntStage].apTexture[nCntTex] != NULL)
			{
				g_aStage[nCntStage].apTexture[nCntTex]->Release();
				g_aStage[nCntStage].apTexture[nCntTex] = NULL;
			}
		}
		//���b�V���̔j��
		if (g_aStage[nCntStage].pMesh != NULL)
		{
			g_aStage[nCntStage].pMesh->Release();
			g_aStage[nCntStage].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (g_aStage[nCntStage].pBuffMat != NULL)
		{
			g_aStage[nCntStage].pBuffMat->Release();
			g_aStage[nCntStage].pBuffMat = NULL;
		}
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateStage(void)
{

}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawStage(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	int nCntStage;
	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		if (g_aStage[nCntStage].bUse)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aStage[nCntStage].mtxWorld);

			//�傫���̔��f
			D3DXMatrixScaling(&mtxScale, g_aStage[nCntStage].scale.x, g_aStage[nCntStage].scale.y, g_aStage[nCntStage].scale.z);
			D3DXMatrixMultiply(&g_aStage[nCntStage].mtxWorld, &g_aStage[nCntStage].mtxWorld, &mtxScale);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aStage[nCntStage].rot.y, g_aStage[nCntStage].rot.x, g_aStage[nCntStage].rot.z);
			D3DXMatrixMultiply(&g_aStage[nCntStage].mtxWorld, &g_aStage[nCntStage].mtxWorld, &mtxRot);

			//�ʒu�̔��f
			D3DXMatrixTranslation(&mtxTrans, g_aStage[nCntStage].pos.x, g_aStage[nCntStage].pos.y, g_aStage[nCntStage].pos.z);
			D3DXMatrixMultiply(&g_aStage[nCntStage].mtxWorld, &g_aStage[nCntStage].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aStage[nCntStage].mtxWorld);

			//���݂̃}�e���A���擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aStage[nCntStage].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aStage[nCntStage].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//�e�N�X�`��
				pDevice->SetTexture(0, g_aStage[nCntStage].apTexture[nCntMat]);

				//���f���`��
				g_aStage[nCntStage].pMesh->DrawSubset(nCntMat);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------
//�z�u
//-----------
void SetStage(char* name, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^
	int nCntStage, nCntTex;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		if (!g_aStage[nCntStage].bUse)
		{
			//X�t�@�C���ǂݍ���
			D3DXLoadMeshFromX
			(
				name,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aStage[nCntStage].pBuffMat,
				NULL,
				&g_aStage[nCntStage].dwNumMat,
				&g_aStage[nCntStage].pMesh
			);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aStage[nCntStage].pBuffMat->GetBufferPointer();

			for (nCntTex = 0; nCntTex < (int)g_aStage[nCntStage].dwNumMat; nCntTex++)
			{
				if (pMat[nCntTex].pTextureFilename != NULL)
				{//�e�N�X�`��������
					//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile
					(
						pDevice,
						pMat[nCntTex].pTextureFilename,
						&g_aStage[nCntStage].apTexture[nCntTex]
					);
				}
			}

			//���_��
			g_aStage[nCntStage].nNumVtx = g_aStage[nCntStage].pMesh->GetNumVertices();
			//���_�T�C�Y
			g_aStage[nCntStage].sizeFVF = D3DXGetFVFVertexSize(g_aStage[nCntStage].pMesh->GetFVF());
			//���_�o�b�t�@�̎擾
			g_aStage[nCntStage].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_aStage[nCntStage].pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < g_aStage[nCntStage].nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_aStage[nCntStage].pVtxBuff;

				if (vtx.x > g_aStage[nCntStage].vtxMax.x)
				{
					g_aStage[nCntStage].vtxMax.x = vtx.x;
				}
				if (vtx.x < g_aStage[nCntStage].vtxMin.x)
				{
					g_aStage[nCntStage].vtxMin.x = vtx.x;
				}
				if (vtx.y > g_aStage[nCntStage].vtxMax.y)
				{
					g_aStage[nCntStage].vtxMax.y = vtx.y;
				}
				if (vtx.y < g_aStage[nCntStage].vtxMin.y)
				{
					g_aStage[nCntStage].vtxMin.y = vtx.y;
				}
				if (vtx.z > g_aStage[nCntStage].vtxMax.z)
				{
					g_aStage[nCntStage].vtxMax.z = vtx.z;
				}
				if (vtx.z < g_aStage[nCntStage].vtxMin.z)
				{
					g_aStage[nCntStage].vtxMin.z = vtx.z;
				}

				g_aStage[nCntStage].pVtxBuff += g_aStage[nCntStage].sizeFVF;
			}

			g_aStage[nCntStage].pos = pos;
			g_aStage[nCntStage].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aStage[nCntStage].rot = rot;
			g_aStage[nCntStage].scale = scale;
			g_aStage[nCntStage].vtxMax.x *= g_aStage[nCntStage].scale.x;
			g_aStage[nCntStage].vtxMax.y *= g_aStage[nCntStage].scale.y;
			g_aStage[nCntStage].vtxMax.z *= g_aStage[nCntStage].scale.z;
			g_aStage[nCntStage].vtxMin.x *= g_aStage[nCntStage].scale.x;
			g_aStage[nCntStage].vtxMin.y *= g_aStage[nCntStage].scale.y;
			g_aStage[nCntStage].vtxMin.z *= g_aStage[nCntStage].scale.z;

			g_aStage[nCntStage].fLength = sqrtf((g_aStage[nCntStage].vtxMax.x - g_aStage[nCntStage].vtxMin.x) * (g_aStage[nCntStage].vtxMax.x - g_aStage[nCntStage].vtxMin.x) + (g_aStage[nCntStage].vtxMax.z - g_aStage[nCntStage].vtxMin.z) * (g_aStage[nCntStage].vtxMax.z - g_aStage[nCntStage].vtxMin.z)) / 2.0f;
			g_aStage[nCntStage].fAngle = atan2f((g_aStage[nCntStage].vtxMax.x - g_aStage[nCntStage].vtxMin.x), (g_aStage[nCntStage].vtxMax.z - g_aStage[nCntStage].vtxMin.z));//�p�x

			g_aStage[nCntStage].nIdxShadow = SetShadow(g_aStage[nCntStage].pos, g_aStage[nCntStage].rot);
			g_aStage[nCntStage].bUse = true;
			break;
		}
	}
}

//------------------------------
//�ʒu�擾
//------------------------------
Stage* GetStage(void)
{
	return &g_aStage[0];
}

//------------------------------
//�����蔻��
//------------------------------
bool CollisionStage(Stage** pStage)
{
	bool bRanding = false;
	Player* pPlayer = GetPlayer();
	Dog* pDog = GetDog();
	SnowBall* pSnowBall = GetSnowBall();
	D3DXVECTOR3 aPos[8] = {}, Stagevec = {}, Posvec = {}, PosOldvec = {}, movevec = {}, Norvec = {}, Dovec = {}, Hit = {};
	int nCntStage;
	float StageCross, PosCross;
	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{//�ǂ̐�
		if (g_aStage[nCntStage].bUse)
		{//�g���Ă��铧���łȂ���
			aPos[0] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y - g_aStage[nCntStage].fAngle) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y - g_aStage[nCntStage].fAngle) * g_aStage[nCntStage].fLength);
			aPos[1] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y - (D3DX_PI - g_aStage[nCntStage].fAngle)) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y - (D3DX_PI - g_aStage[nCntStage].fAngle)) * g_aStage[nCntStage].fLength);
			aPos[2] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y - (D3DX_PI + g_aStage[nCntStage].fAngle)) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y - (D3DX_PI + g_aStage[nCntStage].fAngle)) * g_aStage[nCntStage].fLength);
			aPos[3] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y + g_aStage[nCntStage].fAngle) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + g_aStage[nCntStage].fAngle) * g_aStage[nCntStage].fLength);
			aPos[4] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength);
			aPos[5] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength);
			aPos[6] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength);
			aPos[7] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength);

			Stagevec = aPos[1] - aPos[0];//�ǂ̃x�N�g��
			Posvec = pPlayer->pos - aPos[0];//�ǂɑ΂���v���C���[�̃x�N�g��
			PosOldvec = pPlayer->posOld - aPos[0];//�ǂɑ΂���v���C���[�̋��x�N�g��
			movevec = pPlayer->pos - pPlayer->posOld;//�v���C���[�̈ړ��x�N�g��
			if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pPlayer->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pPlayer->pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
			{//��
				StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
				PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
				PosCross /= StageCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[0] + Stagevec * PosCross;
					movevec = pPlayer->pos - Hit;//�v���C���[�̈ړ��x�N�g��
					Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
					pPlayer->pos += Dovec * 1.1f;
				}
			}

			Stagevec = aPos[2] - aPos[1];//�ǂ̃x�N�g��
			Posvec = pPlayer->pos - aPos[1];//�ǂɑ΂���v���C���[�̃x�N�g��
			PosOldvec = pPlayer->posOld - aPos[1];//�ǂɑ΂���v���C���[�̋��x�N�g��
			movevec = pPlayer->pos - pPlayer->posOld;//�v���C���[�̈ړ��x�N�g��
			if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pPlayer->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pPlayer->pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
			{//��O
				StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
				PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
				PosCross /= StageCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[1] + Stagevec * PosCross;
					movevec = pPlayer->pos - Hit;//�v���C���[�̈ړ��x�N�g��
					Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
					pPlayer->pos += Dovec * 1.1f;
				}
			}

			Stagevec = aPos[3] - aPos[2];//�ǂ̃x�N�g��
			Posvec = pPlayer->pos - aPos[2];//�ǂɑ΂���v���C���[�̃x�N�g��
			PosOldvec = pPlayer->posOld - aPos[2];//�ǂɑ΂���v���C���[�̋��x�N�g��
			movevec = pPlayer->pos - pPlayer->posOld;//�v���C���[�̈ړ��x�N�g��
			if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pPlayer->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pPlayer->pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
			{//�E
				StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
				PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
				PosCross /= StageCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[2] + Stagevec * PosCross;
					movevec = pPlayer->pos - Hit;//�v���C���[�̈ړ��x�N�g��
					Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
					pPlayer->pos += Dovec * 1.1f;
				}
			}

			Stagevec = aPos[0] - aPos[3];//�ǂ̃x�N�g��
			Posvec = pPlayer->pos - aPos[3];//�ǂɑ΂���v���C���[�̃x�N�g��
			PosOldvec = pPlayer->posOld - aPos[3];//�ǂɑ΂���v���C���[�̋��x�N�g��
			movevec = pPlayer->pos - pPlayer->posOld;//�v���C���[�̈ړ��x�N�g��
			if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pPlayer->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pPlayer->pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
			{//��
				StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
				PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
				PosCross /= StageCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[3] + Stagevec * PosCross;
					movevec = pPlayer->pos - Hit;//�v���C���[�̈ړ��x�N�g��
					Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
					pPlayer->pos += Dovec * 1.1f;
				}
			}

			Stagevec = aPos[5] - aPos[4];//�ǂ̃x�N�g��
			Posvec = pPlayer->pos - aPos[4];//�ǂɑ΂���v���C���[�̃x�N�g��
			PosOldvec = pPlayer->posOld - aPos[4];//�ǂɑ΂���v���C���[�̋��x�N�g��
			movevec = pPlayer->pos - pPlayer->posOld;//�v���C���[�̈ړ��x�N�g��
			if ((Stagevec.x * Posvec.y) - (Stagevec.y * Posvec.x) <= 0.0f && (Stagevec.x * PosOldvec.y) - (Stagevec.y * PosOldvec.x) >= 0.0f && pPlayer->pos.z + pPlayer->aModel[1].pos.z + pPlayer->aModel[1].vtxMin.z < g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength && pPlayer->pos.z + pPlayer->aModel[1].pos.z + pPlayer->aModel[1].vtxMax.z > g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength)
			{//��
				StageCross = (Stagevec.x * movevec.y) - (Stagevec.y * movevec.x);
				PosCross = (Posvec.x * movevec.y) - (Posvec.y * movevec.x);
				PosCross /= StageCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[4] + Stagevec * PosCross;
					movevec = pPlayer->pos - Hit;//�v���C���[�̈ړ��x�N�g��
					Norvec = D3DXVECTOR3(Stagevec.y, -Stagevec.x, Stagevec.z);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.y * Norvec.y));
					pPlayer->pos += Dovec * 1.001f;
					pPlayer->move.y = 0.0f;
					bRanding = true;
					if (pPlayer->motionType == MOTIONTYPE_JUMP)
					{
						pPlayer->motionType = MOTIONTYPE_LANDING;
					}
					if (pStage != NULL)
					{
						*pStage = &g_aStage[nCntStage];
					}
				}
			}

			Stagevec = aPos[7] - aPos[6];//�ǂ̃x�N�g��
			Posvec = pPlayer->pos - aPos[6];//�ǂɑ΂���v���C���[�̃x�N�g��
			PosOldvec = pPlayer->posOld - aPos[6];//�ǂɑ΂���v���C���[�̋��x�N�g��
			movevec = pPlayer->pos - pPlayer->posOld;//�v���C���[�̈ړ��x�N�g��
			if ((Stagevec.x * Posvec.y) - (Stagevec.y * Posvec.x) <= 0.0f && (Stagevec.x * PosOldvec.y) - (Stagevec.y * PosOldvec.x) >= 0.0f && pPlayer->pos.z + pPlayer->aModel[1].pos.z + pPlayer->aModel[1].vtxMin.z < g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength && pPlayer->pos.z + pPlayer->aModel[1].pos.z + pPlayer->aModel[1].vtxMax.z > g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength)
			{//��
				StageCross = (Stagevec.x * movevec.y) - (Stagevec.y * movevec.x);
				PosCross = (Posvec.x * movevec.y) - (Posvec.y * movevec.x);
				PosCross /= StageCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[6] + Stagevec * PosCross;
					movevec = pPlayer->pos - Hit;//�v���C���[�̈ړ��x�N�g��
					Norvec = D3DXVECTOR3(Stagevec.y, -Stagevec.x, Stagevec.z);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.y * Norvec.y));
					pPlayer->pos += Dovec * 1.001f;
					pPlayer->move.y = 0.0f;
				}
			}

			pDog = GetDog();
			for (int nCntDog = 0; nCntDog < MAX_DOG; nCntDog++, pDog++)
			{
				if (pDog->bUse)
				{
					Stagevec = aPos[1] - aPos[0];//�ǂ̃x�N�g��
					Posvec = pDog->pos - aPos[0];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = pDog->posOld - aPos[0];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pDog->pos - pDog->posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pDog->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pPlayer->pos.y + pDog->aModel[1].pos.y + pDog->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
					{//��
						StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= StageCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[0] + Stagevec * PosCross;
							movevec = pDog->pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							pDog->pos += Dovec * 1.1f;
						}
					}

					Stagevec = aPos[2] - aPos[1];//�ǂ̃x�N�g��
					Posvec = pDog->pos - aPos[1];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = pDog->posOld - aPos[1];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pDog->pos - pDog->posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pDog->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pDog->pos.y + pDog->aModel[1].pos.y + pDog->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
					{//��O
						StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= StageCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[1] + Stagevec * PosCross;
							movevec = pDog->pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							pDog->pos += Dovec * 1.1f;
						}
					}

					Stagevec = aPos[3] - aPos[2];//�ǂ̃x�N�g��
					Posvec = pDog->pos - aPos[2];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = pDog->posOld - aPos[2];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pDog->pos - pDog->posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pDog->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pDog->pos.y + pDog->aModel[1].pos.y + pDog->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
					{//�E
						StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= StageCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[2] + Stagevec * PosCross;
							movevec = pDog->pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							pDog->pos += Dovec * 1.1f;
						}
					}

					Stagevec = aPos[0] - aPos[3];//�ǂ̃x�N�g��
					Posvec = pDog->pos - aPos[3];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = pDog->posOld - aPos[3];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pDog->pos - pDog->posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pDog->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pDog->pos.y + pDog->aModel[1].pos.y + pDog->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
					{//��
						StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= StageCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[3] + Stagevec * PosCross;
							movevec = pDog->pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							pDog->pos += Dovec * 1.1f;
						}
					}

					Stagevec = aPos[5] - aPos[4];//�ǂ̃x�N�g��
					Posvec = pDog->pos - aPos[4];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = pDog->posOld - aPos[4];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pDog->pos - pDog->posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Stagevec.x * Posvec.y) - (Stagevec.y * Posvec.x) <= 0.0f && (Stagevec.x * PosOldvec.y) - (Stagevec.y * PosOldvec.x) >= 0.0f && pDog->pos.z + pPlayer->aModel[1].pos.z + pDog->aModel[1].vtxMin.z < g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength && pDog->pos.z + pDog->aModel[1].pos.z + pDog->aModel[1].vtxMax.z > g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength)
					{//��
						StageCross = (Stagevec.x * movevec.y) - (Stagevec.y * movevec.x);
						PosCross = (Posvec.x * movevec.y) - (Posvec.y * movevec.x);
						PosCross /= StageCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[4] + Stagevec * PosCross;
							movevec = pDog->pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Stagevec.y, -Stagevec.x, Stagevec.z);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.y * Norvec.y));
							pDog->pos += Dovec * 1.001f;
							pDog->move.y = 0.0f;
							bRanding = true;
							if (pDog->motionType == MOTIONTYPE_JUMP)
							{
								pDog->motionType = MOTIONTYPE_LANDING;
							}
							if (pStage != NULL)
							{
								*pStage = &g_aStage[nCntStage];
							}
						}
					}

					Stagevec = aPos[7] - aPos[6];//�ǂ̃x�N�g��
					Posvec = pDog->pos - aPos[6];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = pDog->posOld - aPos[6];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pDog->pos - pDog->posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Stagevec.x * Posvec.y) - (Stagevec.y * Posvec.x) <= 0.0f && (Stagevec.x * PosOldvec.y) - (Stagevec.y * PosOldvec.x) >= 0.0f && pDog->pos.z + pDog->aModel[1].pos.z + pDog->aModel[1].vtxMin.z < g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength && pDog->pos.z + pDog->aModel[1].pos.z + pDog->aModel[1].vtxMax.z > g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength)
					{//��
						StageCross = (Stagevec.x * movevec.y) - (Stagevec.y * movevec.x);
						PosCross = (Posvec.x * movevec.y) - (Posvec.y * movevec.x);
						PosCross /= StageCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[6] + Stagevec * PosCross;
							movevec = pDog->pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Stagevec.y, -Stagevec.x, Stagevec.z);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.y * Norvec.y));
							pDog->pos += Dovec * 1.001f;
							pDog->move.y = 0.0f;
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

					Stagevec = aPos[1] - aPos[0];//�ǂ̃x�N�g��
					Posvec = pos - aPos[0];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = posOld - aPos[0];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pos - posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pos.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
					{//��
						StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= StageCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[0] + Stagevec * PosCross;
							movevec = pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							pSnowBall->pos += Dovec * 1.1f;
						}
					}

					pos = pSnowBall->pos, posOld = pSnowBall->posOld;
					pos.y -= SNOWBALL_RADIUS * pSnowBall->scale.y;
					posOld.y -= SNOWBALL_RADIUS * pSnowBall->scale.y;

					Stagevec = aPos[2] - aPos[1];//�ǂ̃x�N�g��
					Posvec = pos - aPos[1];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = posOld - aPos[1];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pos - posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pos.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
					{//��O
						StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= StageCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[1] + Stagevec * PosCross;
							movevec = pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							pSnowBall->pos += Dovec * 1.1f;
						}
					}

					pos = pSnowBall->pos, posOld = pSnowBall->posOld;
					pos.y -= SNOWBALL_RADIUS * pSnowBall->scale.y;
					posOld.y -= SNOWBALL_RADIUS * pSnowBall->scale.y;

					Stagevec = aPos[3] - aPos[2];//�ǂ̃x�N�g��
					Posvec = pos - aPos[2];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = posOld - aPos[2];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pos - posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pos.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
					{//�E
						StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= StageCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[2] + Stagevec * PosCross;
							movevec = pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							pSnowBall->pos += Dovec * 1.1f;
						}
					}

					pos = pSnowBall->pos, posOld = pSnowBall->posOld;
					pos.y -= SNOWBALL_RADIUS * pSnowBall->scale.y;
					posOld.y -= SNOWBALL_RADIUS * pSnowBall->scale.y;

					Stagevec = aPos[0] - aPos[3];//�ǂ̃x�N�g��
					Posvec = pos - aPos[3];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = posOld - aPos[3];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pos - posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pos.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
					{//��
						StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= StageCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[3] + Stagevec * PosCross;
							movevec = pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							pSnowBall->pos += Dovec * 1.1f;
						}
					}

					pos = pSnowBall->pos, posOld = pSnowBall->posOld;
					pos.y -= SNOWBALL_RADIUS * pSnowBall->scale.y;
					posOld.y -= SNOWBALL_RADIUS * pSnowBall->scale.y;

					Stagevec = aPos[5] - aPos[4];//�ǂ̃x�N�g��
					Posvec = pos - aPos[4];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = posOld - aPos[4];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pos - posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Stagevec.x * Posvec.y) - (Stagevec.y * Posvec.x) <= 0.0f && (Stagevec.x * PosOldvec.y) - (Stagevec.y * PosOldvec.x) >= 0.0f && pos.z < g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength && pDog->pos.z > g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength)
					{//��
						StageCross = (Stagevec.x * movevec.y) - (Stagevec.y * movevec.x);
						PosCross = (Posvec.x * movevec.y) - (Posvec.y * movevec.x);
						PosCross /= StageCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[4] + Stagevec * PosCross;
							movevec = pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Stagevec.y, -Stagevec.x, Stagevec.z);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.y * Norvec.y));
							pSnowBall->pos += Dovec * 1.001f;
							pSnowBall->move.y = 0.0f;
						}
					}

					pos = pSnowBall->pos, posOld = pSnowBall->posOld;
					pos.y -= SNOWBALL_RADIUS * pSnowBall->scale.y;
					posOld.y -= SNOWBALL_RADIUS * pSnowBall->scale.y;

					Stagevec = aPos[7] - aPos[6];//�ǂ̃x�N�g��
					Posvec = pos - aPos[6];//�ǂɑ΂���v���C���[�̃x�N�g��
					PosOldvec = posOld - aPos[6];//�ǂɑ΂���v���C���[�̋��x�N�g��
					movevec = pos - posOld;//�v���C���[�̈ړ��x�N�g��
					if ((Stagevec.x * Posvec.y) - (Stagevec.y * Posvec.x) <= 0.0f && (Stagevec.x * PosOldvec.y) - (Stagevec.y * PosOldvec.x) >= 0.0f && pos.z < g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength && pDog->pos.z > g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength)
					{//��
						StageCross = (Stagevec.x * movevec.y) - (Stagevec.y * movevec.x);
						PosCross = (Posvec.x * movevec.y) - (Posvec.y * movevec.x);
						PosCross /= StageCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							Hit = aPos[6] + Stagevec * PosCross;
							movevec = pos - Hit;//�v���C���[�̈ړ��x�N�g��
							Norvec = D3DXVECTOR3(Stagevec.y, -Stagevec.x, Stagevec.z);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.y * Norvec.y));
							pSnowBall->pos += Dovec * 1.001f;
							pSnowBall->move.y = 0.0f;
						}
					}
				}
			}
		}
	}
	return bRanding;
}