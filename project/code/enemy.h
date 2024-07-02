//*****************************************************
//
// ��s���𑖂�Ԃ̏���[car.h]
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

	struct SInfoRoadPoint
	{// �ӂɕK�v�ȏ��
		D3DXVECTOR3 pos;
		SInfoRoadPoint() : pos({ 0.0f,0.0f,0.0f }) {}
	};

	CEnemy(int nPriority = 4);	// �R���X�g���N�^
	~CEnemy();	                // �f�X�g���N�^

	HRESULT Init(void);         // ����������
	void Uninit(void);          // �I������
	void Update(void);          // �X�V����
	void Draw(void);            // �`�揈��
	static CEnemy* Create();      // ��������

private:

	// ���
	enum STATE
	{
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_MAX
	};

	// ���
	struct SInfo
	{
		STATE state;

	};

	SInfo m_Info;               // ���
	static CEnemy *m_pEnemy;    // �������g�̃|�C���^
	CCutMullSpline *m_pSpline;	// �X�v���C��
	std::vector<SInfoRoadPoint> m_aRoadPoint;

	int m_nIdx = 1;
	float m_t = 0.0f;
};

#endif