//---------------------------------------
//
//�|���S���\�������̒�`�E�錾[meshfield.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include"main.h"
#include"game.h"

#define MESHFIELD_TEX "data\\TEXTURE\\field000.jpg"
#define MESHFIELD_TEX2 "data\\TEXTURE\\yuki002.png"
#define MESHFIELD_MAX (64)
#define MESHFIELD_TEX_MAX (2)
#define MESHFIELD_WIDTH (10000.0f)
#define MESHFIELD_HEIGHT (0.0f)
#define MESHFIELD_Z (10000.0f)
#define MESHFIELD_WIDTH_DEF (4.54f)
#define MESHFIELD_HEIGHT_DEF (0.0f)
#define MESHFIELD_Z_DEF (3.4f)
#define MESHFIELD_ALPHA (0.001f)
#define MESHFIELD_XNUM (1)
#define MESHFIELD_ZNUM (1)
#define VT_MAX_MESH ((MESHFIELD_XNUM + 1) * (MESHFIELD_ZNUM + 1))
#define INDEX_NUM (((MESHFIELD_XNUM+1)*2)*MESHFIELD_ZNUM+(MESHFIELD_ZNUM-1)*2)
#define POLYGON_NUM (MESHFIELD_XNUM*MESHFIELD_ZNUM*2+(MESHFIELD_ZNUM-1)*4)
#define RAND_MESH (150)
#define RAND_INA (0.01f)
#define RAND_TIME (300)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bAlpha;
	bool bUse;
}MeshField;

void InitMeshField(void);//�|���S���̏���������
void UninitMeshField(void);//�|���S���̏I������
void UpdateMeshField(void);//�|���S���̍X�V����
void DrawMeshField(void);//�|���S���̕`�揈��
void SetMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
MeshField* GetMeshField(void);
void CollisionMeshField(void);

#endif _MESHFIELD_H_