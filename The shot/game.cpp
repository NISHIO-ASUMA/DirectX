//---------------------------
//
//�Q�[������
//Author:NISHIO ASUMA
//
//---------------------------

#include "game.h"
#include "Player.h"
#include "background.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "fade.h"
#include "score.h"
#include "item.h"
#include "title.h"
#include "tutorial.h"
#include "effect.h"
#include "pause.h"

//�O���[�o��
GAMESTATE g_gameState = GAMESTATE_NONE;//�Q�[�����
int g_nCounterGameState = 0;//��ԊǗ��J�E���^�[
bool g_bPause = false;//�|�[�Y�����ǂ���

//===================
//�Q�[���̏�����
//===================
void InitGame(void)
{
	InitBackground();//�w�i

	InitBullet();//�e

	InitPlayer();//�v���C���[

	InitEnemy();//�G

	SetEnemy(D3DXVECTOR3(500.0f, 500.0f, 0.0f), ENEMYTYPE_OWN);
	SetEnemy(D3DXVECTOR3(100.0f, 100.0f, 0.0f), ENEMYTYPE_TWO);

	InitExplosion();//����

	InitScore();//�X�R�A

	InitItem();//�A�C�e��

	InitEffect();//�G�t�F�N�g

	g_gameState = GAMESTATE_NORMAL;//�ʏ���
	g_nCounterGameState = 0;
	g_bPause = false;//�|�[�Y��ʂ̏�����(�|�[�Y����)
}
//===================
//�Q�[���̏I��
//===================
void UninitGame(void)
{
	UninitBackground();//�w�i

	UninitBullet();//�e

	UninitPlayer();//�v���C���[

	UninitEnemy();//�G�̏I��

	UninitExplosion();//����

	UninitScore();//�X�R�A�I��

	UninitItem();//�A�C�e��

	UninitEffect();//�G�t�F�N�g

}
//===================
//�Q�[���̍X�V
//===================
void UpdateGame(void)
{
	int nNum;//�G���J�E���g

	//�v���C���[�̎擾
	Player* pPlayer = GetPlayer();

	nNum = GetNumEnemy();

	if (pPlayer->bDisp == false || nNum <= 0)
	{
		g_gameState = GAMESTATE_END;
	}
	switch(g_gameState)
	{
	case GAMESTATE_NORMAL://�ʏ���
		break;

	case GAMESTATE_END:
  		g_nCounterGameState++;
		if (g_nCounterGameState >= 120)
		{
			g_nCounterGameState = 0;
			//1�b�o��
			g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ����
			//��ʐݒ�
			SetFade(MODE_RESULT);
		}
		break;
	}
	if (KeyboardTrigger(DIK_P) == true)
	{
		//p�������ꂽ
		g_bPause = g_bPause ? false : true;
	}
	
	if (g_bPause == true)
	{
		//�|�[�Y��
		//�|�[�Y�̍X�V����
		UpdatePause();
	}
	else 
	{
		//�|�[�Y���Ŗ������

		UpdateBackground();//�w�i

		UpdatePlayer();//�v���C���[

		UpdateBullet();//�e

		UpdateEnemy();//�G

		UpdateExplosion();//����

		UpdateScore();//�X�R�A�X�V

		UpdateItem();//�A�C�e��

		UpdateEffect();//�G�t�F�N�g
	}
}
//===================
//�Q�[���̕`��
//===================
void DrawGame(void)
{
	//�w�i
	DrawBackground();

	//�e
	DrawBullet();

	//�v���C���[
	DrawPlayer();

	//�G
	DrawEnemy();

	//���j
	DrawExplosion();

	//�X�R�A
	DrawScore();

	//�A�C�e��
	DrawItem();

	//�G�t�F�N�g
	DrawEffect();

	if (g_bPause == true)
	{
		//�|�[�Y��
		//�|�[�Y�̕`��
		DrawPause();
	}
}
//=====================
//�|�[�Y�̗L�������ݒ�
//=====================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}
//=====================
//���[�ޏ�Ԑݒ�
//=====================
void SetGamestate(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}
//=====================
//���[�ޏ�Ԏ擾
//=====================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}


