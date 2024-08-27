//---------------------------
//
//�v���C���[����
//Author:NISHIO ASUMA
//
//---------------------------

#include "pause.h"
#include "fade.h"
#include "input.h"

#define MAX_PAUSE_TEX (3)  //�|�[�Y��ʂ̃e�N�X�`��

//�O���[�o��
LPDIRECT3DTEXTURE9 g_apTexturePause[MAX_PAUSE_TEX] = {};//�e�N�X�`���ւ̃|�C���^(3����)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;//���_�o�b�t�@�̃|�C���^
PAUSE_MENU g_pauseMenu;//�|�[�Y���j���[

//=========================
//�|�[�Y�̏�����
//=========================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntPause;//�w�i�J�E���g

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\pause000.png",
		&g_apTexturePause[0]);

	//�e�N�X�`��2�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\pause001.png",
		&g_apTexturePause[1]);

	//�e�N�X�`��3�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\pause002.png",
		&g_apTexturePause[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE_TEX,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_PAUSE_TEX; nCnt++)
	{
		//���_���W1�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//1�ڂ̒��_���
		pVtx[1].pos = D3DXVECTOR3(500.0f, 0.0f, 0.0f);//2�ڂ̒��_���
		pVtx[2].pos = D3DXVECTOR3(0.0f, 700.0f, 0.0f);//3�ڂ̒��_���
		pVtx[3].pos = D3DXVECTOR3(500.0f, 700.0f, 0.0f);//4�ڂ̒��_���

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
	//�A�����b�N
	g_pVtxBuffPause->Unlock();
}
//=========================
//�|�[�Y�̏I��
//=========================
void UninitPause(void)
{
	int nCnt;//���[�J���ϐ�

	//�e�N�X�`���̏�����
	for (nCnt = 0; nCnt < MAX_PAUSE_TEX; nCnt++)
	{
		if (g_apTexturePause[nCnt] != NULL)
		{
			g_apTexturePause[nCnt]->Release();
			g_apTexturePause[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
//=========================
//�|�[�Y�̍X�V
//=========================
void UpdatePause(void)
{
	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���j���[�I��
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
		//�G���^�[�L�[�������ꂽ
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
//�|�[�Y�̕`��
//=========================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	VERTEX_2D* pVtx = 0;//���_���̃|�C���^

	for (int nCnt = 0; nCnt < MAX_PAUSE_TEX; nCnt++)
	{

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePause[0]);
		pDevice->SetTexture(0, g_apTexturePause[1]);
		pDevice->SetTexture(0, g_apTexturePause[2]);

		//�`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);//�w�i�̎n�_(0�Ԗځ`3�Ԗ�)

		pVtx += 4;
	}
}

