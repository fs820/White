//---------------------------------------
//
//�|���S���\�������̒�`�E�錾[sphere.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _SPHERE_H_
#define _SPHERE_H_

#include"main.h"

#define SPHERE_TEX "data\\TEXTURE\\sky000.jpg"//�e�N�X�`��
#define SPHERE_TEX2 "data\\TEXTURE\\sky001.jpg"//�e�N�X�`��
#define SPHERE_TEX3 "data\\TEXTURE\\sky002.jpg"//�e�N�X�`��
#define SPHERE_MAX (64)//���̐�
#define SPHERE_RADIUS (5000.0f)//���a
#define SPHERE_WIDTH_DEF (42000.0f)//�e�N�X�`���T�C�Y
#define SPHERE_HEIGHT_DEF (15200.0f)//�e�N�X�`���T�C�Y
#define SPHERE_HNUM (64)//H������
#define SPHERE_VNUM (32)//V������
#define SPHERE_ANG (90.0f)//�����S���ؑ�

//����
#define VT_MAX_SP ((SPHERE_HNUM + 1) * SPHERE_VNUM+1)//���̒��_��*�c�̃��C����(�ɂ𔲂���)+�� (����)
#define INDEX_SP_NUM (((SPHERE_HNUM+1)*2)*SPHERE_VNUM+(SPHERE_VNUM-2)*2-SPHERE_HNUM)//���̒��_��*2��**�c�̃��C����(�ɂ𔲂���)+�k�ރ|���S��-�ɂ̕s�v��
#define POLYGON_SP_NUM (SPHERE_HNUM*SPHERE_VNUM*2+(SPHERE_VNUM-2)*4-SPHERE_HNUM)//�S�̂̕���*2*�k�ރ|���S��-�ɂ̕s�v��

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Sphere;

void InitSphere(void);//����������
void UninitSphere(void);//�I������
void UpdateSphere(void);//�X�V����
void DrawSphere(void);//�`�揈��
void SetSphere(D3DXVECTOR3 pos, D3DXVECTOR3 rot);//�ݒ菈��

#endif _SPHERE_H_