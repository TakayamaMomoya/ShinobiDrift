//*****************************************************
//
//�^�C���̏���[timer.cpp]
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
	const int VALUE = 120;			// �l
	const int PLACE = 3;			// ����
	const float WIDTH = SCREEN_WIDTH * 0.5f;		// ��
	const float HEIGHT = SCREEN_HEIGHT * 0.5f;		// ����
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CTimer::CTimer(int nPriority)
{
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
	// �C���X�^���X����
	CTimer* pTimer = new CTimer;

	// ������
	pTimer->Init();

	return pTimer;
}

//=====================================================
// ����������
//=====================================================
HRESULT CTimer::Init(void)
{
	m_nSeconds = VALUE;

	// ����
	m_pNumber = CNumber::Create(PLACE, VALUE);

	// �ʒu�ݒ�
	m_pNumber->SetPosition(D3DXVECTOR3(WIDTH, 75.0f, 0.0f));

	// �T�C�Y����
	m_pNumber->SetSizeAll(35.0f, 35.0f);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTimer::Uninit(void)
{
	m_pNumber = nullptr;

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

	// �J�E���^�[���Z
	m_nCntSeconds++;

	if (m_nCntSeconds > 60)
	{
		m_nCntSeconds = 0;

		if (m_nSeconds >= 1)
		{
			m_nSeconds--;
		}
	}

	// �b�̌v�Z
	int nSecond = m_nSeconds % VALUE;

	if (m_pNumber != nullptr)
	{// �b�\���̐���
		m_pNumber->SetValue(nSecond, PLACE);
	}

	if (m_nSeconds <= 0)
	{
		m_nSeconds = 0;
	}
}

//=====================================================
// �ݒ�
//=====================================================
void CTimer::Set()
{
	int nSeconds = m_nSeconds % 60;

	if (m_pNumber != nullptr)
	{
		m_pNumber->SetValue(nSeconds, PLACE);
	}
}
