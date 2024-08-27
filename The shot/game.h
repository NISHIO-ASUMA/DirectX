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
void InitGame(void);//�Q�[���̏�����
void UninitGame(void);//�Q�[���̏I��
void UpdateGame(void);//�Q�[���̍X�V
void DrawGame(void);//�Q�[���̕`��
void SetGamestate(GAMESTATE state);
GAMESTATE GetGameState(void);
void SetEnablePause(bool bPause);//�|�[�Y���j���[

#endif