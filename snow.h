//---------------------------------------
//
//�p�[�e�B�N���\�������̒�`�E�錾[snow.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _SNOW_H_
#define _SNOW_H_

#include"main.h"

#define SNOW_NUM (5)//�t���[��������
#define SNOW_SPASE (3000)

void InitSnow(void);//�p�[�e�B�N���̏���������
void UninitSnow(void);//�p�[�e�B�N���̏I������
void UpdateSnow(void);//�p�[�e�B�N���̍X�V����
void SetSnow(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�p�[�e�B�N���ݒ�

#endif _SNOW_H_