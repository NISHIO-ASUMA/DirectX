//---------------------------
//
//リザルト処理
//Author:NISHIO ASUMA
//
//---------------------------

#include "result.h"
#include "fade.h"

#define NUM_RESULT (3)  // リザルトテクスチャ

//リザルト情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;//座標
	D3DXVECTOR3 col;//カラー
	int nType;//種類
	bool bUse;//使用状態
	float fHeight;//高さ
	float fWidth;//幅
	RESULTSTATE state;//状態
}Result;

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureResult[NUM_RESULT] = {};//テクスチャのポインタ
Result g_aResult[NUM_RESULT];//リザルト構造体の情報
RESULT g_Result;//リザルト列挙型の情報
int g_nCntResultAnim;//リザルト状態
int g_nPatternResultAnim;//状態パターン


//==================
//リザルトの初期化
//==================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();


	VERTEX_2D* pVtx;//頂点情報のポインタ

	//テクスチャ2の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\result000.png",
		&g_pTextureResult[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//アンロック
	g_pVtxBuffResult->Unlock();

}
//==================
//リザルトの終了
//==================
void UninitResult(void)
{
	for (int nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{
		//テクスチャの破棄
		if (g_pTextureResult[nCntResult] != NULL)
		{
			g_pTextureResult[nCntResult]->Release();
			g_pTextureResult[nCntResult] = NULL;
		}

	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

}
//==================
//リザルトの更新
//==================
void UpdateResult(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		//Enterキーが押された
		//モード設定(リザルトに移動)
		SetFade(MODE_TITLE);
	}
}
//==================
//リザルトの描画
//==================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResult[g_aResult[nCntResult].nType]);

		//リザルトポリゴンの描画(1種類目)
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntResult * 4, 2);//1個目のプレイヤーの始点(0番目～3番目)
	}
}
//=======================
//リザルト画面の設定処理
//=======================
void SetResult(int nType, D3DXVECTOR3 pos)
{


}

