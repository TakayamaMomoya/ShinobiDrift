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

//*****************************************************
// �O����`
//*****************************************************
class CCutMullSpline;

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
		float fRate;            // �X�v���C���̊���
	};

	// �����o�֐�
	void CalcSpeed(void);	// �X�s�[�h�̌v�Z
	void InterpolatePosition(void);	// �ʒu�̕��
	void Debug(void);	// �f�o�b�O�\��

	// �����o�ϐ�
	SInfo m_Info;                     // ���
	static CEnemy *m_pEnemy;          // �������g�̃|�C���^
	CCutMullSpline *m_pSpline;	      // �X�v���C��
	std::vector<D3DXVECTOR3> m_vPos;  // �f�[�^�_�̃x�N�^�[
	int m_nIdx = 1;	// �X�v���C���̔ԍ�
	float m_fSpeed = 0.0f;	// ���x
	float m_fSpeedDefault;	// ��ɂ��鑬�x
	float m_fRateOld = 0.0f;	// �O��̃X�v���C���̊���
};

#endif