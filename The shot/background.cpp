//---------------------------
//
//背景処理
//Author:NISHIO ASUMA
//
//---------------------------

#include "main.h"
#include "background.h"

//マクロ定義
#define NUM_BACKGROUND (3)//背景の数

//グローバル
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBackground = NULL;//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_apTextureBackground[NUM_BACKGROUND] = {};//テクスチャ3枚分のポインタ
float g_aPosTexU[NUM_BACKGROUND];//テクスチャ座標の開始位置

//=======================
//背景の初期化処理
//=======================
void InitBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntBackground;//背景カウント

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bg100.png",
		&g_apTextureBackground[0]);

	//テクスチャ2の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bg101.png",
		&g_apTextureBackground[1]);

	//テクスチャ3の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bg102.png",
		&g_apTextureBackground[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BACKGROUND,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBackground,
		NULL);

	//テクスチャ座標の開始位置(U値)の初期化
	for (nCntBackground = 0; nCntBackground < NUM_BACKGROUND; nCntBackground++)
	{
		g_aPosTexU[nCntBackground] = 0.0f;
	}

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBackground = 0; nCntBackground < NUM_BACKGROUND; nCntBackground++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//1つ目の頂点情報
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);//2つ目の頂点情報
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);//3つ目の頂点情報
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);//4つ目の頂点情報

		//rhwの設定(1.0fで固定)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground]+ 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground] +1.0f, 1.0f);

		pVtx += 4;//4つ分進める
	}
	//アンロック
	g_pVtxBuffBackground->Unlock();
}
//======================
//背景の終了処理
//======================
void UninitBackground(void)
{
	int nCntBackground;//背景カウント

	//テクスチャの破棄
	for (nCntBackground = 0; nCntBackground < NUM_BACKGROUND; nCntBackground++)
	{

		if (g_apTextureBackground[nCntBackground] != NULL)
		{
			g_apTextureBackground[nCntBackground]->Release();
			g_apTextureBackground[nCntBackground] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBackground != NULL)
	{
		g_pVtxBuffBackground->Release();
		g_pVtxBuffBackground = NULL;
	}

}
//=====================
//背景の更新処理
//=====================
void UpdateBackground(void)
{
	int nCntBackground;//背景カウント
	VERTEX_2D* pVtx;//頂点情報のポインタ

    //頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBackground = 0; nCntBackground < NUM_BACKGROUND; nCntBackground++)
	{
		g_aPosTexU[nCntBackground] += 0.005f;//背景スクロールの変化量

		//rhwの設定(1.0fで固定)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground] + 1.0f, 1.0f);

		pVtx += 4;//4つ分進める

	}
	//アンロック
	g_pVtxBuffBackground->Unlock();

}
//=====================
//背景の描画処理
//=====================
void DrawBackground(void)
{
	int nCntBackground;//背景のカウント

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBackground, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	VERTEX_2D* pVtx = 0;//頂点情報のポインタ

	for (nCntBackground = 0; nCntBackground < NUM_BACKGROUND; nCntBackground++)
	{

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureBackground[0]);
		pDevice->SetTexture(0, g_apTextureBackground[1]);
		pDevice->SetTexture(0, g_apTextureBackground[2]);


		//背景の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//背景の始点(0番目～3番目)

		pVtx += 4;
	}

}
