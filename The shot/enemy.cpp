//---------------------------
//
//敵の処理
//Author:NISHIO ASUMA
//
//---------------------------

#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "player.h"
#include "main.h"
#include "score.h"
#include "item.h"

//マクロ
#define NUM_ENEMY (6)//種類数

//グローバル
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;//頂点バッファのポインタ
Enemy  g_aEnemy[MAX_ENEMY];//敵の情報
ENEMYTYPE g_pEnemy;//敵のタイプの列挙型情報
int g_nNumEnemy;//カウント

//=========================
//敵の初期化処理
//=========================
void InitEnemy(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntEnemy;//敵の数

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//頂点情報のポインタ

	for (int nCnt = 0; nCnt < ENEMYTYPE_MAX; nCnt++)
	{
		//敵のテクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			ENEMY_TEXTURE[nCnt],
			&g_apTextureEnemy[nCnt]);
	}

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].state = {};
		g_aEnemy[nCntEnemy].fAngle = 0.0f;
		g_aEnemy[nCntEnemy].fLength = 0.0f;
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nBulletCounter = 0;//敵の弾の数の初期化
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//アンロック
	g_pVtxBuffEnemy->Unlock();

}
//========================
//敵の終了処理
//========================
void UninitEnemy(void)
{
	int nCntEnemy;//敵の数
	//テクスチャの破棄
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{

		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

}
//=============================
//敵の更新処理
//=============================
void UpdateEnemy(void)
{
	VERTEX_2D* pVtx = {};//頂点情報のポインタ

	int nCntEn = 0;// カウント

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEn = 0; nCntEn < MAX_ENEMY; nCntEn++)
	{
		if (g_aEnemy[nCntEn].bUse == true)
		{
			switch (g_aEnemy[nCntEn].state)
			{
			case ENEMYSTATE_NORMAL:

				g_aEnemy[nCntEn].nBulletCounter++;//カウンターを加算
				if (g_aEnemy[nCntEn].nBulletCounter >= MAX_ANIMATION_TIME + 40)//一定時間が経過した
				{
					SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z - D3DX_PI) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 50, BULLETTYPE_ENEMY);
					g_aEnemy[nCntEn].nBulletCounter = 0;//カウンターをリセット
				}

				//頂点カラーの設定(白に戻す)
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				break;
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEn].nCounterState--;
				if (g_aEnemy[nCntEn].nCounterState <= 0)
				{
					g_aEnemy[nCntEn].state = ENEMYSTATE_NORMAL;
				}
				break;
			}
		}
		pVtx += 4;
	}

	//アンロック
	g_pVtxBuffEnemy->Unlock();
}
//===========================
//敵の描画処理
//===========================
void DrawEnemy(void)
{
	int nCntEnemy;//敵の数

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//使用されてる
			int nType = g_aEnemy[nCntEnemy].nType;
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[nType]);

			//敵の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);//始点(0番目～3番目)

		}
	}
}
//============================
//敵の設定処理
//============================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;//敵の数

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//使用されてない
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].bUse = true;//使用状態
			g_aEnemy[nCntEnemy].nLife = 5;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

			//頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE, 0.0f);//1つ目の頂点情報
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE, 0.0f);//2つ目の頂点情報
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + MAX_ENEMY_SIZE, 0.0f);//3つ目の頂点情報
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + MAX_ENEMY_SIZE, 0.0f);//4つ目の頂点情報

			g_nNumEnemy++;//カウントを加算

			break;
		}

		pVtx += 4;
	}
	//アンロック
	g_pVtxBuffEnemy->Unlock();

}
//============================
//敵のヒット処理
//============================
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D* pVtx;//頂点情報のポイタ

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(255, 255, 255, 255));//爆発の処理
		g_aEnemy[nCntEnemy].bUse = false;//使用していない状態にする
 		AddScore(1000);//スコアを加算
		//アイテム生成
		SetItem(g_aEnemy[nCntEnemy].pos,0);

		g_nNumEnemy--;//敵の総数をカウント(デクリメント)
	}
	else
	{
		//頂点バッファをロックし,頂点情報へのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;//ダメージ状態
		g_aEnemy[nCntEnemy].nCounterState = 5;//ダメージ状態の時間

		pVtx += 4 * nCntEnemy;

		//頂点カラーの設定(赤にする)
		pVtx[0].col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);

		//アンロック
		g_pVtxBuffEnemy->Unlock();
	}
}
//=========================
//敵のカウント
//=========================
int GetNumEnemy()
{
	return g_nNumEnemy;
}
//============================
//敵の取得
//============================
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}
