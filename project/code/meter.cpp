//*****************************************************
//
// �^�C���̏���[timer.cpp]
// Author:�X��x��
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "meter.h"
#include "manager.h"
#include "debugproc.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const int VALUE = 240;			// �l
	const int PLACE = 3;			// ����
	const float WIDTH = SCREEN_WIDTH * 0.5f;		// ��
	const float HEIGHT = SCREEN_HEIGHT * 0.5f;		// ����
}

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CMeter::CMeter(int nPriority)
{
	m_nMeter = 0;			// ���݂̃��[�^�[�l
	m_nCntMeter = 0;		// ���[�^�[���Z
	m_pNumber = nullptr;	// �i���o�[�̃|�C���^
	m_pPlayer = nullptr;	// �v���C���[�̃|�C���^
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CMeter::~CMeter()
{
}

//=====================================================
// ��������
//=====================================================
CMeter* CMeter::Create(void)
{
	// �C���X�^���X����
	CMeter* pMeter = new CMeter;

	// ������
	pMeter->Init();

	return pMeter;
}

//=====================================================
// ����������
//=====================================================
HRESULT CMeter::Init(void)
{
	// �v���C���[�̏��擾
	m_pPlayer = CPlayer::GetInstance();

	// ���x
	m_nMeter = 0;

	// ����
	m_pNumber = CNumber::Create(PLACE, 0);

	// �ʒu�ݒ�
	m_pNumber->SetPosition(D3DXVECTOR3(1000, 600.0f, 0.0f));

	// �T�C�Y����
	m_pNumber->SetSizeAll(35.0f, 35.0f);

	// �F�ݒ�
	m_pNumber->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CMeter::Uninit(void)
{
	m_pNumber = nullptr;

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CMeter::Update(void)
{
	// �f���^�^�C���擾
	float fDeltaTime = CManager::GetDeltaTime();

	Acceleration();
}

//=====================================================
// ����������
//=====================================================
void CMeter::Acceleration()
{
	// ���x�擾
	float fSpeed = m_pPlayer->GetParam().fSpeedMax;

	// �J�E���^�[���Z
	m_nCntMeter++;

	if (m_nCntMeter > 60)
	{
		m_nCntMeter = 0;

		if (m_nMeter >= 1)
		{// ���[�^�[���Z
			m_nMeter++;
		}
	}

	// �b�̌v�Z
	int nSecond = m_nMeter % VALUE;

	if (m_pNumber != nullptr)
	{// �b�\���̐���
		m_pNumber->SetValue(nSecond, PLACE);
	}

	if (m_nMeter <= 0)
	{
		m_nMeter = 0;
	}
}

//=====================================================
// ����������
//=====================================================
void CMeter::Deceleration()
{
	// ���x�擾
	float fSpeed = m_pPlayer->GetParam().fSpeedMax;

	// �J�E���^�[���Z
	m_nCntMeter++;

	if (m_nCntMeter > 60)
	{
		m_nCntMeter = 0;

		if (m_nMeter >= 1)
		{// ���[�^�[���Z
			m_nMeter--;
		}
	}

	// �b�̌v�Z
	int nSecond = m_nMeter % VALUE;

	if (m_pNumber != nullptr)
	{// �b�\���̐���
		m_pNumber->SetValue(nSecond, PLACE);
	}

	if (m_nMeter <= 0)
	{
		m_nMeter = 0;
	}
}
