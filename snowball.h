//---------------------------------------
//
//�|���S���\�������̒�`�E�錾[snowball.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _SNOWBALL_H_
#define _SNOWBALL_H_

#include"main.h"

#define SNOWBALL_TEX "data\\TEXTURE\\yuki000.png"//�e�N�X�`��
#define SNOWBALL_TEX2 "data\\TEXTURE\\yuki001.png"//�e�N�X�`��
#define SNOWBALL_MAX (64)//���̐�
#define SNOWBALL_RADIUS (50.0f)//���a
#define SNOWBALL_WIDTH_DEF (8.0f)//�e�N�X�`���T�C�Y
#define SNOWBALL_HEIGHT_DEF (8.0f)//�e�N�X�`���T�C�Y
#define SNOWBALL_HNUM (64)//H������
#define SNOWBALL_VNUM (64)//V������
#define SNOWBALL_ANG (180.0f)//�����S���ؑ�
#define SNOWBALL_NUM (10)

////����
//#define VT_MAX_SP ((SPHERE_HNUM + 1) * SPHERE_VNUM+1)//���̒��_��*�c�̃��C����(�ɂ𔲂���)+�� (����)
//#define INDEX_SP_NUM (((SPHERE_HNUM+1)*2)*SPHERE_VNUM+(SPHERE_VNUM-2)*2-SPHERE_HNUM)//���̒��_��*2��**�c�̃��C����(�ɂ𔲂���)+�k�ރ|���S��-�ɂ̕s�v��
//#define POLYGON_SP_NUM (SPHERE_HNUM*SPHERE_VNUM*2+(SPHERE_VNUM-2)*4-SPHERE_HNUM)//�S�̂̕���*2*�k�ރ|���S��-�ɂ̕s�v��
//�S��
#define VT_MAX_SB ((SNOWBALL_HNUM + 1) * (SNOWBALL_VNUM-1)+2)//���̒��_��*�c�̃��C����(2�ɂ𔲂���)+2�� (�S��)
#define INDEX_SB_NUM (((SNOWBALL_HNUM+1)*2)*(SNOWBALL_VNUM-2)+(SNOWBALL_VNUM-3)*2+(SNOWBALL_HNUM+2)*2)//���̒��_��*2��**�c�̃��C����(2�ɂ𔲂���)+�k�ރ|���S��+2��
#define POLYGON_SB_NUM (SNOWBALL_HNUM*(SNOWBALL_VNUM-2)*2+(SNOWBALL_VNUM-3)*4+SNOWBALL_HNUM*2)//���̕���*2*�k�ރ|���S��+2��

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	D3DXMATRIX mtxWorld;
	bool bUse;
}SnowBall;

void InitSnowBall(void);//����������
void UninitSnowBall(void);//�I������
void UpdateSnowBall(void);//�X�V����
void DrawSnowBall(void);//�`�揈��
void SetSnowBall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);//�ݒ菈��
SnowBall* GetSnowBall(void);
void CollisionSnowBall(D3DXVECTOR3 pos, float Length);

#endif _SNOWBALL_H_