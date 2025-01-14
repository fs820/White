//---------------------------------------
//
//�X�R�A����[ui.cpp]
//Author fuma sato
//
//---------------------------------------

#include"ui.h"

LPDIRECT3DTEXTURE9 g_pTextureUi[UI_MAX] = { NULL };//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUi = NULL;//�o�b�t�@�̃|�C���^
Ui g_aUi[UI_MAX];
//-------------------------
//�|���S���̏���������
//-------------------------
void InitUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	VERTEX_2D* pVtx;//���_���|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�o�b�t�@�[�̐ݒ�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * UI_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUi,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		UI_TEX,
		&g_pTextureUi[0]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		UI_TEX2,
		&g_pTextureUi[1]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		UI_TEX3,
		&g_pTextureUi[2]
	);

	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		g_aUi[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f,0.0f);
		g_aUi[nCnt].nLife = UI_LIFE;
		g_aUi[nCnt].bUse = false;
	}

	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		//���W�ݒ�
		pVtx[0].pos.x = g_aUi[nCnt].pos.x - UI_WIDTH * 0.5f;
		pVtx[0].pos.y = g_aUi[nCnt].pos.y - UI_HEIGHT * 0.5f;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aUi[nCnt].pos.x + UI_WIDTH * 0.5f;
		pVtx[1].pos.y = g_aUi[nCnt].pos.y - UI_HEIGHT * 0.5f;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aUi[nCnt].pos.x - UI_WIDTH * 0.5f;
		pVtx[2].pos.y = g_aUi[nCnt].pos.y + UI_HEIGHT * 0.5f;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aUi[nCnt].pos.x + UI_WIDTH * 0.5f;
		pVtx[3].pos.y = g_aUi[nCnt].pos.y + UI_HEIGHT * 0.5f;
		pVtx[3].pos.z = 0.0f;

		//rhw
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += VT_MAX;
	}

	g_pVtxBuffUi->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
}

//--------------------------
//�|���S���̏I������
//--------------------------
void UninitUi(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		if (g_pTextureUi[nCnt] != NULL)
		{
			g_pTextureUi[nCnt]->Release();
			g_pTextureUi[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffUi != NULL)
	{
		g_pVtxBuffUi->Release();
		g_pVtxBuffUi = NULL;
	}
}

//--------------------------
//�|���S���̍X�V����
//--------------------------
void UpdateUi(void)
{
	VERTEX_2D* pVtx;//���_���|�C���^

	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		if (g_aUi[nCnt].bUse)
		{
			g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCnt * VT_MAX;//�|���S��1���i�߂�
			BYTE alpha = (BYTE)(((float)g_aUi[nCnt].nLife) / ((float)UI_LIFE) * 255.0f);
			pVtx[0].col = (pVtx[0].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[1].col = (pVtx[1].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[2].col = (pVtx[2].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[3].col = (pVtx[3].col & 0x00FFFFFF) | (alpha << 24);

			g_pVtxBuffUi->Unlock();//�o�b�t�@�̃A�����b�N

			g_aUi[nCnt].nLife--;

			if (g_aUi[nCnt].nLife <= 0)
			{
				g_aUi[nCnt].bUse = false;
			}
		}
	}
}

//----------------------------
//�|���S���̕`�揈��
//----------------------------
void DrawUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@
	pDevice->SetStreamSource(0, g_pVtxBuffUi, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		if (g_aUi[nCnt].bUse)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureUi[nCnt]);

			//�w�i�̕`��
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				VT_MAX * nCnt,//�n�܂�̔ԍ�
				2//�|���S���̌�
			);
		}
	}
}

//-----------------------
//�^�C���X�V
//-----------------------
void SetUi(int Number)
{
	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		if (!g_aUi[nCnt].bUse)
		{
			g_aUi[Number].nLife = UI_LIFE;
			g_aUi[Number].bUse = true;
		}
	}
}