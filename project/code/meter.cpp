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
#include "texture.h"
#include "input.h"
#include "inputkeyboard.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int SECOND = 140;		// ���[�^�[�̕\���l
const int PLACE = 3;		// ����
const float WIDTH = SCREEN_WIDTH * 0.80f;		// ��
const float HEIGHT = SCREEN_HEIGHT * 0.9f;		// ����
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
	m_nIdxTexture = 0;		// �e�N�X�`���ԍ�
	m_fRot = 0.0f;			// ����
	m_pNumber = nullptr;	// �i���o�[�̃|�C���^
	m_pPlayer = nullptr;	// �v���C���[�̃|�C���^
	m_pUI = nullptr;		// UI�̃|�C���^
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
HRESULT CMeter::Init()
{
	// ���x
	m_NowMeter = 0;

	// �J�E���g���Z
	m_nCntMeter = 0;

	// �e�N�X�`���ԍ�
	m_nIdxTexture = 0;

	// �v���C���[�̏��擾
	if (m_pPlayer == nullptr)
		m_pPlayer = CPlayer::GetInstance();

	// �e�N�X�`�����̎擾
	CTexture* pTexture = CTexture::GetInstance();

	// �e�N�X�`���ԍ�
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\UI\\Needle.png");

	if (m_pUI == nullptr)
	{
		// ����
		m_pUI = CUI::Create();

		// �e�N�X�`���ݒ�
		m_pUI->SetIdxTexture(m_nIdxTexture);

		// �ʒu�ݒ�
		m_pUI->SetPosition(D3DXVECTOR3(1100, 600.0f, 0.0f));

		// �T�C�Y�ݒ�
		m_pUI->SetSize(75.0f, 100.0f);

		// �����ݒ�
		m_pUI->SetRotation(0.0f);

		// ���_���ݒ�
		m_pUI->SetVtx();

		// �F�ݒ�
		m_pUI->SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
	}

	if (m_pNumber == nullptr)
	{
		// ����
		m_pNumber = CNumber::Create(PLACE, 0);

		// �ʒu�ݒ�
		m_pNumber->SetPosition(D3DXVECTOR3(WIDTH, HEIGHT, 0.0f));

		// �T�C�Y����
		m_pNumber->SetSizeAll(30.0f, 30.0f);

		// �F�ݒ�
		m_pNumber->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CMeter::Uninit(void)
{
	if (m_pNumber != nullptr)
		m_pNumber = nullptr;

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	if (m_pUI != nullptr)
		m_pUI = nullptr;

	if (m_pMeter != nullptr)
		m_pMeter = nullptr;

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CMeter::Update(void)
{
	// ���[�^�[�l
	Acceleration();

	CDebugProc::GetInstance()->Print("\n���݂̌���[%f]", m_fRot);
}

//=====================================================
// ���[�^�[�l����
//=====================================================
void CMeter::Acceleration()
{
	// �f���^�^�C���擾
	float fDeltaTime = CManager::GetDeltaTime();

	if (m_pPlayer != nullptr)
	{
		// ���x�擾
		float fPlayerSpeed = m_pPlayer->GetSpeed();

		// �ō����x
		float fMaxSpeed = m_pPlayer->GetParam().fSpeedMax;


		// ���x�擾
		m_NowMeter = (int)fPlayerSpeed;

		if (m_NowMeter >= fMaxSpeed)
		{// �v���C���[�p�����[�^�[�̑��x�𒴂��Ȃ��悤��
			m_NowMeter = (int)fMaxSpeed;
		}
	}

	// ���[�^�[�l�̌v�Z
	int Meter = m_NowMeter % SECOND;

	if (m_pNumber != nullptr)
	{// �l�\���̐���
		m_pNumber->SetValue(Meter, PLACE);
	}

	if (m_NowMeter <= 0)
	{// �}�C�i�X�̒l�ɂ����Ȃ��悤��
		m_NowMeter = 0;
	}
}

//=====================================================
// ���[�^�[�j����
//=====================================================
void CMeter::Needle()
{
	if (m_pUI != nullptr)
	{
		// �����擾
		m_fRot = m_pUI->GetRotation();

		// 
		m_fRot;

		// �����ݒ�
		m_pUI->SetRotation(m_fRot);
	}
}
