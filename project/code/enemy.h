//*****************************************************
//
// �G�l�~�[�̏���[enemy.h]
// Author:�匴�叫
//
//*****************************************************
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "motion.h"
#include "enemyBehaviour.h"

//*****************************************************
// �O����`
//*****************************************************
class CBehaviourEnemy;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemy : public CMotion
{
public:
	CEnemy(int nPriority = 4);	// �R���X�g���N�^
	~CEnemy();	                // �f�X�g���N�^

	HRESULT Init(void);         // ����������
	void Uninit(void);          // �I������
	void Update(void);          // �X�V����
	void Draw(void);            // �`�揈��
	static CEnemy* Create();    // ��������

private:
	enum STATE
	{// ���
		STATE_NONE = 0,	         // ���ł��Ȃ����
		STATE_NORMAL,	         // �ʏ���
		STATE_MAX
	};
	struct SInfo
	{// ���
		STATE state;             // ���
	};

	// �����o�֐�
	void ReleaseAllBehaviour(void);	// �S�Ẵr�w�C�r�A�̉��

	// �����o�ϐ�
	SInfo m_Info;	// ���
	std::list<CEnemyBehaviour*> m_listBehaviour;	// �r�w�C�r�A�̃��X�g
};

#endif