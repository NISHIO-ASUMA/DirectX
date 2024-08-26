//---------------------------
//
//�G�̏���
//Author:NISHIO ASUMA
//
//---------------------------

#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "player.h"
#include "main.h"
#include "score.h"
#include "item.h"

//�}�N��
#define NUM_ENEMY (6)//��ސ�

//�O���[�o��
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;//���_�o�b�t�@�̃|�C���^
Enemy  g_aEnemy[MAX_ENEMY];//�G�̏��
ENEMYTYPE g_pEnemy;//�G�̃^�C�v�̗񋓌^���
int g_nNumEnemy;//�J�E���g

//=========================
//�G�̏���������
//=========================
void InitEnemy(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntEnemy;//�G�̐�

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//���_���̃|�C���^

	for (int nCnt = 0; nCnt < ENEMYTYPE_MAX; nCnt++)
	{
		//�G�̃e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			ENEMY_TEXTURE[nCnt],
			&g_apTextureEnemy[nCnt]);
	}

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].state = {};
		g_aEnemy[nCntEnemy].fAngle = 0.0f;
		g_aEnemy[nCntEnemy].fLength = 0.0f;
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nBulletCounter = 0;//�G�̒e�̐��̏�����
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffEnemy->Unlock();

}
//========================
//�G�̏I������
//========================
void UninitEnemy(void)
{
	int nCntEnemy;//�G�̐�
	//�e�N�X�`���̔j��
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{

		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

}
//=============================
//�G�̍X�V����
//=============================
void UpdateEnemy(void)
{
	VERTEX_2D* pVtx = {};//���_���̃|�C���^

	int nCntEn = 0;// �J�E���g

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEn = 0; nCntEn < MAX_ENEMY; nCntEn++)
	{
		if (g_aEnemy[nCntEn].bUse == true)
		{
			switch (g_aEnemy[nCntEn].state)
			{
			case ENEMYSTATE_NORMAL:

				g_aEnemy[nCntEn].nBulletCounter++;//�J�E���^�[�����Z
				if (g_aEnemy[nCntEn].nBulletCounter >= MAX_ANIMATION_TIME + 40)//��莞�Ԃ��o�߂���
				{
					SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z - D3DX_PI) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 50, BULLETTYPE_ENEMY);
					g_aEnemy[nCntEn].nBulletCounter = 0;//�J�E���^�[�����Z�b�g
				}

				//���_�J���[�̐ݒ�(���ɖ߂�)
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				break;
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEn].nCounterState--;
				if (g_aEnemy[nCntEn].nCounterState <= 0)
				{
					g_aEnemy[nCntEn].state = ENEMYSTATE_NORMAL;
				}
				break;
			}
		}
		pVtx += 4;
	}

	//�A�����b�N
	g_pVtxBuffEnemy->Unlock();
}
//===========================
//�G�̕`�揈��
//===========================
void DrawEnemy(void)
{
	int nCntEnemy;//�G�̐�

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//�g�p����Ă�
			int nType = g_aEnemy[nCntEnemy].nType;
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[nType]);

			//�G�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);//�n�_(0�Ԗځ`3�Ԗ�)

		}
	}
}
//============================
//�G�̐ݒ菈��
//============================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;//�G�̐�

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//�g�p����ĂȂ�
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].bUse = true;//�g�p���
			g_aEnemy[nCntEnemy].nLife = 5;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE, 0.0f);//1�ڂ̒��_���
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE, 0.0f);//2�ڂ̒��_���
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + MAX_ENEMY_SIZE, 0.0f);//3�ڂ̒��_���
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + MAX_ENEMY_SIZE, 0.0f);//4�ڂ̒��_���

			g_nNumEnemy++;//�J�E���g�����Z

			break;
		}

		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffEnemy->Unlock();

}
//============================
//�G�̃q�b�g����
//============================
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D* pVtx;//���_���̃|�C�^

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(255, 255, 255, 255));//�����̏���
		g_aEnemy[nCntEnemy].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
 		AddScore(1000);//�X�R�A�����Z
		//�A�C�e������
		SetItem(g_aEnemy[nCntEnemy].pos,0);

		g_nNumEnemy--;//�G�̑������J�E���g(�f�N�������g)
	}
	else
	{
		//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;//�_���[�W���
		g_aEnemy[nCntEnemy].nCounterState = 5;//�_���[�W��Ԃ̎���

		pVtx += 4 * nCntEnemy;

		//���_�J���[�̐ݒ�(�Ԃɂ���)
		pVtx[0].col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);

		//�A�����b�N
		g_pVtxBuffEnemy->Unlock();
	}
}
//=========================
//�G�̃J�E���g
//=========================
int GetNumEnemy()
{
	return g_nNumEnemy;
}
//============================
//�G�̎擾
//============================
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}
