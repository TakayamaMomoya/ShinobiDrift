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
const int TIME_DIGIT = 2;			// ���̌���
const int MINUTES_LIMIT = 10;		// ���̏���l
const int SECOND_PLACE = 3;			// �b�̌���
const int SECOND_LIMIT = 300;		// �b�̏���l
const int MILLI_PLACE = 2;			// �~���b�̌���
const int MILLI_LIMIT = 99;			// �~���b�̏��
const float MILLI_WIDTH = SCREEN_WIDTH * 0.65f;		// �~���b��X���W
const float SECOND_WIDTH = SCREEN_WIDTH * 0.5f;		// �b��X���W
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CTimer* CTimer::s_pTimer = nullptr;

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CTimer::CTimer(int nPriority) : CObject(nPriority)
{
	m_fMinutes = 0.0f;			// ���݂̎���(��)
	m_fSecond = 0.0f;			// ���݂̎���(�b)
	m_fMilli = 0.0f;			// ���݂̎���(�~���b)
	m_pMinutes = nullptr;		// ���\���̃|�C���^
	m_pSecond = nullptr;		// �b�\���p�̃|�C���^
	m_pMilli = nullptr;			// �~���Z�J���h�\���p�̃|�C���^
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
	if (s_pTimer == nullptr)
	{// �C���X�^���X����
		s_pTimer = new CTimer;
	}

	if (s_pTimer != nullptr)
	{// ������
		s_pTimer->Init();

		//if (s_pTimer->m_pMinutes == nullptr)
		//{// ���\��
		//	// ����
		//	s_pTimer->m_pMinutes = CNumber::Create(TIME_DIGIT, );

		//	// �ʒu
		//	s_pTimer->m_pMinutes;

		//	// �T�C�Y
		//	s_pTimer->m_pMinutes;
		//}

		if (s_pTimer->m_pSecond == nullptr)
		{// �b�\��
			// ����
			s_pTimer->m_pSecond = CNumber::Create(SECOND_PLACE, SECOND_LIMIT);

			// �ʒu
			s_pTimer->m_pSecond->SetPosition(D3DXVECTOR3(SECOND_WIDTH, 75.0f, 0.0f));

			// �T�C�Y
			s_pTimer->m_pSecond->SetSizeAll(35.0f, 35.0f);
		}

		if (s_pTimer->m_pMilli == nullptr)
		{// �~���b�\��
			// ����
			s_pTimer->m_pMilli = CNumber::Create(MILLI_PLACE, MILLI_LIMIT);

			// �ʒu
			s_pTimer->m_pMilli->SetPosition(D3DXVECTOR3(MILLI_WIDTH, 85.0f, 0.0f));

			// �T�C�Y
			s_pTimer->m_pMilli->SetSizeAll(25.0f,15.0f);
		}
	}

	return s_pTimer;
}

//=====================================================
// ����������
//=====================================================
HRESULT CTimer::Init(void)
{
	// ���E�b�E�~���b�̏�����
	m_fMinutes = 0.0f;
	m_fSecond = 0.0f;
	m_fMilli = 0.0f;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTimer::Uninit(void)
{
	// �ÓI�����o�ϐ��̏I��
	if (s_pTimer != nullptr)
		s_pTimer = nullptr;

	if (m_pMinutes != nullptr)
	{
		m_pMinutes->Uninit();
		m_pMinutes = nullptr;
	}

	if (m_pSecond != nullptr)
	{
		m_pSecond->Uninit();
		m_pSecond = nullptr;
	}

	if (m_pMilli != nullptr)
	{
		m_pMilli->Uninit();
		m_pMilli = nullptr;
	}

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CTimer::Update(void)
{
	// �b�̍X�V
	Second();
}

//=====================================================
// �b�̍X�V
//=====================================================
void CTimer::Second()
{
	// �f���^�^�C���擾
	float fDeltaTime = CManager::GetDeltaTime();

	// �f���^�^�C��(���A������)���Z
	m_fSecond += fDeltaTime;

	// �b�̌v�Z
	int nSecond = (int)m_fSecond % SECOND_LIMIT;

	// �b�\���̐���
	if (m_pSecond != nullptr)
		m_pSecond->SetValue(nSecond, SECOND_PLACE);

	// �b�̏���l�����Ȃ��悤��
	if (nSecond >= SECOND_LIMIT)
		m_fSecond = SECOND_LIMIT;

	// �~���b�̍X�V
	MilliSecond();
}

//=====================================================
// �~���b�X�V
//=====================================================
void CTimer::MilliSecond()
{
	// �f���^�^�C���擾
	float fDeltaTime = CManager::GetDeltaTime();

	// �f���^�^�C��(���A������)���Z
	m_fMilli += fDeltaTime;

	m_fMilli = m_fSecond * 100;

	// �~���b�̌v�Z
	int nMsecond = (int)m_fMilli % MILLI_LIMIT;

	// �~���b�\���̐���
	if (m_pMilli != nullptr)
		m_pMilli->SetValue(nMsecond, MILLI_PLACE);

	// �~���b�̏���l�����Ȃ��悤��
	if (nMsecond >= MILLI_LIMIT)
		m_fMilli = MILLI_LIMIT;
}
