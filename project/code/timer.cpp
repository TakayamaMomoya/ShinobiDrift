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
const int TIME_PLACE = 3;		// ����
const int TIME_LIMIT = 5;		// �^�C���̏���l
const float TIME_WIDTH = SCREEN_WIDTH * 0.5f;		// ��
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
	m_fSeconds = 0.0f;		// ���݂̎���
	m_pNumber = nullptr;	// �i���o�[�̃|�C���^
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
	m_fSeconds = 0.0f;

	// ����
	if(m_pNumber == nullptr)
	m_pNumber = CNumber::Create(TIME_PLACE, TIME_LIMIT);

	if (m_pNumber != nullptr)
	{
		// �ʒu�ݒ�
		m_pNumber->SetPosition(D3DXVECTOR3(TIME_WIDTH, 75.0f, 0.0f));

		// �T�C�Y����
		m_pNumber->SetSizeAll(35.0f, 35.0f);
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTimer::Uninit(void)
{
	if (m_pNumber != nullptr)
	{
		m_pNumber->Uninit();
		m_pNumber = nullptr;
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

	// �^�C�}�[���Z
	m_fSeconds += fDeltaTime;

	// �b�̌v�Z
	int nSecond = (int)m_fSeconds % 60;

	// �b�\���̐���
	if (m_pNumber != nullptr)
		m_pNumber->SetValue(nSecond, TIME_PLACE);

	// �^�C�}�[�̏���l�����Ȃ��悤��
	if (nSecond >= TIME_LIMIT)
		m_fSeconds = TIME_LIMIT;

	//CDebugProc::GetInstance()->Print("\n�f���^�^�C��[%f]", fDeltaTime);
}
