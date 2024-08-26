//===============================
//
//アイテム処理
//Author:ASUMA NISHIO
//
//================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//マクロ
#define MAX_ITEM (6) //アイテムの種類数

//アイテムタイプの列挙型
typedef enum
{
	ITEMTYPE_ONE = 0,//1つ目
	ITEMTYPE_TWO,    //2つ目
	ITEMTYPE_THREE,  //3つ目
	ITEMTYPE_FOUR,   //4つ目
	ITEMTYPE_FIVE,   //5つ目
	ITEMTYPE_SIX,    //6つ目
	ITEMTYPE_MAX
}ITEMTYPE;

//アイテムの構造体
typedef struct
{
	D3DXVECTOR3 pos;//座標
	D3DXVECTOR3 move;//移動量
	D3DXCOLOR col;//色
	int nType;//敵の種類
	bool bUse;//使用しているか
	int nLife;//アイテムの体力
	int nItemCounter;//アイテム数をカウント
}ITEM;

//プロトタイプ宣言
void InitItem(void);//初期化
void UninitItem(void);//終了
void UpdateItem(void);//更新
void DrawItem(void);//描画
void SetItem(D3DXVECTOR3 pos,int nType);//設定
void HitItem(int nCntItem);//アイテムの当たり判定
ITEM* GetItem(void);//判定を取得

#endif