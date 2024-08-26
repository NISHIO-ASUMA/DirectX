//---------------------------
//
//�G�̏���
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"

//�}�N��
#define MAX_ENEMY (128)// �G�̍ő吔
#define MAX_ENEMY_SIZE (25.0f)// �G�̃T�C�Y

//�G�̏�Ԃ̗񋓌^
typedef enum
{
	ENEMYSTATE_NORMAL = 0,// �ʏ���
	ENEMYSTATE_DAMAGE,// �_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//�G�̎�ޏ��(�񋓌^)
typedef enum
{
	ENEMYTYPE_OWN = 0,
	ENEMYTYPE_TWO,
	ENEMYTYPE_THREE,
	ENEMYTYPE_FOUR,
	ENEMYTYPE_FIVE,
	ENEMYTYPE_SIX,
	ENEMYTYPE_MAX
}ENEMYTYPE;

static const char* ENEMY_TEXTURE[ENEMYTYPE_MAX] =   //�G�̃e�N�X�`���̐ݒ�
{
	"date\\TEXTURE\\2.png",
	"date\\TEXTURE\\pingu.jpg",
	"date\\TEXTURE\\bg100.jpg",
	"date\\TEXTURE\\bg200.jpg",
	"date\\TEXTURE\\title000.png",
	"date\\TEXTURE\\title3.png",
};

//�\����
typedef struct
{
	D3DXVECTOR3 pos;//���W
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 rot;//��]��
	ENEMYSTATE state;//�G�̏��
	int nCounterState;//��ԊǗ��J�E���^�[
	float fLength;//�Ίp��
	float fAngle;//�p�x
	int nType;//�G�̎��
	bool bUse;//�g�p���Ă��邩
	int nLife;//�G�̗̑�
	int nBulletCounter;//�G�̒e�̐����J�E���g
}Enemy;

//�v���g
void InitEnemy(void);//�G�̏�����
void UninitEnemy(void);//�G�̏I��
void UpdateEnemy(void);//�G�̍X�V
void DrawEnemy(void);//�G�̕`��
void SetEnemy(D3DXVECTOR3 pos,int nType);//�G�̐ݒ菈��
void HitEnemy(int nCntEnemy, int nDamage);//�G�̓����蔻��
Enemy* GetEnemy(void);//������擾
int GetNumEnemy();//�G�̃J�E���g

#endif

