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
const float DIST_NUMBER = 0.015f;	// �����Ԃ̋���
D3DXVECTOR2 SIZE_NORMAL_NUM = { 0.02f, 0.04f };	// �ʏ퐔���̃T�C�Y
D3DXVECTOR2 SIZE_MINI_NUM = { 0.014f, 0.028f };	// �~�j�����̃T�C�Y
D3DXVECTOR3 POS_INITIAL = { 0.5f,0.04f,0.0f };	// �����ʒu
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

	// �����ʒu�̐ݒ�
	SetPosition(POS_INITIAL);

	// �����̔z��̃��T�C�Y
	m_aNumber.resize(E_Number::NUMBER_MAX);

	int aDigit[E_Number::NUMBER_MAX] =
	{// ����
		MINUTES_DIGIT,
		TIME_DIGIT,
		TIME_DIGIT
	};

	D3DXVECTOR2 aSize[E_Number::NUMBER_MAX] =
	{// �����̃T�C�Y
		SIZE_NORMAL_NUM,
		SIZE_NORMAL_NUM,
		SIZE_MINI_NUM
	};

	// �������A�������Đݒ�
	for (int i = 0; i < E_Number::NUMBER_MAX; i++)
	{
		m_aNumber[i] = CNumber::Create(aDigit[i], 0);	// �����̐���

		if (m_aNumber[i] == nullptr)
			continue;

		// �Q�Ƃ���T�C�Y�̔ԍ�
		int nIdx = i;

		if (nIdx > 0)
			nIdx--;	// 0�ԖڂłȂ���ΑO��̃T�C�Y���Q�Ƃ���

		// �p�����[�^�[�ݒ�
		float fWidth = aSize[nIdx].x * aDigit[nIdx] * 2 + DIST_NUMBER;	// �T�C�Y�ɉ����Đ����Ԃ̃X�y�[�X��������
		D3DXVECTOR3 pos = { POS_INITIAL.x + fWidth * (i - 1), POS_INITIAL.y, 0.0f };
		m_aNumber[i]->SetPosition(pos);
		m_aNumber[i]->SetSizeAll(aSize[i].x, aSize[i].y);
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTimer::Uninit(void)
{
	for (auto it : m_aNumber)
	{
		it->Uninit();
	}

	m_aNumber.clear();

	// ���g�̔j��
	CGameObject::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CTimer::Update(void)
{
	if (!m_bStop)
	{// �����̍X�V
		UpdateNumber();
	}
}

//=====================================================
// �����̍X�V
//=====================================================
void CTimer::UpdateNumber()
{
	if (m_aNumber.empty())
		return;

	// �l�̗p��
	int aValue[E_Number::NUMBER_MAX] =
	{
		(int)m_fSecond / SECOND_LIMIT,
		(int)m_fSecond % SECOND_LIMIT,
		(int)(m_fSecond * MAGNIFICATION) % (int)MAGNIFICATION
	};

	for (int i = 0; i < E_Number::NUMBER_MAX; i++)
	{
		m_aNumber[i]->SetValue(aValue[i]);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CTimer::Draw()
{

}