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
class CCutMullSpline;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyBehaviour
{// �r�w�C�r�A�̊��N���X
public:
	CEnemyBehaviour() {};	// �R���X�g���N�^
	virtual ~CEnemyBehaviour() {};	 // �f�X�g���N�^

	// �����o�֐�
	virtual void Init(CEnemy *pEnemy) = 0;	// ����������
	virtual void Uninit(CEnemy *pEnemy) = 0;	// �I������
	virtual void Update(CEnemy *pEnemy) = 0;	// �X�V����

private:
};

class CEnemyBehaviourChasePlayer : public CEnemyBehaviour
{// �v���C���[�̒ǐ�
public:
	CEnemyBehaviourChasePlayer();	// �R���X�g���N�^
	virtual ~CEnemyBehaviourChasePlayer();	 // �f�X�g���N�^

	// �����o�֐�
	void Init(CEnemy *pEnemy) override;	// ����������
	void Uninit(CEnemy *pEnemy) override;	// �I������
	void Update(CEnemy *pEnemy) override;	// �X�V����

private:
	// �����o�֐�
	void CalcSpeed(CEnemy *pEnemy);	// �X�s�[�h�̌v�Z
	void InterpolatePosition(CEnemy *pEnemy);	// �ʒu�̕��
	void ControllRot(CEnemy *pEnemy);	// �����̐���
	void Debug(CEnemy *pEnemy);	// �f�o�b�O�\��

	// �����o�ϐ�
	CCutMullSpline *m_pSpline;	// �X�v���C��
	std::vector<D3DXVECTOR3> m_vPos;	// �f�[�^�_�̃x�N�^�[
	int m_nIdx = 1;	// �X�v���C���̔ԍ�
	float m_fSpeed;	// ���x
	float m_fSpeedDefault;	// ��ɂ��鑬�x
	float m_fRate;
	float m_fRateOld;	// �O��̃X�v���C���̊���
};

#endif