//========================================
//
//�`���[�g���A������
//Author:ASUMA NISHIO
//
//========================================

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "input.h"

//�񋓌^(���)
typedef enum
{
	TUTORIAL_FIRST = 0,//1�ڂ̃`���[�g���A���摜
	TUTORIAL_SECOND,//2�ڂ̃`���[�g���A���摜
	TUTORIAL_THIRD,//3�ڂ̃`���[�g���A���摜
	TUTORIAL_FOUTH,//4�ڂ̃`���[�g���A���摜
	TUTORIAL_MAX
}TUTORIAL;

//�񋓌^(���)
typedef enum
{
	TUTORIALSTATE_NONE = 0,//�^�C�g�����(�ʏ���)
	TUTORIALSTATE_FLASH,//�_�ŏ��
	TUTORIALSTATE_MAX
}TUTORIALSTATE;

static const char* TUTORIAL_TEXTURE[TUTORIAL_MAX] =   //�`���[�g���A���̃e�N�X�`���̐ݒ�
{
	"date\\TEXTURE\\hirata.jpg",
	"date\\TEXTURE\\Tutorial111.png",
	"date\\TEXTURE\\hirata.jpg",
	"date\\TEXTURE\\hirata.jpg",
};

//�v���g�^�C�v�錾
void InitTutorial(void);//�`���[�g���A���̏�����
void UninitTutorial(void);//�`���[�g���A���̏I��
void UpdateTutorial(void);//�`���[�g���A���̍X�V
void DrawTutorial(void);//�`���[�g���A���̕`��
void SetTutorial(int nType, D3DXVECTOR3 pos);//�`���[�g���A���̐ݒ�
void TutorialFlash(int nType);//�`���[�g���A���̓_��

#endif