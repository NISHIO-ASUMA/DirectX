//---------------------------
//
//wave����
//Author:NISHIO ASUMA
//
//---------------------------

//#include "wave.h"
//#include "input.h"
//#include <stdio.h>
////�O���[�o��
//int g_nCntEnemy;//�G���J�E���g
//int g_nWave;//�E�F�[�u���Ǘ�
//
////==============================
////�E�F�[�u����
////==============================
//void LoadWave(void)
//{
//	FILE* pFile;//�t�@�C���|�C���^
//	char aString[4096];//�ǂݍ��ޕ�����
//
//	//�t�@�C���J��
//	pFile = fopen("WAVE\\wave1.txt", "r");
//
//	if (pFile != NULL)
//	{
//
//		while (1)
//		{
//			//�t�@�C������ǂݍ���
//			fscanf(pFile, "%s", &aString[0]);
//
//			if (strcmp(aString, "POS") == 0)
//			{
//				//���[�J���ϐ��錾
//				D3DXVECTOR3 pos;
//
//				fscanf(pFile, "%f", pos.x);
//				fscanf(pFile, "%f", pos.y);
//				fscanf(pFile, "%f", pos.z);
//
//			}
//			else if (strcmp(aString, "END_SCRIPT") == 0)
//			{
//				//�t�@�C�������
//				fclose(pFile);
//				break;
//			}
//
//		}
//
//	}
//	else
//	{
//		//�J���Ȃ�������
//		//���b�Z�[�WBOX�̕\��
//		MessageBox(NULL, "�J���܂���", "�G���[", MB_OK);
//
//		return;
//	}
//}