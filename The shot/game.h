//---------------------------
//
//ゲーム処理
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//ゲームの状態
typedef enum
{
	GAMESTATE_NONE = 0,//何もしていない状態
	GAMESTATE_NORMAL,//通常状態
	GAMESTATE_END,//終了状態
	GAMESTATE_MAX
}GAMESTATE;

//プロト
void InitGame(void);//タイトルの初期化
void UninitGame(void);//タイトルの終了
void UpdateGame(void);//タイトルの更新
void DrawGame(void);//タイトルの描画
void SetGamestate(GAMESTATE state);
GAMESTATE GetGameState(void);

#endif