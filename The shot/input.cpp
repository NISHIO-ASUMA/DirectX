
//---------------------------
//
//入力処理
//Author:NISHIO ASUMA
//
//---------------------------
#include "input.h"
#include "player.h"

//マクロ定義
#define NUM_KEY_MAX (256)//キーの最大数

//グローバル変数
LPDIRECTINPUT8 g_pInput = NULL;//Directinputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//入力デバイスへのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];//キーボードのプレス情報
BYTE g_aOldState[NUM_KEY_MAX];//過去の入力内容を保存
XINPUT_STATE g_joyKeyState;//ジョイパッドのプレス情報
XINPUT_STATE g_OldKeyState;//ジョイパッドのトリガー情報

//=======================
//キーボードの初期化処理
//=======================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&g_pInput,
		NULL)))
	{
		return E_FAIL;
	}
	//入力デバイス生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;


	}
	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//======================
//キーボードの終了処理
//======================
void UninitKeyboard(void)
{
	//入力デバイス(キーボード)の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();//アクセス権の破棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//======================
//キーボードの更新処理
//======================
void UpdateKeyboard(void)
{

	BYTE aKeyState[NUM_KEY_MAX];//キーボードの入力情報
	int nCntkey;
	for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
	{
		g_aOldState[nCntkey] = g_aKeyState[nCntkey];//キーボードのプレス情報を保存
	}

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			g_aKeyState[nCntkey] = aKeyState[nCntkey];//キーボードのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();//キーボードのアクセス権を獲得
	}
}
//=============================
//キーボードのプレス情報を取得
//=============================
bool GetKeyboardPress(int nkey)
{
	return (g_aKeyState[nkey] & 0x80) ? true : false;//3項演算子を使用
}
//=============================
//キーボードをワンタップ
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
//キーボードを長押し(チャージ攻撃)
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
//キーボードの継続処理(連射処理)
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
//ジョイパッドの初期化処理
//==============================
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//Xinputのステートを設定(有効化)
	XInputEnable(true);

	return S_OK;
}
//==============================
//ジョイパッドの終了
//==============================
void UninitJoypad(void)
{
	//Xinputのステートを設定(無効化)
	XInputEnable(false);
}
//==============================
//ジョイパッドの更新
//==============================
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;//入力情報を取得

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		g_joyKeyState = joykeyState;//ジョイパッドのプレス情報を保存
	}
}
//==============================
//プレス情報を取得
//==============================
bool JoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//==============================
//トリガー情報を取得
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