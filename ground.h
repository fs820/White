//---------------------------------------
//
//�|���S���\�������̒�`�E�錾[ground.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _GROUND_H_
#define _GROUND_H_

#include"main.h"
#include"game.h"

#define GROUND_TEX "data\\TEXTURE\\field000.jpg"
#define GROUND_MAX (64)
#define GROUND_WIDTH (1000.0f)
#define GROUND_HEIGHT (0.0f)
#define GROUND_Z (1000.0f)
#define GROUND_WIDTH_DEF (45.4f)
#define GROUND_HEIGHT_DEF (0.0f)
#define GROUND_Z_DEF (34.0f)
#define GROUND_ALPHA (0.3f)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bAlpha;
	bool bUse;
}Ground;

void InitGround(void);//�|���S���̏���������
void UninitGround(void);//�|���S���̏I������
void UpdateGround(void);//�|���S���̍X�V����
void DrawGround(void);//�|���S���̕`�揈��
void SetGround(D3DXVECTOR3 pos,D3DXVECTOR3 rot);

#endif _GROUND_H_