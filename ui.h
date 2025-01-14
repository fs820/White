//---------------------------------------
//
//�X�R�A�����̒�`�E�錾[ui.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _UI_H_
#define _UI_H_

#include"main.h"

#define UI_TEX "data\\TEXTURE\\�����̂т�.png"
#define UI_TEX2 "data\\TEXTURE\\�����ɏ��.png"
#define UI_TEX3 "data\\TEXTURE\\�Ⴞ.png"
#define UI_MAX (3)//�e�N�X�`����
#define UI_WIDTH (640.0f)//�T�C�Y
#define UI_HEIGHT (128.0f)//�T�C�Y
#define UI_LIFE (120)

typedef struct
{
	D3DXVECTOR3 pos;
	int nLife;
	bool bUse;
}Ui;

//�v���g�^�C�v�錾
void InitUi(void);//�X�R�A�̏���������
void UninitUi(void);//�X�R�A�̏I������
void UpdateUi(void);//�X�R�A�̍X�V����
void DrawUi(void);//�X�R�A�̕`�揈��
void SetUi(int Number);

#endif _UI_H_