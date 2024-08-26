//---------------------------
//
//敵の処理
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"

//マクロ
#define MAX_ENEMY (128)// 敵の最大数
#define MAX_ENEMY_SIZE (25.0f)// 敵のサイズ

//敵の状態の列挙型
typedef enum
{
	ENEMYSTATE_NORMAL = 0,// 通常状態
	ENEMYSTATE_DAMAGE,// ダメージ状態
	ENEMYSTATE_MAX
}ENEMYSTATE;

//敵の種類情報(列挙型)
typedef enum
{
	ENEMYTYPE_OWN = 0,
	ENEMYTYPE_TWO,
	ENEMYTYPE_THREE,
	ENEMYTYPE_FOUR,
	ENEMYTYPE_FIVE,
	ENEMYTYPE_SIX,
	ENEMYTYPE_MAX
}ENEMYTYPE;

static const char* ENEMY_TEXTURE[ENEMYTYPE_MAX] =   //敵のテクスチャの設定
{
	"date\\TEXTURE\\2.png",
	"date\\TEXTURE\\pingu.jpg",
	"date\\TEXTURE\\bg100.jpg",
	"date\\TEXTURE\\bg200.jpg",
	"date\\TEXTURE\\title000.png",
	"date\\TEXTURE\\title3.png",
};

//構造体
typedef struct
{
	D3DXVECTOR3 pos;//座標
	D3DXVECTOR3 move;//移動量
	D3DXVECTOR3 rot;//回転量
	ENEMYSTATE state;//敵の状態
	int nCounterState;//状態管理カウンター
	float fLength;//対角線
	float fAngle;//角度
	int nType;//敵の種類
	bool bUse;//使用しているか
	int nLife;//敵の体力
	int nBulletCounter;//敵の弾の数をカウント
}Enemy;

//プロト
void InitEnemy(void);//敵の初期化
void UninitEnemy(void);//敵の終了
void UpdateEnemy(void);//敵の更新
void DrawEnemy(void);//敵の描画
void SetEnemy(D3DXVECTOR3 pos,int nType);//敵の設定処理
void HitEnemy(int nCntEnemy, int nDamage);//敵の当たり判定
Enemy* GetEnemy(void);//判定を取得
int GetNumEnemy();//敵のカウント

#endif

