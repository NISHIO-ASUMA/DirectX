//---------------------------
//
//ゲーム処理
//Author:NISHIO ASUMA
//
//---------------------------

#include "game.h"
#include "Player.h"
#include "background.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "fade.h"
#include "score.h"
#include "item.h"
#include "title.h"
#include "tutorial.h"
#include "effect.h"

//グローバル
GAMESTATE g_gameState = GAMESTATE_NONE;//ゲーム状態
int g_nCounterGameState = 0;//状態管理カウンター

//===================
//ゲームの初期化
//===================
void InitGame(void)
{
	InitBackground();//背景

	InitBullet();//弾

	InitPlayer();//プレイヤー

	InitEnemy();//敵

	SetEnemy(D3DXVECTOR3(500.0f, 500.0f, 0.0f), ENEMYTYPE_OWN);
	SetEnemy(D3DXVECTOR3(100.0f, 100.0f, 0.0f), ENEMYTYPE_TWO);

	InitExplosion();//爆発

	InitScore();//スコア

	InitItem();//アイテム

	InitEffect();//エフェクト

	g_gameState = GAMESTATE_NORMAL;//通常状態
	g_nCounterGameState = 0;
}
//===================
//ゲームの終了
//===================
void UninitGame(void)
{
	UninitBackground();//背景

	UninitBullet();//弾

	UninitPlayer();//プレイヤー

	UninitEnemy();//敵の終了

	UninitExplosion();//爆発

	UninitScore();//スコア終了

	UninitItem();//アイテム

	UninitEffect();//エフェクト

}
//===================
//ゲームの更新
//===================
void UpdateGame(void)
{
	int nNum;//敵をカウント

	UpdateBackground();//背景

	UpdatePlayer();//プレイヤー

	UpdateBullet();//弾

	UpdateEnemy();//敵

	UpdateExplosion();//爆発

	UpdateScore();//スコア更新

	UpdateItem();//アイテム

	UpdateEffect();//エフェクト

	//プレイヤーの取得
	Player* pPlayer = GetPlayer();

	nNum = GetNumEnemy();

	if (pPlayer->bDisp == false || nNum <= 0)
	{
		g_gameState = GAMESTATE_END;
	}
	switch(g_gameState)
	{
	case GAMESTATE_NORMAL://通常状態
		break;

	case GAMESTATE_END:
  		g_nCounterGameState++;
		if (g_nCounterGameState >= 120)
		{
			g_nCounterGameState = 0;
			//1秒経過
			g_gameState = GAMESTATE_NONE;//何もしていない状態
			//画面設定
			SetFade(MODE_RESULT);
		}
		break;
	}
}
//===================
//ゲームの描画
//===================
void DrawGame(void)
{
	//背景
	DrawBackground();

	//弾
	DrawBullet();

	//プレイヤー
	DrawPlayer();

	//敵
	DrawEnemy();

	//爆破
	DrawExplosion();

	//スコア
	DrawScore();

	//アイテム
	DrawItem();

	DrawEffect();
}
//=====================
//げーむ状態設定
//=====================
void SetGamestate(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}
//=====================
//げーむ状態取得
//=====================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}


