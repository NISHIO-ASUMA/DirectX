//---------------------------
//
//タイトル処理
//Author:NISHIO ASUMA
//
//---------------------------

#include "title.h"
#include "fade.h"

//マクロ
#define NUM_TITLE (2)//タイトル数

//タイトル構造体
typedef struct
{
	D3DXVECTOR3 pos;//座標
	D3DXVECTOR3 col;//カラー
	int nType;//種類
	bool bUse;//使用状態
	float fHeight;//高さ
	float fWidth;//幅
	TITLESTATE state;//状態
}Title;

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_TITLE] = {};//テクスチャのポインタ
Title g_aTitle[NUM_TITLE];//タイトル構造体の情報
TITLE g_Title;//タイトル列挙型の情報
int g_nCntTitleAnim;//タイトル状態
int g_nPatternAnim;//状態パターン

//==================
//タイトルの初期化
//==================
void InitTitle(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\title3.png",
		&g_pTextureTitle[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\title202.png",
		&g_pTextureTitle[1]);

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		g_aTitle[nCntTitle].nType = 0;
		g_aTitle[nCntTitle].fHeight = 0.0f;
		g_aTitle[nCntTitle].fWidth = 0.0f;
		g_aTitle[nCntTitle].bUse = false;
		g_aTitle[nCntTitle].state = TITLE_NONE;//何もしていない状態
	}

	 g_nCntTitleAnim = 0;//タイトル状態
	 g_nPatternAnim = 0;//状態パターン


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TITLE,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//1つ目の頂点情報
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//2つ目の頂点情報
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//3つ目の頂点情報
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//4つ目の頂点情報

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

	SetTitle(TITLE_FIRST, D3DXVECTOR3(650.0f, 300.0f, 0.0f));//タイトル1
	SetTitle(TITLE_SECOND, D3DXVECTOR3(650.0f, 600.0f, 0.0f));//タイトル2

	//アンロック
	g_pVtxBuffTitle->Unlock();
}
//==================
//タイトルの終了
//==================
void UninitTitle(void)
{
	//テクスチャの破棄
	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{

		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}
//==================
//タイトルの更新
//==================
void UpdateTitle(void)
{
	GetFade();//フェードの取得

	FADE g_fade = GetFade();//現在の状態

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		//Enterキーが押された
		for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
		{
			if (g_aTitle[nCntTitle].bUse == true && g_aTitle[nCntTitle].nType == TITLE_SECOND)
			{
				g_aTitle[nCntTitle].state = TITLE_FLASH;
			}
		}
		//モード設定(チュートリアル画面に移動)
		SetFade(MODE_TUTORIAL);
	}
	else if (JoypadTrigger(JOYKEY_START) == true)
	{
		//startが押された
		//モード設定(チュートリアル画面に移動)
		for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
		{
			if (g_aTitle[nCntTitle].bUse == true && g_aTitle[nCntTitle].nType == TITLE_SECOND)
			{
				g_aTitle[nCntTitle].state = TITLE_FLASH;
			}
		}
		//モード設定(チュートリアル画面に移動)
		SetFade(MODE_TUTORIAL);
	}

	TitleFlash(TITLE_SECOND);//タイトルの点滅
}
//==================
//タイトルの描画
//==================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[g_aTitle[nCntTitle].nType]);

		//タイトルポリゴンの描画(1種類目)
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);//1個目のプレイヤーの始点(0番目～3番目)
	}
}
//======================
//タイトルの設定処理
//======================
void SetTitle(int nType, D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == false)
		{
			g_aTitle[nCntTitle].nType = nType;
			g_aTitle[nCntTitle].pos = pos;
			g_aTitle[nCntTitle].bUse = true;

			//場合分け
			switch (nType)
			{
			case TITLE_FIRST:

				g_aTitle[nCntTitle].fHeight =600.0f;//高さ
				g_aTitle[nCntTitle].fWidth = 700.0f;//横幅
				break;

			case TITLE_SECOND:

				g_aTitle[nCntTitle].fHeight = 100.0f;//高さ
				g_aTitle[nCntTitle].fWidth = 870.0f; //横幅
				break;
			}

			//頂点座標1の設定
			pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);//1つ目の頂点情報
			pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);//2つ目の頂点情報
			pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);//3つ目の頂点情報
			pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);//4つ目の頂点情報

			break;
		}

		pVtx += 4;
	}

	//アンロック
	g_pVtxBuffTitle->Unlock();
}
//==============================
//タイトルの点滅
//==============================
void TitleFlash(int nType)
{
	VERTEX_2D* pVtx = 0;//頂点情報のポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == true && g_aTitle[nCntTitle].state == TITLE_FLASH)
		{
			g_nCntTitleAnim++;//カウンターを加算

			if (g_nCntTitleAnim == 5)//5の時
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);

			}

			else if(g_nCntTitleAnim == 10)//10の時
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				g_nCntTitleAnim = 0;//初期値に戻す
			}
		}
		pVtx += 4;
	}
	//アンロック
	g_pVtxBuffTitle->Unlock();

}