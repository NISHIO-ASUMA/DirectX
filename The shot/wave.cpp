//---------------------------
//
//wave処理
//Author:NISHIO ASUMA
//
//---------------------------

//#include "wave.h"
//#include "input.h"
//#include <stdio.h>
////グローバル
//int g_nCntEnemy;//敵をカウント
//int g_nWave;//ウェーブを管理
//
////==============================
////ウェーブ処理
////==============================
//void LoadWave(void)
//{
//	FILE* pFile;//ファイルポインタ
//	char aString[4096];//読み込む文字数
//
//	//ファイル開く
//	pFile = fopen("WAVE\\wave1.txt", "r");
//
//	if (pFile != NULL)
//	{
//
//		while (1)
//		{
//			//ファイルから読み込む
//			fscanf(pFile, "%s", &aString[0]);
//
//			if (strcmp(aString, "POS") == 0)
//			{
//				//ローカル変数宣言
//				D3DXVECTOR3 pos;
//
//				fscanf(pFile, "%f", pos.x);
//				fscanf(pFile, "%f", pos.y);
//				fscanf(pFile, "%f", pos.z);
//
//			}
//			else if (strcmp(aString, "END_SCRIPT") == 0)
//			{
//				//ファイルを閉じる
//				fclose(pFile);
//				break;
//			}
//
//		}
//
//	}
//	else
//	{
//		//開けなかった時
//		//メッセージBOXの表示
//		MessageBox(NULL, "開けません", "エラー", MB_OK);
//
//		return;
//	}
//}