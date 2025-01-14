//---------------------------------------
//
//�X�R�A����[Life.cpp]
//Author fuma sato
//
//---------------------------------------

#include"Life.h"
#include"camera.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;//�o�b�t�@�̃|�C���^
Life g_aLife[LIFE_MAX];
//-------------------------
//�|���S���̏���������
//-------------------------
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	VERTEX_3D* pVtx;//���_���|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�o�b�t�@�[�̐ݒ�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL
	);

	for (int nCnt = 0; nCnt < LIFE_MAX; nCnt++)
	{
		g_aLife[nCnt].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aLife[nCnt].scale = D3DXVECTOR3(1.0f, 1.0f,1.0f);
		g_aLife[nCnt].bUse = false;
	}

	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

	//���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(-LIFE_WIDTH * 0.5f, LIFE_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(LIFE_WIDTH * 0.5f, LIFE_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-LIFE_WIDTH * 0.5f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(LIFE_WIDTH * 0.5f, 0.0f, 0.0f);

	//nor
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	//�e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffLife->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
}

//--------------------------
//�|���S���̏I������
//--------------------------
void UninitLife(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//--------------------------
//�|���S���̍X�V����
//--------------------------
void UpdateLife(void)
{

}

//----------------------------
//�|���S���̕`�揈��
//----------------------------
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxScale, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�e�X�g�I�t
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCnt = 0; nCnt < LIFE_MAX; nCnt++)
	{
		if (g_aLife[nCnt].bUse)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aLife[nCnt].mtxWorld);

			//�r���[�}�g���b�N�X�擾
			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�J�����̋t�s���ݒ�
			g_aLife[nCnt].mtxWorld._11 = mtxView._11;
			g_aLife[nCnt].mtxWorld._12 = mtxView._21;
			g_aLife[nCnt].mtxWorld._13 = mtxView._31;
			g_aLife[nCnt].mtxWorld._21 = mtxView._12;
			g_aLife[nCnt].mtxWorld._22 = mtxView._22;
			g_aLife[nCnt].mtxWorld._23 = mtxView._32;
			g_aLife[nCnt].mtxWorld._31 = mtxView._13;
			g_aLife[nCnt].mtxWorld._32 = mtxView._23;
			g_aLife[nCnt].mtxWorld._33 = mtxView._33;

			//�傫���̔��f
			D3DXMatrixScaling(&mtxScale, g_aLife[nCnt].scale.x, g_aLife[nCnt].scale.y, g_aLife[nCnt].scale.z);
			D3DXMatrixMultiply(&g_aLife[nCnt].mtxWorld, &g_aLife[nCnt].mtxWorld, &mtxScale);

			//�ʒu�̌v�Z
			D3DXMatrixTranslation(&mtxTrans, g_aLife[nCnt].pos.x, g_aLife[nCnt].pos.y, g_aLife[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aLife[nCnt].mtxWorld, &g_aLife[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aLife[nCnt].mtxWorld);

			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//�w�i�̕`��
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				0,//�n�܂�̔ԍ�
				2//�|���S���̌�
			);
		}
	}

	//Z�e�X�g�I��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//-----------------------
//�Q�[�W�Z�b�g
//-----------------------
int LinkLife(void)
{
	for (int nCnt = 0; nCnt < LIFE_MAX; nCnt++)
	{
		if (!g_aLife[nCnt].bUse)
		{
			g_aLife[nCnt].bUse = true;
			return nCnt;
		}
	}

	return -1;
}

//-----------------------
//�Q�[�W�Z�b�g
//-----------------------
void NullLife(int Indx)
{
	g_aLife[Indx].bUse = false;
}

//-----------------------
//�Q�[�W�X�V
//-----------------------
void SetLife(D3DXVECTOR3 pos, float Life, int Indx)
{
	if (g_aLife[Indx].bUse)
	{
		Camera* pCamera = GetCamera();

		g_aLife[Indx].pos = pos;
		g_aLife[Indx].pos.x -= sinf(pCamera->rot.y + D3DX_PI * 0.5f) * LIFE_WIDTH * (1.0f - Life) * 0.5f;
		g_aLife[Indx].pos.y += LIFE_SPACE;
		g_aLife[Indx].pos.z -= cosf(pCamera->rot.y + D3DX_PI * 0.5f) * LIFE_WIDTH * (1.0f - Life) * 0.5f;
		g_aLife[Indx].scale.x = Life;
		g_aLife[Indx].scale.x = max(0.0f, min(1.0f, g_aLife[Indx].scale.x));
		g_aLife[Indx].scale.z = Life;
		g_aLife[Indx].scale.z = max(0.0f, min(1.0f, g_aLife[Indx].scale.x));
	}
}