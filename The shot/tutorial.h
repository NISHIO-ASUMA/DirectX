//========================================
//
//チュートリアル処理
//Author:ASUMA NISHIO
//
//========================================

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "input.h"

//列挙型(種類)
typedef enum
{
	TUTORIAL_FIRST = 0,//1つ目のチュートリアル画像
	TUTORIAL_SECOND,//2つ目のチュートリアル画像
	TUTORIAL_THIRD,//3つ目のチュートリアル画像
	TUTORIAL_FOUTH,//4つ目のチュートリアル画像
	TUTORIAL_MAX
}TUTORIAL;

//列挙型(状態)
typedef enum
{
	TUTORIALSTATE_NONE = 0,//タイトル状態(通常状態)
	TUTORIALSTATE_FLASH,//点滅状態
	TUTORIALSTATE_MAX
}TUTORIALSTATE;

static const char* TUTORIAL_TEXTURE[TUTORIAL_MAX] =   //チュートリアルのテクスチャの設定
{
	"date\\TEXTURE\\hirata.jpg",
	"date\\TEXTURE\\Tutorial111.png",
	"date\\TEXTURE\\hirata.jpg",
	"date\\TEXTURE\\hirata.jpg",
};

//プロトタイプ宣言
void InitTutorial(void);//チュートリアルの初期化
void UninitTutorial(void);//チュートリアルの終了
void UpdateTutorial(void);//チュートリアルの更新
void DrawTutorial(void);//チュートリアルの描画
void SetTutorial(int nType, D3DXVECTOR3 pos);//チュートリアルの設定
void TutorialFlash(int nType);//チュートリアルの点滅

#endif