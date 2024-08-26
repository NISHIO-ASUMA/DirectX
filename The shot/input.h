//---------------------------
//
//入力処理
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//キーの種類
typedef enum
{
	JOYKEY_UP = 0,//十字キー(上)
	JOYKEY_DOWN,//十字キー(下)
	JOYKEY_LEFT,//十字キー(左)
	JOYKEY_RIGHT,//十字キー(右)

	JOYKEY_START,//スタートキーが押された
	JOYKEY_BACK,//バックキーが押された

	JOYKEY_LS,//L3(Lスティック)が押された
	JOYKEY_RS,//R3(Rスティック)が押された

	JOYKEY_LEFT_B,//LBキーが押された
	JOYKEY_RIGHT_B,//RBキーが押された
	JOYKEY_LEFT_TRIGGER,//LTキーが押された
	JOYKEY_RIGHT_TRIGGER,//RTキーが押された

	JOYKEY_A,//Aボタンが押された
	JOYKEY_B,//Bボタンが押された
	JOYKEY_X,//Xボタンが押された
	JOYKEY_Y,//Yボタンが押された

	JOYKEY_MAX
}JOYKEY;

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nkey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);

HRESULT InitJoypad(void);//ジョイパッドの初期化
void UninitJoypad(void);//ジョイパッドの終了
void UpdateJoypad(void);//ジョイパッドの更新
bool JoypadPress(JOYKEY key);//ジョイパッドのプレス情報を取得
bool JoypadTrigger(JOYKEY key);//ジョイパッドのトリガー情報を取得


#endif