//---------------------------
//
//���U���g����
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "input.h"

//�񋓌^(���)
typedef enum
{
	RESULT_FIRST = 0,//1�ڂ̃^�C�g��
	RESULT_SECOND,//2�ڂ̃^�C�g��
	RESULT_MAX
}RESULT;

//�񋓌^(���)
typedef enum
{
	RESULT_NONE = 0,//�^�C�g�����(�ʏ���)
	RESULT_FLASH,//�_�ŏ��
	RESULTSTATE_MAX
}RESULTSTATE;

//�v���g
void InitResult(void);//���U���g�̏�����
void UninitResult(void);//���U���g�̏I��
void UpdateResult(void);//���U���g�̍X�V
void DrawResult(void);//���U���g�̕`��
void SetResult(int nType, D3DXVECTOR3 pos);//���U���g��ʂ̐ݒ�

#endif