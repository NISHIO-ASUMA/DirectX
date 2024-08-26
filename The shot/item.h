//===============================
//
//�A�C�e������
//Author:ASUMA NISHIO
//
//================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//�}�N��
#define MAX_ITEM (6) //�A�C�e���̎�ސ�

//�A�C�e���^�C�v�̗񋓌^
typedef enum
{
	ITEMTYPE_ONE = 0,//1��
	ITEMTYPE_TWO,    //2��
	ITEMTYPE_THREE,  //3��
	ITEMTYPE_FOUR,   //4��
	ITEMTYPE_FIVE,   //5��
	ITEMTYPE_SIX,    //6��
	ITEMTYPE_MAX
}ITEMTYPE;

//�A�C�e���̍\����
typedef struct
{
	D3DXVECTOR3 pos;//���W
	D3DXVECTOR3 move;//�ړ���
	D3DXCOLOR col;//�F
	int nType;//�G�̎��
	bool bUse;//�g�p���Ă��邩
	int nLife;//�A�C�e���̗̑�
	int nItemCounter;//�A�C�e�������J�E���g
}ITEM;

//�v���g�^�C�v�錾
void InitItem(void);//������
void UninitItem(void);//�I��
void UpdateItem(void);//�X�V
void DrawItem(void);//�`��
void SetItem(D3DXVECTOR3 pos,int nType);//�ݒ�
void HitItem(int nCntItem);//�A�C�e���̓����蔻��
ITEM* GetItem(void);//������擾

#endif