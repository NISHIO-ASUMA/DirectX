//---------------------------
//
//�|�[�Y����
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//�|�[�Y���j���[
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,//�Q�[���ɖ߂�
	PAUSE_MENU_RETRY,       //�Q�[������蒼��
	PAUSE_MENU_QUIT,        //�^�C�g���ɖ߂�
	PAUSE_MENU_MAX
}PAUSE_MENU;

//�|�[�Y�̃e�N�X�`���^�C�v
//typedef enum
//{
//	PAUSE_TEXTYPE = 0,
//	PAUSE_TEXTYPE1,
//	PAUSE_TEXTYPE2,
//	PAUSE_TEXTYPE_MAX
//}PAUSE_TEXTYPE;

//�v���g�^�C�v�錾
void InitPause(void);//�|�[�Y��ʂ̏�����
void UninitPause(void);//�|�[�Y��ʂ̏I��
void UpdatePause(void);//�|�[�Y��ʂ̍X�V
void DrawPause(void);//�|�[�Y��ʂ̕`��

#endif