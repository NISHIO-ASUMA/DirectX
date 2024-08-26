//===============================
//
//アイテム処理
//Author:ASUMA NISHIO
//
//================================

#include "item.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"

//グローバル
LPDIRECT3DTEXTURE9 g_apTextureItem[MAX_ITEM] = {};//テクスチャ座標
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;//頂点バッファのポインタ
ITEM  g_aItem[MAX_ITEM];//アイテムの情報
ITEMTYPE g_Item;//アイテムの列挙型
int nCntItem;//アイテム数をカウント

//==============================
//アイテムの初期化処理
//==============================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nItem;//敵の数

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bg000.png",
		&g_apTextureItem[0]);

	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		g_aItem[nItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//座標
		g_aItem[nItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//移動量
		g_aItem[nItem].col = D3DXCOLOR(255, 255, 255, 255);//色
		g_aItem[nItem].nLife = 1;//体力
		g_aItem[nItem].nType = 0;//種類
		g_aItem[nItem].bUse = false;//未使用状態
		g_aItem[nItem].nItemCounter = 0;//アイテムカウンターの初期化
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定(1.0fで固定)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//アンロック
	g_pVtxBuffItem->Unlock();

}
//========================
//アイテムの終了
//========================
void UninitItem(void)
{
	int nItem;//ローカル変数

	//テクスチャ座標の破棄
	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{

		if (g_apTextureItem[nItem] != NULL)
		{			   
			g_apTextureItem[nItem]->Release();
			g_apTextureItem[nItem] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{			  
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}
//============================
//アイテムの更新処理
//============================
void UpdateItem(void)
{
	//なし?
}
//=============================
//アイテムの描画
//=============================
void DrawItem(void)
{
	int nItem;//弾をカウント
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定

	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (g_aItem[nItem].bUse == true)
		{
			//弾が使用されている
			//ポリゴンの描画
			pDevice->SetTexture(0, g_apTextureItem[nItem]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プレイヤーの始点(0番目～3番目)

		}
	}
}
//===========================
//アイテムの設定
//===========================
void SetItem(D3DXVECTOR3 pos, int nType)
{
	int nItem;//ローカル変数

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (g_aItem[nItem].bUse == false)
		{
			//使用されてない
			g_aItem[nItem].pos = pos;
			g_aItem[nItem].nType = nType;
			g_aItem[nItem].bUse = true;//使用状態
			g_aItem[nItem].nLife = 1;
			g_aItem[nItem].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);//色


			//頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 30.0f, g_aItem[nItem].pos.y - 30.0f, 0.0f);//1つ目の頂点情報
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 30.0f, g_aItem[nItem].pos.y - 30.0f, 0.0f);//2つ目の頂点情報
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 30.0f, g_aItem[nItem].pos.y + 30.0f, 0.0f);//3つ目の頂点情報
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 30.0f, g_aItem[nItem].pos.y + 30.0f, 0.0f);//4つ目の頂点情報

			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


		}
		break;

		pVtx += 4;
	}
	//アンロック
	g_pVtxBuffItem->Unlock();
}
//=======================
//アイテム側の当たり判定
//=======================
void HitItem(int nCntItem)
{
	int nItem = 0;//ローカル変数

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aItem[nItem].nLife <= 0)
	{

		g_aItem[nItem].bUse = false;//未使用状態
	}
	else
	{
		g_aItem[nItem].nLife--;//ライフを減らす
		pVtx += 4 * nCntItem;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);

	}
	//アンロック
	g_pVtxBuffItem->Unlock();

}
//=======================
//アイテムの判定を取得
//=======================
ITEM* GetItem(void)
{
	return &g_aItem[0];
}