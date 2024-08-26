//---------------------------
//
//プレイヤー処理
//Author:NISHIO ASUMA
//
//---------------------------

#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "fade.h"


//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffplayer = NULL;//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureplayer = NULL;//テクスチャのポインタ
Player g_aPlayer;//プレイヤーの情報
PLAYERSTATE g_pPlayer;//プレイヤー状態の変数

//=======================
//プレイヤーの初期化処理
//=======================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();


	VERTEX_2D* pVtx;//頂点情報のポインタ

	//テクスチャ2の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\Player001.png",
		&g_pTextureplayer);

	//g_nCounterAnimPlayer = 0;//カウンターの初期化
	//g_nPatternAnimPlayer = 0;//パターンNo.の初期化
	g_aPlayer.pos = D3DXVECTOR3(600.0f,600.0f,0.0f);//位置の初期化
	g_aPlayer.move = D3DXVECTOR3(0.0f,0.0f,0.0f);//移動量の初期化
	g_aPlayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期化
	g_aPlayer.nLife = 50;
	g_aPlayer.nCntAnimState = 0;
	g_aPlayer.bHit = false;
	g_aPlayer.nCntState = 0;
	g_aPlayer.state = PLAYERSTATE_NORMAL;
	g_aPlayer.bDisp = true;

	//対角線の長さを算出
	g_aPlayer.fLength = sqrtf((MAX_SIZE_X * MAX_SIZE_X) + (MAX_SIZE_Y * MAX_SIZE_Y)) / 2.0f;
	
	//対角線の角度を算出
	g_aPlayer.fAngle = atan2f(MAX_SIZE_X,MAX_SIZE_Y);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffplayer,
		NULL);

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (-D3DX_PI + g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[0].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (-D3DX_PI + g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (D3DX_PI - g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[1].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (D3DX_PI - g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (0.0f - g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[2].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (0.0f - g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (0.0f + g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[3].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (0.0f + g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[3].pos.z = 0.0f;

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
	pVtx[1].tex = D3DXVECTOR2(SPLIT_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, SPLIT_V);
	pVtx[3].tex = D3DXVECTOR2(SPLIT_U, SPLIT_V);

	//アンロック
	g_pVtxBuffplayer->Unlock();
}
//======================
//プレイヤーの終了処理
//======================
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTextureplayer != NULL)
	{
		g_pTextureplayer->Release();
		g_pTextureplayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffplayer != NULL)
	{
		g_pVtxBuffplayer->Release();
		g_pVtxBuffplayer = NULL;
	}

}
//=====================
//プレイヤーの更新処理
//=====================
void UpdatePlayer(void)
{
	VERTEX_2D* pVtx;//頂点情報のポイタ

	//キー入力情報の取得
	GetKeyPlayer();

	//パッド情報を取得
	GetJoypadPlayer();

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_aPlayer.state)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMAGE:
		g_aPlayer.nCntState--;

		if (g_aPlayer.nCntState <= 0)
		{
			g_aPlayer.state = PLAYERSTATE_NORMAL;
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		}
		break;

	case PLAYERSTATE_DEATH:
		g_aPlayer.nCntState--;
		if (g_aPlayer.nCntState <= 0)
		{
			//リザルト画面に移行
			SetFade(MODE_RESULT);

			return;
		}
		break;
	}
	//アンロック
	g_pVtxBuffplayer->Unlock();

}
//=====================
//プレイヤーの描画処理
//=====================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	if (g_aPlayer.bDisp == true)
	{

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffplayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureplayer);

		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プレイヤーの始点
	}

}
//=================================
//ダメージ食らってプレイヤー消える
//=================================
void HitPlayer(int nDamage)
{
	VERTEX_2D* pVtx;//頂点情報のポイタ

	g_aPlayer.nLife -= nDamage;//ダメージを食らったら体力減らす

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aPlayer.nLife <= 0)
	{
		g_aPlayer.state = PLAYERSTATE_DEATH;
		g_aPlayer.nCntState = 60;
		g_aPlayer.bDisp = false;
	}
	else
	{
		g_aPlayer.state = PLAYERSTATE_DAMAGE;
		g_aPlayer.nCntState = 5;
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	}

	//アンロック
	g_pVtxBuffplayer->Unlock();
	
}
//===================
// キー入力情報の取得
//===================
void GetKeyPlayer(void)
{
	VERTEX_2D* pVtx;//頂点情報のポインタ
	static float fData = SPLIT_U;
	static float fData2 = 0.0f;
	//Aキーを押したら
	if (GetKeyboardPress(DIK_A) == true)
	{
		fData = SPLIT_U;
		//A単体の処理
		g_aPlayer.move.x -= 0.07f;
	}
	//Dを押したら
	else if (GetKeyboardPress(DIK_D) == true)
	{
		fData = -SPLIT_U;
		//D単体の処理
		g_aPlayer.move.x += 0.07f;
	}
	//Sを押したら
	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_aPlayer.move.y += 0.05f;
	}
	//Wを押したら
	else if (GetKeyboardPress(DIK_W) == true)
	{
		g_aPlayer.move.y -= 0.05f;
	}
	//rを押したら(リセット)
	else if (KeyboardTrigger(DIK_R) == true)
	{
		g_aPlayer.fLength = 85.0f;
		g_aPlayer.rot.z = 0.0f;
		g_aPlayer.pos.x = 640.0f;
		g_aPlayer.pos.y = 500.0f;
	}
	//spaceキーを押した
	if (KeyboardTrigger(DIK_SPACE) == true)
	{
		//弾の設定
		SetBullet(g_aPlayer.pos, D3DXVECTOR3(sinf(g_aPlayer.rot.z + D3DX_PI) * 7.0f, cosf(g_aPlayer.rot.z + D3DX_PI) * 7.0f, 0.0f), g_aPlayer.rot, 50.0f, 50.0f, 45, BULLETTYPE_PLAYER);
	}
	//ヒット状態
	if (g_aPlayer.bHit == true)
	{
		g_aPlayer.nCntAnimState++;//カウンターを加算
	}

	//位置を更新
	g_aPlayer.pos.x += g_aPlayer.move.x;
	g_aPlayer.pos.y += g_aPlayer.move.y;

	//移動量の更新(減衰させる)
	g_aPlayer.move.x += (0.0f - g_aPlayer.move.x) * 0.05f;
	g_aPlayer.move.y += (0.0f - g_aPlayer.move.y) * 0.05f;

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aPlayer.nCntAnimState >= 5)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		g_aPlayer.nCntAnimState = 0;//初期状態に戻す
		g_aPlayer.bHit = false;//判定を未使用状態にする
	}

	pVtx[0].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (-D3DX_PI + g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[0].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (-D3DX_PI + g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (D3DX_PI - g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[1].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (D3DX_PI - g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (0.0f - g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[2].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (0.0f - g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (0.0f + g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[3].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (0.0f + g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[3].pos.z = 0.0f;

	//アンロック
	g_pVtxBuffplayer->Unlock();

}
//=================================
//パッドの処理
//=================================
void GetJoypadPlayer(void)
{
	VERTEX_2D* pVtx;//頂点情報のポイタ


	if (JoypadPress(JOYKEY_UP) == true)
	{
		//上キーが押された
		g_aPlayer.pos.y -= 1.0f;
	}
	else if (JoypadPress(JOYKEY_DOWN) == true)
	{
		//下キーが押された
		g_aPlayer.pos.y += 1.0f;
	}
	else if (JoypadPress(JOYKEY_LEFT) == true)
	{
		//左キーが押された
		g_aPlayer.pos.x -= 1.0f;
	}
	else if (JoypadPress(JOYKEY_RIGHT) == true)
	{
		//右キーが押された
		g_aPlayer.pos.x += 1.0f;
	}
	else if (JoypadPress(JOYKEY_START) == true)
	{
		//右に行く
		g_aPlayer.pos.x += 1.0f;
	}
	else if (JoypadPress(JOYKEY_BACK) == true)
	{
		//リセット
		g_aPlayer.fLength = 110.0f;
		g_aPlayer.rot.z = 0.0f;
		g_aPlayer.pos.x = 1000.0f;
		g_aPlayer.pos.y = 300.0f;
	}
	else if (JoypadPress(JOYKEY_LS) == true)
	{
		//左回転
		g_aPlayer.rot.z += 0.1f;
	}
	else if (JoypadPress(JOYKEY_RS) == true)
	{
		//右回転
		g_aPlayer.rot.z -= 0.1f;
	}
	else if (JoypadPress(JOYKEY_LEFT_B) == true)
	{
		//LBボタンが押された(拡大)
		if (g_aPlayer.fLength <= 400.0f)
		{
			g_aPlayer.fLength += 1.0f;
		}
	}
	else if (JoypadPress(JOYKEY_RIGHT_B) == true)
	{
		//RBボタンが押された(拡大)
		if (g_aPlayer.fLength >= 50.0f)
		{
			g_aPlayer.fLength -= 1.0f;

		}
	}
	else if (JoypadPress(JOYKEY_LEFT_TRIGGER) == true)
	{
		//LBキー(L1キー)が押された

	}
	else if (JoypadPress(JOYKEY_RIGHT_TRIGGER) == true)
	{
		//RBキー(L1キー)が押された

	}
	else if (JoypadPress(JOYKEY_A) == true)
	{
		//Aキーが押された
		SetBullet(g_aPlayer.pos, D3DXVECTOR3(sinf(g_aPlayer.rot.z + D3DX_PI) * 10.0f, cosf(g_aPlayer.rot.z + D3DX_PI) * 10.0f, 0.0f), g_aPlayer.rot, 50.0f, 50.0f, 30, BULLETTYPE_PLAYER);

	}
	else if (JoypadPress(JOYKEY_B) == true)
	{
		//Bキーが押された(右上)
		g_aPlayer.move.x += sinf(D3DX_PI * 0.75) * 0.05f;
		g_aPlayer.move.y += cosf(D3DX_PI * 0.75) * 0.05f;

	}
	else if (JoypadPress(JOYKEY_X) == true)
	{
		//Xキーが押された(左下)
		g_aPlayer.move.x -= sinf(D3DX_PI * 0.75) * 0.05f;
		g_aPlayer.move.y -= cosf(D3DX_PI * 0.75) * 0.05f;

	}
	else if (JoypadPress(JOYKEY_Y) == true)
	{
		//Yキーが押された(3WAY)
		SetBullet(g_aPlayer.pos, D3DXVECTOR3(sinf(g_aPlayer.rot.z + D3DX_PI) * 7.0f, cosf(g_aPlayer.rot.z + D3DX_PI) * 7.0f, 0.0f), g_aPlayer.rot, 50.0f, 50.0f, 30, BULLETTYPE_PLAYER);
	}

	//ヒット状態
	if (g_aPlayer.bHit == true)
	{
		g_aPlayer.nCntAnimState++;//カウンターを加算
	}

	//位置を更新
	g_aPlayer.pos.x += g_aPlayer.move.x;
	g_aPlayer.pos.y += g_aPlayer.move.y;

	//移動量の更新(減衰させる)
	g_aPlayer.move.x += (0.0f - g_aPlayer.move.x) * 0.01f;
	g_aPlayer.move.y += (0.0f - g_aPlayer.move.y) * 0.01f;

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aPlayer.nCntAnimState >= 5)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_aPlayer.nCntAnimState = 0;
		g_aPlayer.bHit = false;
	}

	pVtx[0].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (-D3DX_PI + g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[0].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (-D3DX_PI + g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (D3DX_PI - g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[1].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (D3DX_PI - g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (0.0f - g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[2].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (0.0f - g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (0.0f + g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[3].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (0.0f + g_aPlayer.fAngle)) * g_aPlayer.fLength;
	pVtx[3].pos.z = 0.0f;

	//アンロック
	g_pVtxBuffplayer->Unlock();

}
//===================
//プレイヤーの取得
//===================
Player* GetPlayer(void)
{
	return &g_aPlayer;
}

