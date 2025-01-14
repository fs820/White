//---------------------------------------
//
//�|���S���\�������̒�`�E�錾[shadow.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _SHADOW_H_
#define _SHADOW_H_

#include"main.h"
#include"game.h"

#define SHADOW_TEX "data\\TEXTURE\\shadow000.jpg"
#define SHADOW_MAX (512)
#define SHADOW_WIDTH (100.0f)
#define SHADOW_HEIGHT (0.0f)
#define SHADOW_Z (100.0f)
#define SHADOW_INA (0.0001f)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Shadow;

void InitShadow(void);//�|���S���̏���������
void UninitShadow(void);//�|���S���̏I������
void UpdateShadow(void);//�|���S���̍X�V����
void DrawShadow(void);//�|���S���̕`�揈��
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos, D3DXVECTOR3 scale, float fSize);
void NullShadow(int nIdxShadow);

#endif _POLYGON_H_