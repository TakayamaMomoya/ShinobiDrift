//*****************************************************
//
// �G�l�~�[�r�w�C�r�A[enemyBehaviour.h]
// Author:�匴�叫
//
//*****************************************************
#ifndef _ENEMYBEHAVIOUR_H_
#define _ENEMYBEHAVIOUR_H_

//*****************************************************
// �C���N���[�h
//*****************************************************

//*****************************************************
// �O����`
//*****************************************************
class CEnemy;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyBehaviour
{// �r�w�C�r�A�̊��N���X
public:
	CEnemyBehaviour() {};	// �R���X�g���N�^
	virtual ~CEnemyBehaviour() {};	 // �f�X�g���N�^

	// �����o�ϐ�
	virtual void Init(CEnemy *pEnemy) = 0;	// ����������
	virtual void Uninit(CEnemy *pEnemy) = 0;	// �I������
	virtual void Update(CEnemy *pEnemy) = 0;	// �X�V����

private:
};

class CEnemyBehaviourChasePlayer : public CEnemyBehaviour
{// �v���C���[�̒ǐ�
	CEnemyBehaviourChasePlayer();	// �R���X�g���N�^
	virtual ~CEnemyBehaviourChasePlayer();	 // �f�X�g���N�^

	// �����o�ϐ�
	void Init(CEnemy *pEnemy) override;	// ����������
	void Uninit(CEnemy *pEnemy) override;	// �I������
	void Update(CEnemy *pEnemy) override;	// �X�V����
};

#endif