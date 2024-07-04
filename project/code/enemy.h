//*****************************************************
//
// �G�l�~�[�̏���[enemy.h]
// Author:�匴�叫
//
//*****************************************************

#ifndef _CAR_H_
#define _CAR_H_

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

	// ���
	enum STATE
	{
		STATE_NONE = 0,	         // ���ł��Ȃ����
		STATE_NORMAL,	         // �ʏ���
		STATE_MAX
	};

	// ���
	struct SInfo
	{
		STATE state;             // ���
		float fSpeed;            // ����
	};

	SInfo m_Info;                     // ���
	static CEnemy *m_pEnemy;          // �������g�̃|�C���^
	CMotion* m_pEnemyNinja;           // �o�C�N�ɏ���Ă���E��
	CCutMullSpline *m_pSpline;	      // �X�v���C��
	std::vector<D3DXVECTOR3> m_vPos;  // �f�[�^�_�̃x�N�^�[

	int m_nIdx = 1;
	int m_nSize = 0;
	float m_t = 0.0f;
};

#endif