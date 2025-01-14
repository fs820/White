//---------------------------------------
//
//�e�\������[snow.cpp]
//Author fuma sato
//
//---------------------------------------

#include"snow.h"
#include"effect.h"
#include"game.h"

//�e�\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 scale;//�X�P�[��
	bool bUse;//�g�p���Ă��邩�ǂ���
}SNOW;

SNOW g_Snow;
//-----------------
//�e�̏���������
//-----------------
void InitSnow(void)
{
	g_Snow.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Snow.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Snow.bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
}

//----------------
//�e�̏I������
//----------------
void UninitSnow(void)
{

}

//----------------
//�e�̍X�V����
//----------------
void UpdateSnow(void)
{
	if (g_Snow.bUse == true)
	{//�e���g�p����Ă���

		for (int nCnt = 0; nCnt < SNOW_NUM; nCnt++)
		{
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), move = D3DXVECTOR3(0.0f, 0.0f, 0.0f), scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f), dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			float fangle = 0.0f, fspeed = 0.0f, length = 0.0f;
			pos = g_Snow.pos;
			float RotRand = (((float)(rand() % 201) / 100.0f) - 1.0f) * D3DX_PI, LengthRand = (float)(rand() % (SNOW_SPASE * 10) + 1) / 10.0f;
			pos += D3DXVECTOR3(sinf(RotRand) * LengthRand, 0.0f, cosf(RotRand) * LengthRand);
			fspeed = (float)(rand() % 50) / 10.0f + 1.0f;
			dir.x = (float)(rand() % 201 - 100) / 100.0f;
			dir.y = (float)(rand() % 201 - 200) / 100.0f;
			dir.z = (float)(rand() % 201 - 100) / 100.0f;
			D3DXVec3Normalize(&dir, &dir);
			move = dir * fspeed;
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			scale = g_Snow.scale;
			int nLife = (int)(pos.y / -move.y) * FRAME;

			SetEffect(pos, move, col, scale, nLife, EFFECT_TYPE_NORMAL);
		}
	}
}

//-------------------
//���ʏ�e
//-------------------
void SetSnow(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	if (g_Snow.bUse == false)
	{//�e���g�p����Ă��Ȃ�
		g_Snow.pos = pos;
		g_Snow.scale = scale;
		g_Snow.bUse = true;
	}
	else
	{
		g_Snow.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Snow.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Snow.bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}
}