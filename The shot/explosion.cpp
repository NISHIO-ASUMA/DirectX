//---------------------------
//
//��������
//Author:NISHIO ASUMA
//
//---------------------------

#include "explosion.h"
#include "player.h"
#include "main.h"

//�}�N����`
#define MAX_EXPLOSION (128)//�����̍ő吔
#define MAX_EXPLOSIONSIZE_X (30)//�����̃T�C�Y
#define MAX_EXPLOSIONSIZE_Y (30)//�����̃T�C�Y

//�����\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXCOLOR col;//�F
	int nCounterAnimExplosion;//�A�j���[�V�����J�E���^�[
	int nPatternAnimExplosion;//�A�j���[�V�����p�^�[��
	bool bUse;//�g�p���Ă��邩
}Explosion;

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;//�e�N�X�`���̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];//�����̏��

//=========================
//�����̏���������
//=========================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntExplosion;//�����̐�
		
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);

	//�������̏�����
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); 
		g_aExplosion[nCntExplosion].bUse = false;//�g�p���ĂȂ���Ԃɂ���
		g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;
		g_aExplosion[nCntExplosion].nPatternAnimExplosion = 0;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y - 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50.0f, g_aExplosion[nCntExplosion].pos.y - 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y + 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50.0f, g_aExplosion[nCntExplosion].pos.y + 50.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���܂Ƃ߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}
//========================
//�����̏I������
//========================
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

}
//=============================
//�����̍X�V����
//=============================
void UpdateExplosion(void)
{
	int nCntExplosion;//�������J�E���g
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx ;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].nCounterAnimExplosion++;

		if (g_aExplosion[nCntExplosion].bUse == true)
		{

				if (g_aExplosion[nCntExplosion].nCounterAnimExplosion >= MAX_ANIMATION_TIME)
				{
					g_aExplosion[nCntExplosion].nCounterAnimExplosion = NULL;//�J�E���^�[�������l�ɖ߂�

					g_aExplosion[nCntExplosion].nPatternAnimExplosion++;//�p�^�[���i���o�[���X�V

					//���_���W�̍X�V
					pVtx[0].tex = D3DXVECTOR2(0.0f + g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(0.125f + g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f + g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, SPLIT_V);
					pVtx[3].tex = D3DXVECTOR2(0.125f + g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, SPLIT_V);

				}
				if (g_aExplosion[nCntExplosion].nPatternAnimExplosion > MAX_ANIMATION_PATTERN)
				{
					g_aExplosion[nCntExplosion].nPatternAnimExplosion = 0;//�p�^�[���i���o�[�������l�ɖ߂�
					g_aExplosion[nCntExplosion].bUse = false;
				}
		}

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();

}
//===========================
//�����̕`�揈��
//===========================
void DrawExplosion(void)
{
	int nCntExplosion;//�������J�E���g
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//�������g�p����Ă���
			//�|���S���̕`��
			pDevice->SetTexture(0, g_pTextureExplosion);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);//�v���C���[�̎n�_(0�Ԗځ`3�Ԗ�)

		}
	}
}
//============================
//�����̐ݒ菈��
//============================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;//�����̃J�E���g
	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			//�������g���Ă��Ȃ�
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].bUse = true;//�g�p���ĂȂ���Ԃɂ���

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 50.0f,g_aExplosion[nCntExplosion].pos.y - 50.0f,0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50.0f,g_aExplosion[nCntExplosion].pos.y - 50.0f,0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 50.0f,g_aExplosion[nCntExplosion].pos.y + 50.0f,0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50.0f,g_aExplosion[nCntExplosion].pos.y + 50.0f,0.0f);
																		 		
			//rhw�̐ݒ�(1.0f�ŌŒ�)
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			break;
		}

		pVtx += 4;//4���ړ�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();

}