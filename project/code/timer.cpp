//*****************************************************
//
// �^�C���̏���[timer.cpp]
// Author:�X��x��
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "timer.h"
#include "manager.h"
#include "debugproc.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int SECOND_PLACE = 3;			// �b�̌���
const int SECOND_LIMIT = 300;		// �b�̏���l
const float SECOND_WIDTH = SCREEN_WIDTH * 0.5f;		// �b��X���W
const int MILLI_PLACE = 2;			// �~���b�̌���
const int MILLI_LIMIT = 60;			// �~���b�̏��
const float MILLI_WIDTH = SCREEN_WIDTH * 0.65f;
const int TIME_CALCULATION = 60;	// �b�v�Z�p
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CTimer* CTimer::m_pTimer = nullptr;

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CTimer::CTimer(int nPriority) : CObject(nPriority)
{
	m_fSecond = 0.0f;			// ���݂̎���(�b)
	m_fMsecond = 0.0f;			// ���݂̎���(�~���b)
	m_pSecond = nullptr;		// �b�\���p�̃|�C���^
	m_pMilliSecond = nullptr;	// �~���Z�J���h�\���p�̃|�C���^
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTimer::~CTimer()
{
}

//=====================================================
// ��������
//=====================================================
CTimer* CTimer::Create(void)
{
	if (m_pTimer == nullptr)
	{// �C���X�^���X����
		m_pTimer = new CTimer;
	}

	if (m_pTimer != nullptr)
	{// ������
		m_pTimer->Init();

		if (m_pTimer->m_pSecond == nullptr)
		{// �b�\��
			// ����
			m_pTimer->m_pSecond = CNumber::Create(SECOND_PLACE, SECOND_LIMIT);

			// �ʒu
			m_pTimer->m_pSecond->SetPosition(D3DXVECTOR3(SECOND_WIDTH, 75.0f, 0.0f));

			// �T�C�Y
			m_pTimer->m_pSecond->SetSizeAll(35.0f, 35.0f);
		}

		if (m_pTimer->m_pMilliSecond == nullptr)
		{// �~���b�\��
			// ����
			m_pTimer->m_pMilliSecond = CNumber::Create(MILLI_PLACE, MILLI_LIMIT);

			// �ʒu
			m_pTimer->m_pMilliSecond->SetPosition(D3DXVECTOR3(MILLI_WIDTH, 85.0f, 0.0f));

			// �T�C�Y
			m_pTimer->m_pMilliSecond->SetSizeAll(25.0f,15.0f);
		}
	}

	return m_pTimer;
}

//=====================================================
// ����������
//=====================================================
HRESULT CTimer::Init(void)
{
	// ���ݎ��Ԃ̏�����
	m_fSecond = 0.0f;

	m_fMsecond = 0.0f;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTimer::Uninit(void)
{
	if (m_pSecond != nullptr)
	{
		m_pSecond->Uninit();
		m_pSecond = nullptr;
	}

	if (m_pMilliSecond != nullptr)
	{
		m_pMilliSecond->Uninit();
		m_pMilliSecond = nullptr;
	}

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CTimer::Update(void)
{
	// �f���^�^�C���擾
	float fDeltaTime = CManager::GetDeltaTime();

	// �f���^�^�C��(���A������)���Z
	m_fSecond += fDeltaTime;

	// �b�̌v�Z
	int nSecond = (int)m_fSecond % TIME_CALCULATION;

	// �~���b�̌v�Z
	int nMsecond;

	// �b�\���̐���
	if (m_pSecond != nullptr)
		m_pSecond->SetValue(nSecond, SECOND_PLACE);

	// �������Ԃ̏���l�����Ȃ��悤��
	if (nSecond >= SECOND_LIMIT)
		m_fSecond = SECOND_LIMIT;
}
