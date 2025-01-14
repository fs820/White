//---------------------------------------
//
//���C�������̒�`�E�錾[line.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _LINE_H_
#define _LINE_H_

#include"main.h"
#include"game.h"

#define LINE_TEX "data\\TEXTURE\\White.jpg"
#define LINE_MAX (128)
#define LINE_WIDTH (1.0f)
#define LINE_HEIGHT (0.0f)
#define LINE_Z (1.0f)
#define LINE_WIDTH_DEF (4.54f)
#define LINE_HEIGHT_DEF (0.0f)
#define LINE_Z_DEF (3.4f)
#define LINE_ALPHA (0.001f)
#define LINE_XNUM (16)
#define LINE_ZNUM (16)
#define VT_MAX_LINE ((LINE_XNUM + 1) * (LINE_ZNUM + 1))
#define INDEX_NUM_LINE (((LINE_XNUM+1)*2)*LINE_ZNUM+(LINE_ZNUM-1)*2)
#define POLYGON_NUM_LINE (LINE_XNUM*LINE_ZNUM*2+(LINE_ZNUM-1)*4)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	float fLength;
	float fAngle;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Line;

void InitLine(void);//�|���S���̏���������
void UninitLine(void);//�|���S���̏I������
void UpdateLine(void);//�|���S���̍X�V����
void DrawLine(void);//�|���S���̕`�揈��
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);
void HitLine(void);

#endif _LINE_H_