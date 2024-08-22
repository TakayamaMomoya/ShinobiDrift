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
#include "goal.h"
#include "player.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int MINUTES_LIMIT = 9;		// ���̏���l
const int SECOND_LIMIT = 59;		// �b�̏���l
const int MILLI_LIMIT = 99;			// �~���b�̏��
const int MINUTES_DIGIT = 1;		// ���\���̌���
const int TIME_DIGIT = 2;			// ���ꂼ��̌���
const float MAGNIFICATION = 100.0f;	// �|����{��
const float MINUTES_WIDTH = 0.44f;	// ����X���W
const float SECOND_WIDTH = 0.5f;		// �b��X���W
const float MILLI_WIDTH = 0.6f;		// �~���b��X���W
D3DXVECTOR2 SIZE_NORMAL_NUM = { 0.02f, 0.04f };	// �ʏ퐔���̃T�C�Y
D3DXVECTOR2 SIZE_MINI_NUM = { 0.014f, 0.028f };	// �~�j�����̃T�C�Y
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CTimer::CTimer()
{
	m_fSecond = 0.0f;			// ���݂̎���(�b)
	m_bStop = false;
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
	CTimer *pTimer = nullptr;

	pTimer = new CTimer;

	if (pTimer != nullptr)
	{// ������
		pTimer->Init();
	}

	return pTimer;
}

//=====================================================
// ����������
//=====================================================
HRESULT CTimer::Init(void)
{
	// ���E�b�E�~���b�̏�����
	m_fSecond = 0.0f;

	m_bStop = false;	// �^�C�}�[��~�̃t���O

	if (m_pMinutes == nullptr)
	{// ���\��
		// �����E�ʒu�A�T�C�Y�ݒ�
		m_pMinutes = CNumber::Create(MINUTES_DIGIT, MINUTES_LIMIT);
		m_pMinutes->SetPosition(D3DXVECTOR3(MINUTES_WIDTH, SIZE_MINI_NUM.y * 2.0f + 0.01f, 0.0f));
		m_pMinutes->SetSizeAll(SIZE_NORMAL_NUM.x, SIZE_NORMAL_NUM.y);
	}

	if (m_pSecond == nullptr)
	{// �b�\��
		// �����E�ʒu�A�T�C�Y�ݒ�
		m_pSecond = CNumber::Create(TIME_DIGIT, SECOND_LIMIT);
		m_pSecond->SetPosition(D3DXVECTOR3(SECOND_WIDTH, SIZE_MINI_NUM.y * 2.0f + 0.01f , 0.0f));
		m_pSecond->SetSizeAll(SIZE_NORMAL_NUM.x, SIZE_NORMAL_NUM.y);
	}

	if (m_pMilli == nullptr)
	{// �~���b�\��
		// �����E�ʒu�A�T�C�Y�ݒ�
		m_pMilli = CNumber::Create(TIME_DIGIT, MILLI_LIMIT);
		m_pMilli->SetPosition(D3DXVECTOR3(MILLI_WIDTH, SIZE_MINI_NUM.y * 2.0f + 0.01f, 0.0f));
		m_pMilli->SetSizeAll(SIZE_MINI_NUM.x, SIZE_MINI_NUM.y);
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTimer::Uninit(void)
{
	if (m_pMinutes != nullptr)
	{// ���̏I��
		m_pMinutes->Uninit();
		m_pMinutes = nullptr;
	}

	if (m_pSecond != nullptr)
	{// �b�̏I��
		m_pSecond->Uninit();
		m_pSecond = nullptr;
	}

	if (m_pMilli != nullptr)
	{// �~���b�̏I��
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
	// ���̍X�V
	if (!m_bStop)
	{
		Minutes();
	}
}

//=====================================================
// ���̍X�V
//=====================================================
void CTimer::Minutes()
{
	// �b�̍X�V
	Second();

	// ���̌v�Z
	int nMinutes = (int)m_fSecond / SECOND_LIMIT;

	// ���̏���l�����Ȃ��悤��
	if (nMinutes >= MINUTES_LIMIT)
		nMinutes = MINUTES_LIMIT;

	// ���\��
	if (m_pMinutes != nullptr)
		m_pMinutes->SetValue(nMinutes, MINUTES_DIGIT);
}

//=====================================================
// �b�̍X�V
//=====================================================
void CTimer::Second()
{
	// �~���b�̍X�V
	MilliSecond();

	// �b�̌v�Z
	int nSecond = (int)m_fSecond % SECOND_LIMIT;

	// �b�\��
	if (m_pSecond != nullptr)
		m_pSecond->SetValue(nSecond, TIME_DIGIT);
}

//=====================================================
// �~���b�X�V
//=====================================================
void CTimer::MilliSecond()
{
	// �b��100�{
	int nMilli = (int)(m_fSecond * MAGNIFICATION);

	// �~���b�̌v�Z
	nMilli = nMilli % (int)MAGNIFICATION;

	// �~���b�\��
	if (m_pMilli != nullptr)
		m_pMilli->SetValue(nMilli, TIME_DIGIT);
}
