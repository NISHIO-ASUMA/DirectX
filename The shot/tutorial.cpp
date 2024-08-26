//========================================
//
//チュートリアル処理
//Author:ASUMA NISHIO
//
//========================================

#include "tutorial.h"
#include "player.h"
#include "game.h"
#include "fade.h"
#include "enemy.h"
#include "bullet.h"
#include "background.h"

//マクロ定義
#define MAX_TUTORIAL (4)//数

//チュートリアル構造体
typedef struct
{
	D3DXVECTOR3 pos;//座標
	D3DXVECTOR3 col;//カラー
	int nType;//種類
	bool bUse;//使用状態
	float fHeight;//高さ
	float fWidth;//幅
	TUTORIALSTATE state;//状態
}Tutorial;

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTutorial[MAX_TUTORIAL] = {};//テクスチャのポインタ
Tutorial g_aTutorial[MAX_TUTORIAL];//チュートリアル構造体の情報
TUTORIAL g_Tutorial;//チュートリアル列挙型の情報
int g_nCntTutoAnim;//チュートリアル状態
int g_nPatternTutoAnim;//状態パターン


//======================
//チュートリアルの初期化
//======================
void InitTutorial(void)
{
	//InitGame();

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//頂点情報のポインタ

	for (int nCnt = 0; nCnt < TUTORIAL_MAX; nCnt++)
	{
		//敵のテクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			TUTORIAL_TEXTURE[nCnt],
			&g_pTextureTutorial[nCnt]);
	}

	for (int nCntTutorial = 0; nCntTutorial < MAX_TUTORIAL; nCntTutorial++)
	{
		g_aTutorial[nCntTutorial].nType = 0;
		g_aTutorial[nCntTutorial].fHeight = 0.0f;
		g_aTutorial[nCntTutorial].fWidth = 0.0f;
		g_aTutorial[nCntTutorial].bUse = false;
		g_aTutorial[nCntTutorial].state = TUTORIALSTATE_NONE;//何もしていない状態
	}

	g_nCntTutoAnim = 0;//チュートリアル状態
	g_nPatternTutoAnim = 0;//状態パターン

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TUTORIAL,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
	{
		//頂点座標1の設定
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
	SetTutorial(TUTORIAL_FIRST, D3DXVECTOR3(190.0f, 350.0f, 0.0f));//チュートリアル1
	SetTutorial(TUTORIAL_SECOND, D3DXVECTOR3(1030.0f, 680.0f, 0.0f));//チュートリアル2
}
//====================
//チュートリアルの終了
//====================
void UninitTutorial(void)
{
	//UninitGame();
	for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureTutorial[nCnt] != NULL)
		{					   
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

}
//=====================
//チュートリアルの更新
//=====================
void UpdateTutorial(void)
{
	//UpdateGame();

	GetFade();//フェードの取得

	FADE g_fade = GetFade();//現在の状態

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		//Enterキーが押された
		for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
		{
			if (g_aTutorial[nCnt].bUse == true && g_aTutorial[nCnt].nType == TUTORIAL_SECOND)
			{
				g_aTutorial[nCnt].state = TUTORIALSTATE_FLASH;
			}
		}
		//モード設定(チュートリアル画面に移動)
		SetFade(MODE_GAME);
	}
	else if (JoypadTrigger(JOYKEY_START) == true)
	{
		//startが押された
		//モード設定(チュートリアル画面に移動)
		for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
		{
			if (g_aTutorial[nCnt].bUse == true && g_aTutorial[nCnt].nType == TUTORIAL_SECOND)
			{
				g_aTutorial[nCnt].state = TUTORIALSTATE_FLASH;
			}
		}
		//モード設定(チュートリアル画面に移動)
		SetFade(MODE_GAME);
	}

	TutorialFlash(TUTORIAL_SECOND);//チュートリアルの点滅

}
//====================
//チュートリアルの描画
//====================
void DrawTutorial(void)
{
	//DrawGame();

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTutorial[g_aTutorial[nCnt].nType]);

		//チュートリアルポリゴンの描画(1種類目)
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);//1個目のプレイヤーの始点(0番目～3番目)
	}
}
//================================
//チュートリアルの設定(テクスチャ)
//================================
void SetTutorial(int nType, D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;//頂点情報のポインタ

//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
	{
		if (g_aTutorial[nCnt].bUse == false)
		{
			g_aTutorial[nCnt].nType = nType;
			g_aTutorial[nCnt].pos = pos;
			g_aTutorial[nCnt].bUse = true;

			//場合分け
			switch (nType)
			{
			case TUTORIAL_FIRST://1つ目

				g_aTutorial[nCnt].fHeight = 600.0f;//高さ
				g_aTutorial[nCnt].fWidth = 300.0f;//横幅
				break;

			case TUTORIAL_SECOND://2つ目

				g_aTutorial[nCnt].fHeight = 50.0f;//高さ
				g_aTutorial[nCnt].fWidth = 450.0f; //横幅
				break;
			}

			//頂点座標1の設定
			pVtx[0].pos = D3DXVECTOR3(g_aTutorial[nCnt].pos.x - g_aTutorial[nCnt].fWidth * 0.5f, g_aTutorial[nCnt].pos.y - g_aTutorial[nCnt].fHeight * 0.5f, 0.0f);//1つ目の頂点情報
			pVtx[1].pos = D3DXVECTOR3(g_aTutorial[nCnt].pos.x + g_aTutorial[nCnt].fWidth * 0.5f, g_aTutorial[nCnt].pos.y - g_aTutorial[nCnt].fHeight * 0.5f, 0.0f);//2つ目の頂点情報
			pVtx[2].pos = D3DXVECTOR3(g_aTutorial[nCnt].pos.x - g_aTutorial[nCnt].fWidth * 0.5f, g_aTutorial[nCnt].pos.y + g_aTutorial[nCnt].fHeight * 0.5f, 0.0f);//3つ目の頂点情報
			pVtx[3].pos = D3DXVECTOR3(g_aTutorial[nCnt].pos.x + g_aTutorial[nCnt].fWidth * 0.5f, g_aTutorial[nCnt].pos.y + g_aTutorial[nCnt].fHeight * 0.5f, 0.0f);//4つ目の頂点情報

			break;
		}

		pVtx += 4;
	}

	//アンロック
	g_pVtxBuffTutorial->Unlock();
}
//==========================
//点滅の処理
//==========================
void TutorialFlash(int nType)
{
	VERTEX_2D* pVtx = 0;//頂点情報のポインタ

//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
	{
		if (g_aTutorial[nCnt].bUse == true && g_aTutorial[nCnt].state == TUTORIALSTATE_FLASH)
		{
			g_nCntTutoAnim++;//カウンターを加算

			if (g_nCntTutoAnim == 5)//5の時
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);

			}

			else if (g_nCntTutoAnim == 10)//10の時
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				g_nCntTutoAnim = 0;//初期化に戻す
			}
		}
		pVtx += 4;
	}
	//アンロック
	g_pVtxBuffTutorial->Unlock();
}