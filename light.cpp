//----------------------------------------
//
//���C�g����[light.cpp]
//Author fuma sato
//
//----------------------------------------

#include"main.h"
#include"light.h"
#include"input.h"
#include"game.h"

//�O���[�o���ϐ��錾
D3DLIGHT9 g_light[LIGHT_MAX];
D3DXVECTOR3 g_vecDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
float g_angle = 0.0f;
bool g_Input = false;
//----------------------
//����������
//----------------------
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCount = 0;

	g_Input = false;

	//���C�g���N���A����
	ZeroMemory(&g_light, sizeof(g_light));

	//------------------------------
	// �f�B���N�V���i�����C�g�̐ݒ�
	//------------------------------
	//���
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	//�g�U��
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_light[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[0].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	//���K��
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[0].Direction = g_vecDir;
	//���C�g�Z�b�g
	pDevice->SetLight(0,&g_light[0]);
	//�L����
	pDevice->LightEnable(0, TRUE);

	//���
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;
	//�g�U��
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_light[1].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[1].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_vecDir = D3DXVECTOR3(-0.9f, -0.8f, 0.8f);
	//���K��
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[1].Direction = g_vecDir;
	//���C�g�Z�b�g
	pDevice->SetLight(1, &g_light[1]);
	//�L����
	pDevice->LightEnable(1, TRUE);

	//���
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;
	//�g�U��
	g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_light[2].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[2].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_vecDir = D3DXVECTOR3(0.1f, -0.4f, 0.8f);
	//���K��
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[2].Direction = g_vecDir;
	//���C�g�Z�b�g
	pDevice->SetLight(2, &g_light[2]);
	//�L����
	pDevice->LightEnable(2, TRUE);

	//���
	g_light[3].Type = D3DLIGHT_DIRECTIONAL;
	//�g�U��
	g_light[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_light[3].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[3].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_vecDir = D3DXVECTOR3(-0.6f, 0.8f, -0.2f);
	//���K��
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[3].Direction = g_vecDir;
	//���C�g�Z�b�g
	pDevice->SetLight(3, &g_light[3]);
	//�L����
	pDevice->LightEnable(3, TRUE);

	//���
	g_light[8].Type = D3DLIGHT_DIRECTIONAL;
	//�g�U��
	g_light[8].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_light[8].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[8].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_vecDir = D3DXVECTOR3(0.7f, -0.1f, -0.2f);
	//���K��
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[8].Direction = g_vecDir;
	//���C�g�Z�b�g
	pDevice->SetLight(8, &g_light[8]);
	//�L����
	pDevice->LightEnable(8, TRUE);

	//���
	g_light[9].Type = D3DLIGHT_DIRECTIONAL;
	//�g�U��
	g_light[9].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_light[9].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[9].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_vecDir = D3DXVECTOR3(0.7f, -0.1f, -0.2f);
	//���K��
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[9].Direction = g_vecDir;
	//���C�g�Z�b�g
	pDevice->SetLight(9, &g_light[9]);
	//�L����
	pDevice->LightEnable(9, TRUE);

	//-----------------------
	// �X�|�b�g���C�g�̐ݒ�
	//-----------------------
	//���
	g_light[4].Type = D3DLIGHT_SPOT;
	//�g�U��
	g_light[4].Diffuse = D3DXCOLOR(10.0f, 10.0f, 10.0f, 1.0f);
	//����
	g_light[4].Ambient = D3DXCOLOR(10.0f, 10.0f, 10.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[4].Specular = D3DXCOLOR(10.0f, 10.0f, 10.0f, 1.0f);
	//�ʒu
	g_light[4].Position = D3DXVECTOR3(0.0f, 2000.0f, 1.0f);
	//����
	g_vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//���K��
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[4].Direction = g_vecDir;
	//�͈�
	g_light[4].Range = 3000.0f;
	//�R�[��������
	g_light[4].Falloff = 0.01f;
	//����������
	g_light[4].Attenuation0 = 0.1f;
	//�R�[���p�x(��)
	g_light[4].Theta = D3DXToRadian(0.0f);
	//�R�[���p�x(�O)
	g_light[4].Phi = D3DXToRadian(360.0f);
	//���C�g�Z�b�g
	pDevice->SetLight(4, &g_light[4]);
	//�L����
	pDevice->LightEnable(4, TRUE);

	//----------------------
	// �|�C���g���C�g�̐ݒ�
	//----------------------
	//���
	g_light[5].Type = D3DLIGHT_POINT;
	//�g�U��
	g_light[5].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_light[5].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[5].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�ʒu
	g_light[5].Position = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
	//�͈�
	g_light[5].Range = 1000.0f;
	//����������(���)
	g_light[5].Attenuation0 = 0.1f;
	//����������(����)
	g_light[5].Attenuation1 = 0.0f;
	//����������(����*2)
	g_light[5].Attenuation2 = 0.0f;
	//���C�g�Z�b�g
	pDevice->SetLight(5, &g_light[5]);
	//�L����
	pDevice->LightEnable(5, TRUE);

	//���
	g_light[6].Type = D3DLIGHT_POINT;
	//�g�U��
	g_light[6].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_light[6].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[6].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�ʒu
	g_light[6].Position = D3DXVECTOR3(-100.0f, 0.0f, 1500.0f);
	//�͈�
	g_light[6].Range = 1000.0f;
	//����������(���)
	g_light[6].Attenuation0 = 0.1f;
	//����������(����)
	g_light[6].Attenuation1 = 0.0f;
	//����������(����*2)
	g_light[6].Attenuation2 = 0.0f;
	//���C�g�Z�b�g
	pDevice->SetLight(6, &g_light[6]);
	//�L����
	pDevice->LightEnable(6, TRUE);

	//���
	g_light[7].Type = D3DLIGHT_POINT;
	//�g�U��
	g_light[7].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//����
	g_light[7].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���ʔ��ˌ�
	g_light[7].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�ʒu
	g_light[7].Position = D3DXVECTOR3(0.0f, 0.0f, 1600.0f);
	//�͈�
	g_light[7].Range = 1000.0f;
	//����������(���)
	g_light[7].Attenuation0 = 0.1f;
	//����������(����)
	g_light[7].Attenuation1 = 0.0f;
	//����������(����*2)
	g_light[7].Attenuation2 = 0.0f;
	//���C�g�Z�b�g
	pDevice->SetLight(7, &g_light[7]);
	//�L����
	pDevice->LightEnable(7, TRUE);
}

//-------------------
//�I������
//-------------------
void UninitLight(void)
{

}

//-------------------
//�X�V����
//-------------------
void UpdateLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (GetKeyboradTrigger(DIK_I))
	{
		g_Input = !g_Input;
	}

	if (g_Input)
	{
		if (GetKeyboradPress(DIK_LEFT))
		{
			g_angle -= 0.01f;
		}

		if (GetKeyboradPress(DIK_RIGHT))
		{
			g_angle += 0.01f;
		}
	}
	else
	{
		//�p�x���X�V
		g_angle += 0.01f;
	}

	//���K��
	if (g_angle > D3DX_PI)
	{
		g_angle -= D3DX_PI * 2.0f;
	}
	else if (g_angle < -D3DX_PI)
	{
		g_angle += D3DX_PI * 2.0f;
	}

	//�x�N�g�����v�Z
	g_vecDir = D3DXVECTOR3(sinf(g_angle) * 0.2f, -0.8f, cosf(g_angle) * -0.4f);

	//���K��
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[0].Direction = g_vecDir;

	//�Z�b�g
	pDevice->SetLight(0, &g_light[0]);

	//�f�B���N�V���i���鉻
	int Time=GetTime();
	g_light[0].Diffuse = D3DXCOLOR(1.0f - (float)((float)Time / (float)TIME_LIMIT) + (((float)Time / (float)TIME_LIMIT) < 0.6f && ((float)Time / (float)TIME_LIMIT) > 0.5f) * 0.2f, 1.0f - (float)((float)Time / (float)TIME_LIMIT), 1.0f - (float)((float)Time / (float)TIME_LIMIT), 1.0f - (float)((float)Time / (float)TIME_LIMIT));
	g_light[1].Diffuse = D3DXCOLOR(1.0f - (float)((float)Time / (float)TIME_LIMIT) + (((float)Time / (float)TIME_LIMIT) < 0.6f && ((float)Time / (float)TIME_LIMIT) > 0.5f) * 0.2f, 1.0f - (float)((float)Time / (float)TIME_LIMIT), 1.0f - (float)((float)Time / (float)TIME_LIMIT), 1.0f - (float)((float)Time / (float)TIME_LIMIT));
	g_light[2].Diffuse = D3DXCOLOR(1.0f - (float)((float)Time / (float)TIME_LIMIT) + (((float)Time / (float)TIME_LIMIT) < 0.6f && ((float)Time / (float)TIME_LIMIT) > 0.5f) * 0.2f, 1.0f - (float)((float)Time / (float)TIME_LIMIT), 1.0f - (float)((float)Time / (float)TIME_LIMIT), 1.0f - (float)((float)Time / (float)TIME_LIMIT));
	g_light[3].Diffuse = D3DXCOLOR(1.0f - (float)((float)Time / (float)TIME_LIMIT) + (((float)Time / (float)TIME_LIMIT) < 0.6f && ((float)Time / (float)TIME_LIMIT) > 0.5f) * 0.2f, 1.0f - (float)((float)Time / (float)TIME_LIMIT), 1.0f - (float)((float)Time / (float)TIME_LIMIT), 1.0f - (float)((float)Time / (float)TIME_LIMIT));
	g_light[8].Diffuse = D3DXCOLOR(1.0f - (float)((float)Time / (float)TIME_LIMIT) + (((float)Time / (float)TIME_LIMIT) < 0.6f && ((float)Time / (float)TIME_LIMIT) > 0.5f) * 0.2f, 1.0f - (float)((float)Time / (float)TIME_LIMIT), 1.0f - (float)((float)Time / (float)TIME_LIMIT), 1.0f - (float)((float)Time / (float)TIME_LIMIT));
	g_light[9].Diffuse = D3DXCOLOR(1.0f - (float)((float)Time / (float)TIME_LIMIT) + (((float)Time / (float)TIME_LIMIT) < 0.6f && ((float)Time / (float)TIME_LIMIT) > 0.5f) * 0.2f, 1.0f - (float)((float)Time / (float)TIME_LIMIT), 1.0f - (float)((float)Time / (float)TIME_LIMIT), 1.0f - (float)((float)Time / (float)TIME_LIMIT));

	static int nCnt = 0;
	if (nCnt % 60 == 0)
	{
		//�x�N�g�����v�Z
		g_vecDir = D3DXVECTOR3((((float)(rand() % 201) / 100) - 1.0f), (((float)(rand() % 201) / 100) - 1.0f), (((float)(rand() % 201) / 100) - 1.0f));

		//���K��
		D3DXVec3Normalize(&g_vecDir, &g_vecDir);
		g_light[9].Direction = g_vecDir;

		//�Z�b�g
		pDevice->SetLight(9, &g_light[9]);
	}
	nCnt++;

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		pDevice->SetLight(nCnt, &g_light[nCnt]);
	}
}

//--------------------------
//�p�x�擾
//--------------------------
float GetLightAngle(void)
{
	return g_angle;
}