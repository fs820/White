//----------------------------------------
//
//���f���\������[model.cpp]
//Author fuma sato
//
//----------------------------------------

#include"model.h"
#include"camera.h"
#include"input.h"

//�O���[�o���ϐ��錾
//Model g_aModel[MODEL_MAX];
//----------------------
//�|���S���̏���������
//----------------------
void InitModel(void)
{
	//LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	//D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	////�f�o�C�X�̎擾
	//pDevice = GetDevice();

	//int nCnt;
	//for (nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	//{
	//	g_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_aModel[nCnt].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//	//X�t�@�C���ǂݍ���
	//	D3DXLoadMeshFromX
	//	(
	//		X_NAME,
	//		D3DXMESH_SYSTEMMEM,
	//		pDevice,
	//		NULL,
	//		&g_pBuffMatModel,
	//		NULL,
	//		&g_dwNumMatModel,
	//		&g_pMeshModel
	//	);

	//	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	//	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	//	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	//	{
	//		if (pMat[nCntMat].pTextureFilename != NULL)
	//		{//�e�N�X�`��������
	//			//�e�N�X�`���̓ǂݍ���
	//			D3DXCreateTextureFromFile
	//			(
	//				pDevice,
	//				pMat[nCntMat].pTextureFilename,
	//				&g_apTextureModel[nCntMat]
	//			);
	//		}
	//	}
	//}
}

//-------------------
//�|���S���I������
//-------------------
void UninitModel(void)
{
	//for (int i = 0; i < 128; i++)
	//{
	//	if (g_apTextureModel[i]!=NULL)
	//	{
	//		g_apTextureModel[i]->Release();
	//		g_apTextureModel[i] = NULL;
	//	}
	//}
	////���b�V���̔j��
	//if (g_pMeshModel != NULL)
	//{
	//	g_pMeshModel->Release();
	//	g_pMeshModel = NULL;
	//}
	////�}�e���A���̔j��
	//if (g_pBuffMatModel != NULL)
	//{
	//	g_pBuffMatModel->Release();
	//	g_pBuffMatModel = NULL;
	//}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateModel(void)
{

}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawModel(void)
{
	//LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	//D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
	//D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	//D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	////�f�o�C�X�̎擾
	//pDevice = GetDevice();
	////�}�g���b�N�X������
	//D3DXMatrixIdentity(&g_mtxWorldModel);

	////�傫���̔��f
	//D3DXMatrixScaling(&mtxScale, g_scaleModel.x, g_scaleModel.y, g_scaleModel.z);
	//D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxScale);

	////�����̔��f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	//D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	////�ʒu�̔��f
	//D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	//D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	////���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	////���݂̃}�e���A���擾
	//pDevice->GetMaterial(&matDef);

	////�}�e���A���f�[�^�ւ̃|�C���^���擾
	//pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	//{
	//	//�}�e���A���̐ݒ�
	//	pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
	//	//�e�N�X�`��
	//	pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

	//	//���f���`��
	//	g_pMeshModel->DrawSubset(nCntMat);
	//}

	//pDevice->SetMaterial(&matDef);
}

////------------------------------
////�ʒu�擾
////------------------------------
//Model* GetModel(void)
//{
//	return &g_aModel[0];
//}