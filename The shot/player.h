//---------------------------
//
//�v���C���[����
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _PLAYER_H_ //���̃}�N����`������ĂȂ�������
#define _PLAYER_H_ //2�d�C���N���[�h�h�~�̃}�N����`


#define SPLIT_U (1.0f)//���̕�����
#define SPLIT_V (1.0f)//�c�̕�����
#define MAX_ANIMATION_TIME (10)//�ő�A�j���[�V��������
#define MAX_ANIMATION_PATTERN (8)//�ő�p�^�[����
#define MAX_SIZE_X (120.0f)//���̃T�C�Y(���@)
#define MAX_SIZE_Y (120.0f)//�c�̃T�C�Y(���@)

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR = 0,
	PLAYERSTATE_NORMAL,
	PLAYERSTATE_DAMAGE,
	PLAYERSTATE_DEATH,
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 rot;//z��
	float fLength;//�Ίp���̒���
	float fAngle;//�Ίp���̊p�x
	//bool bUse;//�g�p���Ă��邩
	bool bHit;//�e����������
	int nLife;//���@�̗̑�
	int nCntAnimState;//��Ԃ��J�E���g
	int nCntState;//�J�E���^�[
	PLAYERSTATE state;//�v���C���[�̏��
	bool bDisp;//�\�����邩���Ȃ���
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);//�v���C���[�̏�����
void UninitPlayer(void);//�v���C���[�̏I��
void UpdatePlayer(void);//�v���C���[�̍X�V����
void DrawPlayer(void);//�v���C���[�̕`�揈��
void HitPlayer(int nDamage);//�e���v���C���[�ɓ����������̏���(���@�̓����蔻��)
void GetKeyPlayer(void);//�L�[���͏����擾
Player* GetPlayer(void);//�v���C���[���擾
void GetJoypadPlayer(void);//�W���C�p�b�h�����擾

#endif