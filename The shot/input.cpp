
//---------------------------
//
//���͏���
//Author:NISHIO ASUMA
//
//---------------------------
#include "input.h"
#include "player.h"

//�}�N����`
#define NUM_KEY_MAX (256)//�L�[�̍ő吔

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;//Directinput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//���̓f�o�C�X�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̃v���X���
BYTE g_aOldState[NUM_KEY_MAX];//�ߋ��̓��͓��e��ۑ�
XINPUT_STATE g_joyKeyState;//�W���C�p�b�h�̃v���X���
XINPUT_STATE g_OldKeyState;//�W���C�p�b�h�̃g���K�[���

//=======================
//�L�[�{�[�h�̏���������
//=======================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&g_pInput,
		NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X����
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;


	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//======================
//�L�[�{�[�h�̏I������
//======================
void UninitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();//�A�N�Z�X���̔j��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//======================
//�L�[�{�[�h�̍X�V����
//======================
void UpdateKeyboard(void)
{

	BYTE aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏��
	int nCntkey;
	for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
	{
		g_aOldState[nCntkey] = g_aKeyState[nCntkey];//�L�[�{�[�h�̃v���X����ۑ�
	}

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			g_aKeyState[nCntkey] = aKeyState[nCntkey];//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();//�L�[�{�[�h�̃A�N�Z�X�����l��
	}
}
//=============================
//�L�[�{�[�h�̃v���X�����擾
//=============================
bool GetKeyboardPress(int nkey)
{
	return (g_aKeyState[nkey] & 0x80) ? true : false;//3�����Z�q���g�p
}
//=============================
//�L�[�{�[�h�������^�b�v
//=============================
bool KeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//================================
//�L�[�{�[�h�𒷉���(�`���[�W�U��)
//================================
bool KeyboardRelease(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//===============================
//�L�[�{�[�h�̌p������(�A�ˏ���)
//===============================
bool KeyboardRepeat(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//==============================
//�W���C�p�b�h�̏���������
//==============================
HRESULT InitJoypad(void)
{
	//�������̃N���A
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//Xinput�̃X�e�[�g��ݒ�(�L����)
	XInputEnable(true);

	return S_OK;
}
//==============================
//�W���C�p�b�h�̏I��
//==============================
void UninitJoypad(void)
{
	//Xinput�̃X�e�[�g��ݒ�(������)
	XInputEnable(false);
}
//==============================
//�W���C�p�b�h�̍X�V
//==============================
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;//���͏����擾

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		g_joyKeyState = joykeyState;//�W���C�p�b�h�̃v���X����ۑ�
	}
}
//==============================
//�v���X�����擾
//==============================
bool JoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//==============================
//�g���K�[�����擾
//==============================
bool JoypadTrigger(JOYKEY key)
{
	bool Trigger = false;
	if (g_joyKeyState.Gamepad.wButtons == (0x01 << key))
	{
		if (g_joyKeyState.Gamepad.wButtons != g_OldKeyState.Gamepad.wButtons)
		{
			Trigger = true;
		}
	}
	return Trigger;
}