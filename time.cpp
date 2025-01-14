//---------------------------------------
//
//�X�R�A����[time.cpp]
//Author fuma sato
//
//---------------------------------------

#include"Time.h"
#include"game.h"

LPDIRECT3DTEXTURE9 g_pTextureTime[TIME_MAX] = { NULL };//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;//�o�b�t�@�̃|�C���^
Time g_aTime[TIME_MAX];
//-------------------------
//�|���S���̏���������
//-------------------------
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	VERTEX_2D* pVtx;//���_���|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�o�b�t�@�[�̐ݒ�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * TIME_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TIME_TEX,
		&g_pTextureTime[0]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TIME_TEX2,
		&g_pTextureTime[1]
	);

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		g_aTime[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, TIME_HEIGHT / 2, 0.0f);
		g_aTime[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * -0.57f);
	}

	g_aTime[0].fLength = sqrtf(TIME_WIDTH * TIME_WIDTH + TIME_HEIGHT * TIME_HEIGHT) / 2.0f;//�Ίp���̒���
	g_aTime[0].fAngle = atan2f(TIME_WIDTH, TIME_HEIGHT);//�p�x
	g_aTime[1].fLength = sqrtf((TIME_WIDTH2 * 0.5f) * (TIME_WIDTH2 * 0.5f) + TIME_HEIGHT2 * TIME_HEIGHT2);//�Ίp���̒���
	g_aTime[1].fAngle = atan2f(TIME_WIDTH2 * 0.5f, TIME_HEIGHT2);//�p�x

	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

	//���W�ݒ�
	pVtx[0].pos.x = g_aTime[0].pos.x + sinf(g_aTime[0].rot.z - (D3DX_PI - g_aTime[0].fAngle)) * g_aTime[0].fLength;
	pVtx[0].pos.y = g_aTime[0].pos.y + cosf(g_aTime[0].rot.z - (D3DX_PI - g_aTime[0].fAngle)) * g_aTime[0].fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aTime[0].pos.x + sinf(g_aTime[0].rot.z - (D3DX_PI + g_aTime[0].fAngle)) * g_aTime[0].fLength;
	pVtx[1].pos.y = g_aTime[0].pos.y + cosf(g_aTime[0].rot.z - (D3DX_PI + g_aTime[0].fAngle)) * g_aTime[0].fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aTime[0].pos.x + sinf(g_aTime[0].rot.z - g_aTime[0].fAngle) * g_aTime[0].fLength;
	pVtx[2].pos.y = g_aTime[0].pos.y + cosf(g_aTime[0].rot.z - g_aTime[0].fAngle) * g_aTime[0].fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aTime[0].pos.x + sinf(g_aTime[0].rot.z + g_aTime[0].fAngle) * g_aTime[0].fLength;
	pVtx[3].pos.y = g_aTime[0].pos.y + cosf(g_aTime[0].rot.z + g_aTime[0].fAngle) * g_aTime[0].fLength;
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

	//���W�ݒ�
	pVtx[0].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z - (D3DX_PI - g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[0].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z - (D3DX_PI - g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z - (D3DX_PI + g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[1].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z - (D3DX_PI + g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z - D3DX_PI * 0.5f) * g_aTime[1].fLength;
	pVtx[2].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z - D3DX_PI * 0.5f) * g_aTime[1].fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z + D3DX_PI * 0.5f) * g_aTime[1].fLength;
	pVtx[3].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z + D3DX_PI * 0.5f) * g_aTime[1].fLength;
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

	g_pVtxBuffTime->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
}

//--------------------------
//�|���S���̏I������
//--------------------------
void UninitTime(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		if (g_pTextureTime[nCnt] != NULL)
		{
			g_pTextureTime[nCnt]->Release();
			g_pTextureTime[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//--------------------------
//�|���S���̍X�V����
//--------------------------
void UpdateTime(void)
{

}

//----------------------------
//�|���S���̕`�揈��
//----------------------------
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTime[nCnt]);

		//�w�i�̕`��
		pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,//�^�C�v
			VT_MAX * nCnt,//�n�܂�̔ԍ�
			2//�|���S���̌�
		);
	}
}

//-----------------------
//�^�C���X�V
//-----------------------
void SetTime(float Time)
{
	VERTEX_2D* pVtx;//���_���|�C���^

	Time /= (float)TIME_LIMIT;

	g_aTime[1].rot.z = -(D3DX_PI * 2.0f) * Time;

	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N
	pVtx += VT_MAX;

	//���W�ݒ�
	pVtx[0].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z - (D3DX_PI - g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[0].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z - (D3DX_PI - g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z - (D3DX_PI + g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[1].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z - (D3DX_PI + g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z - D3DX_PI * 0.5f) * TIME_WIDTH2 * 0.5f;
	pVtx[2].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z - D3DX_PI * 0.5f) * TIME_WIDTH2 * 0.5f;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z + D3DX_PI * 0.5f) * TIME_WIDTH2 * 0.5f;
	pVtx[3].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z + D3DX_PI * 0.5f) * TIME_WIDTH2 * 0.5f;
	pVtx[3].pos.z = 0.0f;

	g_pVtxBuffTime->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
}