//===============================
//
//�A�C�e������
//Author:ASUMA NISHIO
//
//================================

#include "item.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_apTextureItem[MAX_ITEM] = {};//�e�N�X�`�����W
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;//���_�o�b�t�@�̃|�C���^
ITEM  g_aItem[MAX_ITEM];//�A�C�e���̏��
ITEMTYPE g_Item;//�A�C�e���̗񋓌^
int nCntItem;//�A�C�e�������J�E���g

//==============================
//�A�C�e���̏���������
//==============================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nItem;//�G�̐�

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bg000.png",
		&g_apTextureItem[0]);

	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		g_aItem[nItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���W
		g_aItem[nItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
		g_aItem[nItem].col = D3DXCOLOR(255, 255, 255, 255);//�F
		g_aItem[nItem].nLife = 1;//�̗�
		g_aItem[nItem].nType = 0;//���
		g_aItem[nItem].bUse = false;//���g�p���
		g_aItem[nItem].nItemCounter = 0;//�A�C�e���J�E���^�[�̏�����
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nItem = 0; nItem < MAX_ITEM; nItem++)
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
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffItem->Unlock();

}
//========================
//�A�C�e���̏I��
//========================
void UninitItem(void)
{
	int nItem;//���[�J���ϐ�

	//�e�N�X�`�����W�̔j��
	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{

		if (g_apTextureItem[nItem] != NULL)
		{			   
			g_apTextureItem[nItem]->Release();
			g_apTextureItem[nItem] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{			  
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}
//============================
//�A�C�e���̍X�V����
//============================
void UpdateItem(void)
{
	//�Ȃ�?
}
//=============================
//�A�C�e���̕`��
//=============================
void DrawItem(void)
{
	int nItem;//�e���J�E���g
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�

	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (g_aItem[nItem].bUse == true)
		{
			//�e���g�p����Ă���
			//�|���S���̕`��
			pDevice->SetTexture(0, g_apTextureItem[nItem]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//�v���C���[�̎n�_(0�Ԗځ`3�Ԗ�)

		}
	}
}
//===========================
//�A�C�e���̐ݒ�
//===========================
void SetItem(D3DXVECTOR3 pos, int nType)
{
	int nItem;//���[�J���ϐ�

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (g_aItem[nItem].bUse == false)
		{
			//�g�p����ĂȂ�
			g_aItem[nItem].pos = pos;
			g_aItem[nItem].nType = nType;
			g_aItem[nItem].bUse = true;//�g�p���
			g_aItem[nItem].nLife = 1;
			g_aItem[nItem].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);//�F


			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 30.0f, g_aItem[nItem].pos.y - 30.0f, 0.0f);//1�ڂ̒��_���
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 30.0f, g_aItem[nItem].pos.y - 30.0f, 0.0f);//2�ڂ̒��_���
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 30.0f, g_aItem[nItem].pos.y + 30.0f, 0.0f);//3�ڂ̒��_���
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 30.0f, g_aItem[nItem].pos.y + 30.0f, 0.0f);//4�ڂ̒��_���

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


		}
		break;

		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffItem->Unlock();
}
//=======================
//�A�C�e�����̓����蔻��
//=======================
void HitItem(int nCntItem)
{
	int nItem = 0;//���[�J���ϐ�

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aItem[nItem].nLife <= 0)
	{

		g_aItem[nItem].bUse = false;//���g�p���
	}
	else
	{
		g_aItem[nItem].nLife--;//���C�t�����炷
		pVtx += 4 * nCntItem;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);

	}
	//�A�����b�N
	g_pVtxBuffItem->Unlock();

}
//=======================
//�A�C�e���̔�����擾
//=======================
ITEM* GetItem(void)
{
	return &g_aItem[0];
}