//---------------------------
//
//背景処理
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _BACKGROUND_H_ //このマクロ定義がされてなかったら
#define _BACKGROUND_H_ //2重インクルード防止のマクロ定義

//プロトタイプ宣言
void InitBackground(void);//プレイヤーの初期化
void UninitBackground(void);//プレイヤーの終了
void UpdateBackground(void);//プレイヤーの更新処理
void DrawBackground(void);//プレイヤーの描画処理

#endif
