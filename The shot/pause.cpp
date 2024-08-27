//---------------------------
//
//プレイヤー処理
//Author:NISHIO ASUMA
//
//---------------------------

#include "pause.h"
#include "fade.h"
#include "input.h"

#define MAX_PAUSE_TEX (3)  //ポーズ画面のテクスチャ

//グローバル
LPDIRECT3DTEXTURE9 g_apTexturePause[MAX_PAUSE_TEX] = {};//テクスチャへのポインタ(3枚分)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;//頂点バッファのポインタ
PAUSE_MENU g_pauseMenu;//ポーズメニュー

//=========================
//ポーズの初期化
//=========================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntPause;//背景カウント

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\pause000.png",
		&g_apTexturePause[0]);

	//テクスチャ2の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\pause001.png",
		&g_apTexturePause[1]);

	//テクスチャ3の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\pause002.png",
		&g_apTexturePause[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE_TEX,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_PAUSE_TEX; nCnt++)
	{
		//頂点座標1の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//1つ目の頂点情報
		pVtx[1].pos = D3DXVECTOR3(500.0f, 0.0f, 0.0f);//2つ目の頂点情報
		pVtx[2].pos = D3DXVECTOR3(0.0f, 700.0f, 0.0f);//3つ目の頂点情報
		pVtx[3].pos = D3DXVECTOR3(500.0f, 700.0f, 0.0f);//4つ目の頂点情報

		//rhwの設定(1.0fで固定)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		pVtx += 4;
	}
	//アンロック
	g_pVtxBuffPause->Unlock();
}
//=========================
//ポーズの終了
//=========================
void UninitPause(void)
{
	int nCnt;//ローカル変数

	//テクスチャの初期化
	for (nCnt = 0; nCnt < MAX_PAUSE_TEX; nCnt++)
	{
		if (g_apTexturePause[nCnt] != NULL)
		{
			g_apTexturePause[nCnt]->Release();
			g_apTexturePause[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
//=========================
//ポーズの更新
//=========================
void UpdatePause(void)
{
	VERTEX_2D* pVtx;//頂点情報のポインタ

	//メニュー選択
	switch (g_pauseMenu)
	{
	case PAUSE_MENU_CONTINUE:
		break;

	case PAUSE_MENU_RETRY:
		break;

	case PAUSE_MENU_QUIT:
		break;
	}

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		//エンターキーが押された
		switch (g_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:
			break;

		case PAUSE_MENU_RETRY:
			SetFade(MODE_GAME);
			break;

		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE);
			break;
		}

	}
}
//=========================
//ポーズの描画
//=========================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	VERTEX_2D* pVtx = 0;//頂点情報のポインタ

	for (int nCnt = 0; nCnt < MAX_PAUSE_TEX; nCnt++)
	{

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexturePause[0]);
		pDevice->SetTexture(0, g_apTexturePause[1]);
		pDevice->SetTexture(0, g_apTexturePause[2]);

		//描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);//背景の始点(0番目～3番目)

		pVtx += 4;
	}
}

