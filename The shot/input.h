//---------------------------
//
//���͏���
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//�L�[�̎��
typedef enum
{
	JOYKEY_UP = 0,//�\���L�[(��)
	JOYKEY_DOWN,//�\���L�[(��)
	JOYKEY_LEFT,//�\���L�[(��)
	JOYKEY_RIGHT,//�\���L�[(�E)

	JOYKEY_START,//�X�^�[�g�L�[�������ꂽ
	JOYKEY_BACK,//�o�b�N�L�[�������ꂽ

	JOYKEY_LS,//L3(L�X�e�B�b�N)�������ꂽ
	JOYKEY_RS,//R3(R�X�e�B�b�N)�������ꂽ

	JOYKEY_LEFT_B,//LB�L�[�������ꂽ
	JOYKEY_RIGHT_B,//RB�L�[�������ꂽ
	JOYKEY_LEFT_TRIGGER,//LT�L�[�������ꂽ
	JOYKEY_RIGHT_TRIGGER,//RT�L�[�������ꂽ

	JOYKEY_A,//A�{�^���������ꂽ
	JOYKEY_B,//B�{�^���������ꂽ
	JOYKEY_X,//X�{�^���������ꂽ
	JOYKEY_Y,//Y�{�^���������ꂽ

	JOYKEY_MAX
}JOYKEY;

//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nkey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);

HRESULT InitJoypad(void);//�W���C�p�b�h�̏�����
void UninitJoypad(void);//�W���C�p�b�h�̏I��
void UpdateJoypad(void);//�W���C�p�b�h�̍X�V
bool JoypadPress(JOYKEY key);//�W���C�p�b�h�̃v���X�����擾
bool JoypadTrigger(JOYKEY key);//�W���C�p�b�h�̃g���K�[�����擾


#endif