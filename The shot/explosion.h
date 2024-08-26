//---------------------------
//
//爆発処理
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"


//プロトタイプ宣言
void InitExplosion(void);//弾の初期化
void UninitExplosion(void);//弾の終了
void UpdateExplosion(void);//弾の更新
void DrawExplosion(void);//弾の描画
void SetExplosion(D3DXVECTOR3 pos,D3DXCOLOR col);//弾の設定処理

#endif

