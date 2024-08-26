//---------------------------
//
//�v���C���[����
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


//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffplayer = NULL;//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureplayer = NULL;//�e�N�X�`���̃|�C���^
Player g_aPlayer;//�v���C���[�̏��
PLAYERSTATE g_pPlayer;//�v���C���[��Ԃ̕ϐ�

//=======================
//�v���C���[�̏���������
//=======================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	VERTEX_2D* pVtx;//���_���̃|�C���^

	//�e�N�X�`��2�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\Player001.png",
		&g_pTextureplayer);

	//g_nCounterAnimPlayer = 0;//�J�E���^�[�̏�����
	//g_nPatternAnimPlayer = 0;//�p�^�[��No.�̏�����
	g_aPlayer.pos = D3DXVECTOR3(600.0f,600.0f,0.0f);//�ʒu�̏�����
	g_aPlayer.move = D3DXVECTOR3(0.0f,0.0f,0.0f);//�ړ��ʂ̏�����
	g_aPlayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏�����
	g_aPlayer.nLife = 50;
	g_aPlayer.nCntAnimState = 0;
	g_aPlayer.bHit = false;
	g_aPlayer.nCntState = 0;
	g_aPlayer.state = PLAYERSTATE_NORMAL;
	g_aPlayer.bDisp = true;

	//�Ίp���̒������Z�o
	g_aPlayer.fLength = sqrtf((MAX_SIZE_X * MAX_SIZE_X) + (MAX_SIZE_Y * MAX_SIZE_Y)) / 2.0f;
	
	//�Ίp���̊p�x���Z�o
	g_aPlayer.fAngle = atan2f(MAX_SIZE_X,MAX_SIZE_Y);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffplayer,
		NULL);

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
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

	//rhw�̐ݒ�(1.0f�ŌŒ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(SPLIT_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, SPLIT_V);
	pVtx[3].tex = D3DXVECTOR2(SPLIT_U, SPLIT_V);

	//�A�����b�N
	g_pVtxBuffplayer->Unlock();
}
//======================
//�v���C���[�̏I������
//======================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureplayer != NULL)
	{
		g_pTextureplayer->Release();
		g_pTextureplayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffplayer != NULL)
	{
		g_pVtxBuffplayer->Release();
		g_pVtxBuffplayer = NULL;
	}

}
//=====================
//�v���C���[�̍X�V����
//=====================
void UpdatePlayer(void)
{
	VERTEX_2D* pVtx;//���_���̃|�C�^

	//�L�[���͏��̎擾
	GetKeyPlayer();

	//�p�b�h�����擾
	GetJoypadPlayer();

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
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
			//���_�J���[�̐ݒ�
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
			//���U���g��ʂɈڍs
			SetFade(MODE_RESULT);

			return;
		}
		break;
	}
	//�A�����b�N
	g_pVtxBuffplayer->Unlock();

}
//=====================
//�v���C���[�̕`�揈��
//=====================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (g_aPlayer.bDisp == true)
	{

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffplayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureplayer);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//�v���C���[�̎n�_
	}

}
//=================================
//�_���[�W�H����ăv���C���[������
//=================================
void HitPlayer(int nDamage)
{
	VERTEX_2D* pVtx;//���_���̃|�C�^

	g_aPlayer.nLife -= nDamage;//�_���[�W��H�������̗͌��炷

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
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
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	}

	//�A�����b�N
	g_pVtxBuffplayer->Unlock();
	
}
//===================
// �L�[���͏��̎擾
//===================
void GetKeyPlayer(void)
{
	VERTEX_2D* pVtx;//���_���̃|�C���^
	static float fData = SPLIT_U;
	static float fData2 = 0.0f;
	//A�L�[����������
	if (GetKeyboardPress(DIK_A) == true)
	{
		fData = SPLIT_U;
		//A�P�̂̏���
		g_aPlayer.move.x -= 0.07f;
	}
	//D����������
	else if (GetKeyboardPress(DIK_D) == true)
	{
		fData = -SPLIT_U;
		//D�P�̂̏���
		g_aPlayer.move.x += 0.07f;
	}
	//S����������
	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_aPlayer.move.y += 0.05f;
	}
	//W����������
	else if (GetKeyboardPress(DIK_W) == true)
	{
		g_aPlayer.move.y -= 0.05f;
	}
	//r����������(���Z�b�g)
	else if (KeyboardTrigger(DIK_R) == true)
	{
		g_aPlayer.fLength = 85.0f;
		g_aPlayer.rot.z = 0.0f;
		g_aPlayer.pos.x = 640.0f;
		g_aPlayer.pos.y = 500.0f;
	}
	//space�L�[��������
	if (KeyboardTrigger(DIK_SPACE) == true)
	{
		//�e�̐ݒ�
		SetBullet(g_aPlayer.pos, D3DXVECTOR3(sinf(g_aPlayer.rot.z + D3DX_PI) * 7.0f, cosf(g_aPlayer.rot.z + D3DX_PI) * 7.0f, 0.0f), g_aPlayer.rot, 50.0f, 50.0f, 45, BULLETTYPE_PLAYER);
	}
	//�q�b�g���
	if (g_aPlayer.bHit == true)
	{
		g_aPlayer.nCntAnimState++;//�J�E���^�[�����Z
	}

	//�ʒu���X�V
	g_aPlayer.pos.x += g_aPlayer.move.x;
	g_aPlayer.pos.y += g_aPlayer.move.y;

	//�ړ��ʂ̍X�V(����������)
	g_aPlayer.move.x += (0.0f - g_aPlayer.move.x) * 0.05f;
	g_aPlayer.move.y += (0.0f - g_aPlayer.move.y) * 0.05f;

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aPlayer.nCntAnimState >= 5)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		g_aPlayer.nCntAnimState = 0;//������Ԃɖ߂�
		g_aPlayer.bHit = false;//����𖢎g�p��Ԃɂ���
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

	//�A�����b�N
	g_pVtxBuffplayer->Unlock();

}
//=================================
//�p�b�h�̏���
//=================================
void GetJoypadPlayer(void)
{
	VERTEX_2D* pVtx;//���_���̃|�C�^


	if (JoypadPress(JOYKEY_UP) == true)
	{
		//��L�[�������ꂽ
		g_aPlayer.pos.y -= 1.0f;
	}
	else if (JoypadPress(JOYKEY_DOWN) == true)
	{
		//���L�[�������ꂽ
		g_aPlayer.pos.y += 1.0f;
	}
	else if (JoypadPress(JOYKEY_LEFT) == true)
	{
		//���L�[�������ꂽ
		g_aPlayer.pos.x -= 1.0f;
	}
	else if (JoypadPress(JOYKEY_RIGHT) == true)
	{
		//�E�L�[�������ꂽ
		g_aPlayer.pos.x += 1.0f;
	}
	else if (JoypadPress(JOYKEY_START) == true)
	{
		//�E�ɍs��
		g_aPlayer.pos.x += 1.0f;
	}
	else if (JoypadPress(JOYKEY_BACK) == true)
	{
		//���Z�b�g
		g_aPlayer.fLength = 110.0f;
		g_aPlayer.rot.z = 0.0f;
		g_aPlayer.pos.x = 1000.0f;
		g_aPlayer.pos.y = 300.0f;
	}
	else if (JoypadPress(JOYKEY_LS) == true)
	{
		//����]
		g_aPlayer.rot.z += 0.1f;
	}
	else if (JoypadPress(JOYKEY_RS) == true)
	{
		//�E��]
		g_aPlayer.rot.z -= 0.1f;
	}
	else if (JoypadPress(JOYKEY_LEFT_B) == true)
	{
		//LB�{�^���������ꂽ(�g��)
		if (g_aPlayer.fLength <= 400.0f)
		{
			g_aPlayer.fLength += 1.0f;
		}
	}
	else if (JoypadPress(JOYKEY_RIGHT_B) == true)
	{
		//RB�{�^���������ꂽ(�g��)
		if (g_aPlayer.fLength >= 50.0f)
		{
			g_aPlayer.fLength -= 1.0f;

		}
	}
	else if (JoypadPress(JOYKEY_LEFT_TRIGGER) == true)
	{
		//LB�L�[(L1�L�[)�������ꂽ

	}
	else if (JoypadPress(JOYKEY_RIGHT_TRIGGER) == true)
	{
		//RB�L�[(L1�L�[)�������ꂽ

	}
	else if (JoypadPress(JOYKEY_A) == true)
	{
		//A�L�[�������ꂽ
		SetBullet(g_aPlayer.pos, D3DXVECTOR3(sinf(g_aPlayer.rot.z + D3DX_PI) * 10.0f, cosf(g_aPlayer.rot.z + D3DX_PI) * 10.0f, 0.0f), g_aPlayer.rot, 50.0f, 50.0f, 30, BULLETTYPE_PLAYER);

	}
	else if (JoypadPress(JOYKEY_B) == true)
	{
		//B�L�[�������ꂽ(�E��)
		g_aPlayer.move.x += sinf(D3DX_PI * 0.75) * 0.05f;
		g_aPlayer.move.y += cosf(D3DX_PI * 0.75) * 0.05f;

	}
	else if (JoypadPress(JOYKEY_X) == true)
	{
		//X�L�[�������ꂽ(����)
		g_aPlayer.move.x -= sinf(D3DX_PI * 0.75) * 0.05f;
		g_aPlayer.move.y -= cosf(D3DX_PI * 0.75) * 0.05f;

	}
	else if (JoypadPress(JOYKEY_Y) == true)
	{
		//Y�L�[�������ꂽ(3WAY)
		SetBullet(g_aPlayer.pos, D3DXVECTOR3(sinf(g_aPlayer.rot.z + D3DX_PI) * 7.0f, cosf(g_aPlayer.rot.z + D3DX_PI) * 7.0f, 0.0f), g_aPlayer.rot, 50.0f, 50.0f, 30, BULLETTYPE_PLAYER);
	}

	//�q�b�g���
	if (g_aPlayer.bHit == true)
	{
		g_aPlayer.nCntAnimState++;//�J�E���^�[�����Z
	}

	//�ʒu���X�V
	g_aPlayer.pos.x += g_aPlayer.move.x;
	g_aPlayer.pos.y += g_aPlayer.move.y;

	//�ړ��ʂ̍X�V(����������)
	g_aPlayer.move.x += (0.0f - g_aPlayer.move.x) * 0.01f;
	g_aPlayer.move.y += (0.0f - g_aPlayer.move.y) * 0.01f;

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aPlayer.nCntAnimState >= 5)
	{
		//���_�J���[�̐ݒ�
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

	//�A�����b�N
	g_pVtxBuffplayer->Unlock();

}
//===================
//�v���C���[�̎擾
//===================
Player* GetPlayer(void)
{
	return &g_aPlayer;
}

