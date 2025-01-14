//----------------------------------------
//
//�|���S���\������[ground.cpp]
//Author fuma sato
//
//----------------------------------------

#include"ground.h"
#include"camera.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGround=NULL;//�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureGround = NULL;
Ground g_aGround[GROUND_MAX];

//----------------------
//�|���S���̏���������
//----------------------
void InitGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	VERTEX_3D* pVtx;//���_���|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGround,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		GROUND_TEX,
		&g_pTextureGround
	);

	int nCntGround;
	for (nCntGround = 0; nCntGround < GROUND_MAX; nCntGround++)
	{
		g_aGround[nCntGround].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGround[nCntGround].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGround[nCntGround].bAlpha = false;
		g_aGround[nCntGround].bUse = false;
	}
	//1��

	g_pVtxBuffGround->Lock(0,0,(void**)&pVtx,0);

	//���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aGround[nCntGround].pos.x - GROUND_WIDTH * 0.5f, g_aGround[nCntGround].pos.y + GROUND_HEIGHT, g_aGround[nCntGround].pos.z + GROUND_Z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(g_aGround[nCntGround].pos.x + GROUND_WIDTH * 0.5f, g_aGround[nCntGround].pos.y + GROUND_HEIGHT, g_aGround[nCntGround].pos.z + GROUND_Z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(g_aGround[nCntGround].pos.x - GROUND_WIDTH * 0.5f, g_aGround[nCntGround].pos.y, g_aGround[nCntGround].pos.z - GROUND_Z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(g_aGround[nCntGround].pos.x + GROUND_WIDTH * 0.5f, g_aGround[nCntGround].pos.y, g_aGround[nCntGround].pos.z - GROUND_Z * 0.5f);

	//nor
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(GROUND_WIDTH / GROUND_WIDTH_DEF, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, GROUND_Z / GROUND_Z_DEF);
	pVtx[3].tex = D3DXVECTOR2(GROUND_WIDTH / GROUND_WIDTH_DEF, GROUND_Z / GROUND_Z_DEF);

	g_pVtxBuffGround->Unlock();
}

//-------------------
//�|���S���I������
//-------------------
void UninitGround(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGround != NULL)
	{
		g_pTextureGround->Release();
		g_pTextureGround = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGround != NULL)
	{
		g_pVtxBuffGround->Release();
		g_pVtxBuffGround = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateGround(void)
{

}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�}�g���b�N�X

    //�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntGround;
	for (nCntGround = 0; nCntGround < GROUND_MAX; nCntGround++)
	{
		if (g_aGround[nCntGround].bUse && !g_aGround[nCntGround].bAlpha)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aGround[nCntGround].mtxWorld);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aGround[nCntGround].rot.y, g_aGround[nCntGround].rot.x, g_aGround[nCntGround].rot.z);
			D3DXMatrixMultiply(&g_aGround[nCntGround].mtxWorld, &g_aGround[nCntGround].mtxWorld, &mtxRot);

			//�ʒu�̌v�Z
			D3DXMatrixTranslation(&mtxTrans, g_aGround[nCntGround].pos.x, g_aGround[nCntGround].pos.y, g_aGround[nCntGround].pos.z);
			D3DXMatrixMultiply(&g_aGround[nCntGround].mtxWorld, &g_aGround[nCntGround].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aGround[nCntGround].mtxWorld);

			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffGround, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureGround);

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

//----------
//�ݒ�
//----------
void SetGround(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntGround;
	for (nCntGround = 0; nCntGround < GROUND_MAX; nCntGround++)
	{
		if (!g_aGround[nCntGround].bUse)
		{
			g_aGround[nCntGround].pos = pos;
			g_aGround[nCntGround].rot = rot;
			g_aGround[nCntGround].bAlpha = false;
			g_aGround[nCntGround].bUse = true;
			break;
		}
	}
}