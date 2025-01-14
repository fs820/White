//---------------------------------------
//
//�X�R�A�����̒�`�E�錾[time.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _TIME_H_
#define _TIME_H_

#include"main.h"

#define TIME_TEX "data\\TEXTURE\\Time.png"
#define TIME_TEX2 "data\\TEXTURE\\TimeMaster.png"
#define TIME_MAX (2)//�e�N�X�`����
#define TIME_WIDTH (160.0f)//�T�C�Y
#define TIME_HEIGHT (120.0f)//�T�C�Y
#define TIME_WIDTH2 (75.0f)//�T�C�Y
#define TIME_HEIGHT2 (75.0f)//�T�C�Y

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fLength;
	float fAngle;
}Time;

//�v���g�^�C�v�錾
void InitTime(void);//�X�R�A�̏���������
void UninitTime(void);//�X�R�A�̏I������
void UpdateTime(void);//�X�R�A�̍X�V����
void DrawTime(void);//�X�R�A�̕`�揈��
void SetTime(float Time);

#endif _Time_H_
