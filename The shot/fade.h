//---------------------------
//
//�t�F�[�h����
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

//�t�F�[�h�̏��
typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FAFE_MAX
}FADE;

//�v���g
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modeNext);
FADE GetFade(void);

#endif