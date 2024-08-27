//---------------------------
//
//ポーズ処理
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//ポーズメニュー
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,//ゲームに戻る
	PAUSE_MENU_RETRY,       //ゲームをやり直す
	PAUSE_MENU_QUIT,        //タイトルに戻る
	PAUSE_MENU_MAX
}PAUSE_MENU;

//ポーズのテクスチャタイプ
//typedef enum
//{
//	PAUSE_TEXTYPE = 0,
//	PAUSE_TEXTYPE1,
//	PAUSE_TEXTYPE2,
//	PAUSE_TEXTYPE_MAX
//}PAUSE_TEXTYPE;

//プロトタイプ宣言
void InitPause(void);//ポーズ画面の初期化
void UninitPause(void);//ポーズ画面の終了
void UpdatePause(void);//ポーズ画面の更新
void DrawPause(void);//ポーズ画面の描画

#endif