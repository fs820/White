//------------------------------------------
//
//�|�[�Y�����̒�`�E�錾[pause.h]
//Author fuma sato
//
//------------------------------------------

#ifndef _PAUSE_H_
#define _PAUSE_H_

#include"main.h"
#include"sound.h"

#define TEXTURE_RESTART "data\\TEXTURE\\Restart.png"
#define TEXTURE_RETRY "data\\TEXTURE\\Retry.png"
#define TEXTURE_BACKTITLE "data\\TEXTURE\\Back to Title.png"
#define TEXTURE_EXIT "data\\TEXTURE\\Exit.png"

void InitPause(void);//�Q�[���̏���������
void UninitPause(void);//�Q�[���̏I������
void UpdatePause(void);//�Q�[���̍X�V����
void DrawPause(void);//�Q�[���̕`�揈��
void Pause(SOUND_LABEL label);//�|�[�Y
bool bPause(void);//�|�[�Y���ǂ���

#endif _PAUSE_H_
