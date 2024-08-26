//---------------------------
//
//�w�i����
//Author:NISHIO ASUMA
//
//---------------------------

#include "main.h"
#include "background.h"

//�}�N����`
#define NUM_BACKGROUND (3)//�w�i�̐�

//�O���[�o��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBackground = NULL;//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureBackground[NUM_BACKGROUND] = {};//�e�N�X�`��3�����̃|�C���^
float g_aPosTexU[NUM_BACKGROUND];//�e�N�X�`�����W�̊J�n�ʒu

//=======================
//�w�i�̏���������
//=======================
void InitBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntBackground;//�w�i�J�E���g

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bg100.png",
		&g_apTextureBackground[0]);

	//�e�N�X�`��2�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bg101.png",
		&g_apTextureBackground[1]);

	//�e�N�X�`��3�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bg102.png",
		&g_apTextureBackground[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BACKGROUND,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBackground,
		NULL);

	//�e�N�X�`�����W�̊J�n�ʒu(U�l)�̏�����
	for (nCntBackground = 0; nCntBackground < NUM_BACKGROUND; nCntBackground++)
	{
		g_aPosTexU[nCntBackground] = 0.0f;
	}

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBackground = 0; nCntBackground < NUM_BACKGROUND; nCntBackground++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//1�ڂ̒��_���
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);//2�ڂ̒��_���
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);//3�ڂ̒��_���
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);//4�ڂ̒��_���

		//rhw�̐ݒ�(1.0f�ŌŒ�)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground]+ 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground] +1.0f, 1.0f);

		pVtx += 4;//4���i�߂�
	}
	//�A�����b�N
	g_pVtxBuffBackground->Unlock();
}
//======================
//�w�i�̏I������
//======================
void UninitBackground(void)
{
	int nCntBackground;//�w�i�J�E���g

	//�e�N�X�`���̔j��
	for (nCntBackground = 0; nCntBackground < NUM_BACKGROUND; nCntBackground++)
	{

		if (g_apTextureBackground[nCntBackground] != NULL)
		{
			g_apTextureBackground[nCntBackground]->Release();
			g_apTextureBackground[nCntBackground] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBackground != NULL)
	{
		g_pVtxBuffBackground->Release();
		g_pVtxBuffBackground = NULL;
	}

}
//=====================
//�w�i�̍X�V����
//=====================
void UpdateBackground(void)
{
	int nCntBackground;//�w�i�J�E���g
	VERTEX_2D* pVtx;//���_���̃|�C���^

    //���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBackground = 0; nCntBackground < NUM_BACKGROUND; nCntBackground++)
	{
		g_aPosTexU[nCntBackground] += 0.005f;//�w�i�X�N���[���̕ω���

		//rhw�̐ݒ�(1.0f�ŌŒ�)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBackground] + 1.0f, 1.0f);

		pVtx += 4;//4���i�߂�

	}
	//�A�����b�N
	g_pVtxBuffBackground->Unlock();

}
//=====================
//�w�i�̕`�揈��
//=====================
void DrawBackground(void)
{
	int nCntBackground;//�w�i�̃J�E���g

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBackground, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	VERTEX_2D* pVtx = 0;//���_���̃|�C���^

	for (nCntBackground = 0; nCntBackground < NUM_BACKGROUND; nCntBackground++)
	{

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBackground[0]);
		pDevice->SetTexture(0, g_apTextureBackground[1]);
		pDevice->SetTexture(0, g_apTextureBackground[2]);


		//�w�i�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//�w�i�̎n�_(0�Ԗځ`3�Ԗ�)

		pVtx += 4;
	}

}
