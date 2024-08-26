//========================================
//
//�`���[�g���A������
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

//�}�N����`
#define MAX_TUTORIAL (4)//��

//�`���[�g���A���\����
typedef struct
{
	D3DXVECTOR3 pos;//���W
	D3DXVECTOR3 col;//�J���[
	int nType;//���
	bool bUse;//�g�p���
	float fHeight;//����
	float fWidth;//��
	TUTORIALSTATE state;//���
}Tutorial;

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTutorial[MAX_TUTORIAL] = {};//�e�N�X�`���̃|�C���^
Tutorial g_aTutorial[MAX_TUTORIAL];//�`���[�g���A���\���̂̏��
TUTORIAL g_Tutorial;//�`���[�g���A���񋓌^�̏��
int g_nCntTutoAnim;//�`���[�g���A�����
int g_nPatternTutoAnim;//��ԃp�^�[��


//======================
//�`���[�g���A���̏�����
//======================
void InitTutorial(void)
{
	//InitGame();

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//���_���̃|�C���^

	for (int nCnt = 0; nCnt < TUTORIAL_MAX; nCnt++)
	{
		//�G�̃e�N�X�`���̓ǂݍ���
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
		g_aTutorial[nCntTutorial].state = TUTORIALSTATE_NONE;//�������Ă��Ȃ����
	}

	g_nCntTutoAnim = 0;//�`���[�g���A�����
	g_nPatternTutoAnim = 0;//��ԃp�^�[��

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TUTORIAL,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
	{
		//���_���W1�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//1�ڂ̒��_���
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//2�ڂ̒��_���
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//3�ڂ̒��_���
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//4�ڂ̒��_���

		//rhw�̐ݒ�(1.0f�ŌŒ�)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		pVtx += 4;
	}
	SetTutorial(TUTORIAL_FIRST, D3DXVECTOR3(190.0f, 350.0f, 0.0f));//�`���[�g���A��1
	SetTutorial(TUTORIAL_SECOND, D3DXVECTOR3(1030.0f, 680.0f, 0.0f));//�`���[�g���A��2
}
//====================
//�`���[�g���A���̏I��
//====================
void UninitTutorial(void)
{
	//UninitGame();
	for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTutorial[nCnt] != NULL)
		{					   
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

}
//=====================
//�`���[�g���A���̍X�V
//=====================
void UpdateTutorial(void)
{
	//UpdateGame();

	GetFade();//�t�F�[�h�̎擾

	FADE g_fade = GetFade();//���݂̏��

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		//Enter�L�[�������ꂽ
		for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
		{
			if (g_aTutorial[nCnt].bUse == true && g_aTutorial[nCnt].nType == TUTORIAL_SECOND)
			{
				g_aTutorial[nCnt].state = TUTORIALSTATE_FLASH;
			}
		}
		//���[�h�ݒ�(�`���[�g���A����ʂɈړ�)
		SetFade(MODE_GAME);
	}
	else if (JoypadTrigger(JOYKEY_START) == true)
	{
		//start�������ꂽ
		//���[�h�ݒ�(�`���[�g���A����ʂɈړ�)
		for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
		{
			if (g_aTutorial[nCnt].bUse == true && g_aTutorial[nCnt].nType == TUTORIAL_SECOND)
			{
				g_aTutorial[nCnt].state = TUTORIALSTATE_FLASH;
			}
		}
		//���[�h�ݒ�(�`���[�g���A����ʂɈړ�)
		SetFade(MODE_GAME);
	}

	TutorialFlash(TUTORIAL_SECOND);//�`���[�g���A���̓_��

}
//====================
//�`���[�g���A���̕`��
//====================
void DrawTutorial(void)
{
	//DrawGame();

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTutorial[g_aTutorial[nCnt].nType]);

		//�`���[�g���A���|���S���̕`��(1��ޖ�)
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);//1�ڂ̃v���C���[�̎n�_(0�Ԗځ`3�Ԗ�)
	}
}
//================================
//�`���[�g���A���̐ݒ�(�e�N�X�`��)
//================================
void SetTutorial(int nType, D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;//���_���̃|�C���^

//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
	{
		if (g_aTutorial[nCnt].bUse == false)
		{
			g_aTutorial[nCnt].nType = nType;
			g_aTutorial[nCnt].pos = pos;
			g_aTutorial[nCnt].bUse = true;

			//�ꍇ����
			switch (nType)
			{
			case TUTORIAL_FIRST://1��

				g_aTutorial[nCnt].fHeight = 600.0f;//����
				g_aTutorial[nCnt].fWidth = 300.0f;//����
				break;

			case TUTORIAL_SECOND://2��

				g_aTutorial[nCnt].fHeight = 50.0f;//����
				g_aTutorial[nCnt].fWidth = 450.0f; //����
				break;
			}

			//���_���W1�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aTutorial[nCnt].pos.x - g_aTutorial[nCnt].fWidth * 0.5f, g_aTutorial[nCnt].pos.y - g_aTutorial[nCnt].fHeight * 0.5f, 0.0f);//1�ڂ̒��_���
			pVtx[1].pos = D3DXVECTOR3(g_aTutorial[nCnt].pos.x + g_aTutorial[nCnt].fWidth * 0.5f, g_aTutorial[nCnt].pos.y - g_aTutorial[nCnt].fHeight * 0.5f, 0.0f);//2�ڂ̒��_���
			pVtx[2].pos = D3DXVECTOR3(g_aTutorial[nCnt].pos.x - g_aTutorial[nCnt].fWidth * 0.5f, g_aTutorial[nCnt].pos.y + g_aTutorial[nCnt].fHeight * 0.5f, 0.0f);//3�ڂ̒��_���
			pVtx[3].pos = D3DXVECTOR3(g_aTutorial[nCnt].pos.x + g_aTutorial[nCnt].fWidth * 0.5f, g_aTutorial[nCnt].pos.y + g_aTutorial[nCnt].fHeight * 0.5f, 0.0f);//4�ڂ̒��_���

			break;
		}

		pVtx += 4;
	}

	//�A�����b�N
	g_pVtxBuffTutorial->Unlock();
}
//==========================
//�_�ł̏���
//==========================
void TutorialFlash(int nType)
{
	VERTEX_2D* pVtx = 0;//���_���̃|�C���^

//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
	{
		if (g_aTutorial[nCnt].bUse == true && g_aTutorial[nCnt].state == TUTORIALSTATE_FLASH)
		{
			g_nCntTutoAnim++;//�J�E���^�[�����Z

			if (g_nCntTutoAnim == 5)//5�̎�
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);

			}

			else if (g_nCntTutoAnim == 10)//10�̎�
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				g_nCntTutoAnim = 0;//�������ɖ߂�
			}
		}
		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffTutorial->Unlock();
}