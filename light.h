//---------------------------------------
//
//���C�g�̒�`�E�錾[light.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include"main.h"

#define LIGHT_MAX (16)

void InitLight(void);//����������
void UninitLight(void);//�I������
void UpdateLight(void);//�X�V����
float GetLightAngle(void);

#endif _LIGHT_H_