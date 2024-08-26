//---------------------------
//
//DirectX シューティング
//Author:NISHIO ASUMA
//
//---------------------------

#include "main.h"
#include "Player.h"
#include "background.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "tutorial.h"

//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;//現在のモード
bool g_isFullscreen = false;// ウィンドウを切り替えるためのフラグ
RECT g_windowRect;// ウィンドウを切り替えるための変数

//************************************************
// ウィンドウをフルスクリーンに変える処理
//************************************************
void ToggleFullscreen(HWND hWnd)
{
	// 現在のウィンドウスタイルを取得
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// ウィンドウモードに切り替え
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// フルスクリーンモードに切り替え
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}

//----------------------------
//メイン関数
//----------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),         //WNDCLASSEXのメモリサイズ
		CS_CLASSDC,                 //ウインドウのスタイル
		WindowProc,                 //ウインドウプロシージャ
		0,                          //0にする
		0,                          //0にする
		hInstance,                  //インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),  //タスクバーアイコン
		LoadCursor(NULL,IDC_ARROW),      //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),      //クライアント領域の背景色
		NULL,                            //メニューバー
		CLASS_NAME,                      //ウインドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),  //ファイルアイコン
	};

	HWND hWnd;  //ウインドウハンドル(識別子)
	MSG msg;    //メッセージを格納する変数

	//画面サイズの構造
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	//ウインドウを生成
	hWnd = CreateWindowEx(0,    //拡張ウインドウスタイル
	CLASS_NAME,             //ウインドウクラスの名前
	WINDOW_NAME,            //ウインドウの名前
	WS_OVERLAPPEDWINDOW,    //ウインドウスタイル
	CW_USEDEFAULT,          //ウインドウの左上のX座標
	CW_USEDEFAULT,          //ウインドウの左上のY座標
	(rect.right - rect.left),           //ウインドウ幅
	(rect.bottom - rect.top),          //ウインドウの高さ
	NULL,
	NULL,
	hInstance,              //インスタンスハンドル
	NULL);                  //ウインドウ作成データ

//初期化処理
if (FAILED(Init(hInstance, hWnd, TRUE)))
{
	//初期化処理が失敗したとき
	return -1;
}

//ウインドウの表示
ShowWindow(hWnd, nCmdShow);//ウインドウの表示状態の設定
UpdateWindow(hWnd);//クライアント領域の更新

//メッセージループ
while (1)
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
	{
		//Windowsの処理
		if (msg.message == WM_QUIT)
		{
			//WM_QUITメッセージを受け取ったらループ抜ける
			break;
		}
		else
		{
			//メッセージ設定
			TranslateMessage(&msg);//仮想キーメッセージを文字メッセージへ変換
			DispatchMessage(&msg);//ウインドウプロシージャへメッセージを送出
		}
	}
	else
	{
		//DirectXの処理
		//更新処理
		Update();

		//描画処理
		Draw();
	}
}
//終了処理
Uninit();

//ウインドウクラスの登録を解除
UnregisterClass(CLASS_NAME, wcex.hInstance);

return(int)msg.wParam;
}
//---------------------------------------
//ウインドウプロシージャ
//---------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//ウインドウの領域

	switch (uMsg)
	{
	case WM_DESTROY://ウインドウ破棄メッセージ
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN://キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE://[ESC]キーが押された
			DestroyWindow(hWnd);//ウインドウ破棄メッセージ
			break;
		case VK_F11:
			ToggleFullscreen(hWnd);//F11でフルスクリーン
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//既定の処理を繰り返す
}
//=========================
//初期化処理
//=========================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;//プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションのパラメーターを設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));//パラメーターの0クリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;//バックバッファの形式
	d3dpp.BackBufferCount = 1;//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//デプスバッファとして16bitを使用
	d3dpp.Windowed = bWindow;//ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//リフレッシュシート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//インターバル

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成(描画処理はハードウェア,頂点処理をCPUで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3Dデバイスの生成(描画処理,頂点処理をCPUで行う)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージチャートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//==============
	//各種初期化処理
	//==============
	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//ジョイパッドの初期化
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//モードの設定
	SetMode(g_mode);

	//フェードの設定
	InitFade(g_mode);

	return S_OK;
}
//==================
//終了処理
//==================
void Uninit(void)
{
	//==================
	//各種終了処理
	//==================

	//タイトルの終了
	UninitTitle();

	//ゲーム画面の終了
	UninitGame();

	//リザルト画面の終了
	UninitResult();

	//キーボードの終了処理
	UninitKeyboard();

	//ジョイパッドの終了
	UninitJoypad();

	//フェードの終了
	UninitFade();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D ->Release();
		g_pD3D = NULL;
	}

}
//===================
//更新処理
//===================
void Update(void)
{
	//========================
	//各種オブジェクト更新処理
	//========================
	
	//キーボードの更新処理
	UpdateKeyboard();//キー入力

	//ジョイパッドの更新処理
	UpdateJoypad();

	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
		UpdateTitle();
		break;

	case MODE_TUTORIAL://チュートリアル画面
		UpdateTutorial();
		break;

	case MODE_GAME://ゲーム画面
		UpdateGame();
		break;

	case MODE_RESULT://リザルト画面
		UpdateResult();
		break;
	}
	//フェードの更新
	UpdateFade();
}
//===================
//描画処理
//===================
void Draw(void)
{
	//画面クリア(バックバッファ&Zバッファのクリア)
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0,), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//描画成功時
		//================
		//描画処理
		//================
		//現在の画面の終了
		switch (g_mode)
		{
		case MODE_TITLE://タイトル画面
			DrawTitle();
			break;

		case MODE_TUTORIAL://チュートリアル画面
			DrawTutorial();
			break;

		case MODE_GAME:
			DrawGame();
			break;

		case MODE_RESULT:
			DrawResult();
			break;
		}
		//フェードの描画
		DrawFade();
		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//======================
// モードの設定
//======================
void SetMode(MODE mode)
{
	//現在の画面の終了処理
	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
		UninitTitle();
		break;

	case MODE_TUTORIAL://チュートリアル画面
		UninitTutorial();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;
	}

	//新しい画面の初期化処理
	switch (mode)
	{
	case MODE_TITLE://タイトル画面
		InitTitle();
		break;

	case MODE_TUTORIAL://チュートリアル画面
		InitTutorial();
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;
	}
	g_mode = mode;//画面切り替え
}
//======================
//デバイスの取得
//======================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//====================
//モードの取得
//====================
MODE GetMode(void)
{
	return g_mode;//変数を返す
}