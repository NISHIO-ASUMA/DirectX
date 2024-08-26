//---------------------------
//
//リザルト処理
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "input.h"

//列挙型(種類)
typedef enum
{
	RESULT_FIRST = 0,//1つ目のタイトル
	RESULT_SECOND,//2つ目のタイトル
	RESULT_MAX
}RESULT;

//列挙型(状態)
typedef enum
{
	RESULT_NONE = 0,//タイトル状態(通常状態)
	RESULT_FLASH,//点滅状態
	RESULTSTATE_MAX
}RESULTSTATE;

//プロト
void InitResult(void);//リザルトの初期化
void UninitResult(void);//リザルトの終了
void UpdateResult(void);//リザルトの更新
void DrawResult(void);//リザルトの描画
void SetResult(int nType, D3DXVECTOR3 pos);//リザルト画面の設定

#endif