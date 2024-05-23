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
	const int SECOND = 70;		// ���[�^�[�̕\���l
	const int PLACE = 2;		// ����
}

//=====================================================
// �ÓI�����o�ϐ�
//=====================================================
CMeter* CMeter::m_pMeter = nullptr;

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CMeter::CMeter(int nPriority)
{
	m_NowMeter = 0;			// ���݂̃��[�^�[�l
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
	if (m_pMeter == nullptr)
	{// �C���X�^���X����
		m_pMeter = new CMeter;

		if (m_pMeter != nullptr)
		{// ������
			m_pMeter->Init();
		}
	}

	return m_pMeter;
}

//=====================================================
// ����������
//=====================================================
HRESULT CMeter::Init(void)
{
	// �v���C���[�̏��擾
	m_pPlayer = CPlayer::GetInstance();

	// ���x
	m_NowMeter = 0;

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

	m_pMeter = nullptr;

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CMeter::Update(void)
{
	// ���[�^�[�l�̉��Z
	Acceleration();
}

//=====================================================
// ����������
//=====================================================
void CMeter::Acceleration()
{
	// �f���^�^�C���擾
	float fDeltaTime = CManager::GetDeltaTime();

	// ���x�擾
	float fSpeed = m_pPlayer->GetSpeed();
	float fMaxSpeed = m_pPlayer->GetParam().fSpeedMax;

	m_NowMeter = fSpeed;

	if (m_NowMeter >= fMaxSpeed)
	{// �v���C���[�p�����[�^�[�̑��x�𒴂��Ȃ��悤��
		m_NowMeter = fMaxSpeed;
	}

	// ���[�^�[�l�̌v�Z
	int Meter = m_NowMeter % SECOND;

	if (m_pNumber != nullptr)
	{// �b�\���̐���
		m_pNumber->SetValue(Meter, PLACE);
	}

	if (m_NowMeter <= 0)
	{// �}�C�i�X�̒l�ɂ����Ȃ��悤��
		m_NowMeter = 0;
	}
}
