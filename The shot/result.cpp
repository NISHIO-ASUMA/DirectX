//---------------------------
//
//���U���g����
//Author:NISHIO ASUMA
//
//---------------------------

#include "result.h"
#include "fade.h"

#define NUM_RESULT (3)  // ���U���g�e�N�X�`��

//���U���g���̍\����
typedef struct
{
	D3DXVECTOR3 pos;//���W
	D3DXVECTOR3 col;//�J���[
	int nType;//���
	bool bUse;//�g�p���
	float fHeight;//����
	float fWidth;//��
	RESULTSTATE state;//���
}Result;

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureResult[NUM_RESULT] = {};//�e�N�X�`���̃|�C���^
Result g_aResult[NUM_RESULT];//���U���g�\���̂̏��
RESULT g_Result;//���U���g�񋓌^�̏��
int g_nCntResultAnim;//���U���g���
int g_nPatternResultAnim;//��ԃp�^�[��


//==================
//���U���g�̏�����
//==================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	VERTEX_2D* pVtx;//���_���̃|�C���^

	//�e�N�X�`��2�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\result000.png",
		&g_pTextureResult[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	g_pVtxBuffResult->Unlock();

}
//==================
//���U���g�̏I��
//==================
void UninitResult(void)
{
	for (int nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureResult[nCntResult] != NULL)
		{
			g_pTextureResult[nCntResult]->Release();
			g_pTextureResult[nCntResult] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

}
//==================
//���U���g�̍X�V
//==================
void UpdateResult(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		//Enter�L�[�������ꂽ
		//���[�h�ݒ�(���U���g�Ɉړ�)
		SetFade(MODE_TITLE);
	}
}
//==================
//���U���g�̕`��
//==================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[g_aResult[nCntResult].nType]);

		//���U���g�|���S���̕`��(1��ޖ�)
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntResult * 4, 2);//1�ڂ̃v���C���[�̎n�_(0�Ԗځ`3�Ԗ�)
	}
}
//=======================
//���U���g��ʂ̐ݒ菈��
//=======================
void SetResult(int nType, D3DXVECTOR3 pos)
{


}

