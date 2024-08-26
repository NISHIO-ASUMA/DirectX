//---------------------------
//
//�Q�[������
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE = 0,//�������Ă��Ȃ����
	GAMESTATE_NORMAL,//�ʏ���
	GAMESTATE_END,//�I�����
	GAMESTATE_MAX
}GAMESTATE;

//�v���g
void InitGame(void);//�^�C�g���̏�����
void UninitGame(void);//�^�C�g���̏I��
void UpdateGame(void);//�^�C�g���̍X�V
void DrawGame(void);//�^�C�g���̕`��
void SetGamestate(GAMESTATE state);
GAMESTATE GetGameState(void);

#endif