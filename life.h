//---------------------------------------
//
//�̗̓Q�[�W�̒�`�E�錾[life.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _LIFE_H_
#define _LIFE_H_

#include"main.h"

#define LIFE_MAX (64)
#define LIFE_WIDTH (160.0f)//�T�C�Y
#define LIFE_HEIGHT (10.0f)//�T�C�Y
#define LIFE_SPACE (50.0f)//����

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 scale;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Life;

//�v���g�^�C�v�錾
void InitLife(void);//�X�R�A�̏���������
void UninitLife(void);//�X�R�A�̏I������
void UpdateLife(void);//�X�R�A�̍X�V����
void DrawLife(void);//�X�R�A�̕`�揈��
int LinkLife(void);
void NullLife(int Indx);
void SetLife(D3DXVECTOR3 pos, float Life, int Indx);//�ݒ�

#endif _LIFE_H_
