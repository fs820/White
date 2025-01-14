//---------------------------------------
//
//�|���S���\�������̒�`�E�錾[wall.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _WALL_H_
#define _WALL_H_

#include"main.h"
#include"game.h"

#define WALL_TEX "data\\TEXTURE\\wall000.jpg"
#define WALL_MAX (64)
#define WALL_WIDTH (1000.0f)
#define WALL_HEIGHT (1000.0f)
#define WALL_Z (0.0f)
#define WALL_WIDTH_DEF (50.0f)
#define WALL_HEIGHT_DEF (50.0f)
#define WALL_Z_DEF (0.0f)
#define WALL_ALPHA (0.3f)
#define WALL_COLL_SPASE (0.0f)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	bool bAlpha;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Wall;

void InitWall(void);//�|���S���̏���������
void UninitWall(void);//�|���S���̏I������
void UpdateWall(void);//�|���S���̍X�V����
void DrawWall(void);//�|���S���̕`�揈��
void DrawAlphaWall(void);//����
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
Wall* GetWall(void);
void CollisionWall(void);

#endif _POLYGON_H_