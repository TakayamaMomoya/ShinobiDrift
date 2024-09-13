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
#include "UI.h"
#include "texture.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int MINUTES_LIMIT = 9;	// ���̏���l
const int SECOND_LIMIT = 59;	// �b�̏���l
const int MILLI_LIMIT = 99;	// �~���b�̏��
const int MINUTES_DIGIT = 2;	// ���\���̌���
const int TIME_DIGIT = 2;	// ���ꂼ��̌���
const float MAGNIFICATION = 100.0f;	// �|����{��
const float DIST_NUMBER = 0.03f;	// �����Ԃ̋���
D3DXVECTOR2 SIZE_NORMAL_NUM = { 0.02f, 0.06f };	// �ʏ퐔���̃T�C�Y
D3DXVECTOR2 SIZE_MINI_NUM = { 0.014f, 0.028f };	// �~�j�����̃T�C�Y
D3DXVECTOR3 POS_INITIAL = { 0.5f,0.08f,0.0f };	// �����ʒu
const string PATH_TEX_COLON = "data\\TEXTURE\\UI\\colon.png";	// �R�����̃e�N�X�`���p�X
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CTimer::CTimer()
{
	m_fSecond = 0.0f;
	m_fScaleNumber = 0.0f;
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
	m_fSecond = 0.0f;	// �b�̏�����
	m_fScaleNumber = 1.0f;	// �����X�P�[���ݒ�
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

	// �����̐���
	for (int i = 0; i < E_Number::NUMBER_MAX; i++)
	{
		m_aNumber[i] = CNumber::Create(aDigit[i], 0);	// �����̐���
	}

	// �R�����̐���
	m_aColon.resize(E_Number::NUMBER_MAX - 1);

	for (int i = 0; i < E_Number::NUMBER_MAX - 1; i++)
	{
		m_aColon[i] = CUI::Create();

		if (m_aColon[i] == nullptr)
			continue;

		int nIdxTexture = Texture::GetIdx(&PATH_TEX_COLON[0]);
		m_aColon[i]->SetIdxTexture(nIdxTexture);
	}

	// �����̃g�����X�t�H�[���̐ݒ�
	TransformNumber();

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

	for (auto it : m_aColon)
	{
		it->Uninit();
	}

	m_aColon.clear();

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
// �����̃g�����X�t�H�[���ݒ�
//=====================================================
void CTimer::TransformNumber()
{
	if (m_aNumber.empty())
		return;

	int aDigit[E_Number::NUMBER_MAX] =
	{// ����
		MINUTES_DIGIT,
		TIME_DIGIT,
		TIME_DIGIT
	};

	D3DXVECTOR2 aSize[E_Number::NUMBER_MAX] =
	{// �����̃T�C�Y
		SIZE_NORMAL_NUM * m_fScaleNumber,
		SIZE_NORMAL_NUM * m_fScaleNumber,
		SIZE_NORMAL_NUM * m_fScaleNumber
	};

	D3DXVECTOR3 posBase = GetPosition();

	// �������A�������Đݒ�
	for (int i = 0; i < E_Number::NUMBER_MAX; i++)
	{
		if (m_aNumber[i] == nullptr)
			continue;

		// �Q�Ƃ���T�C�Y�̔ԍ�
		int nIdx = i;

		if (nIdx > 0)
			nIdx--;	// 0�ԖڂłȂ���ΑO��̃T�C�Y���Q�Ƃ���

		// �p�����[�^�[�ݒ�
		float fWidth = aSize[nIdx].x * aDigit[nIdx] * 2 + DIST_NUMBER * m_fScaleNumber;	// �T�C�Y�ɉ����Đ����Ԃ̃X�y�[�X��������
		D3DXVECTOR3 pos = { posBase.x + fWidth * (i - 1), posBase.y, 0.0f };
		m_aNumber[i]->SetPosition(pos);
		m_aNumber[i]->SetSizeAll(aSize[i].x, aSize[i].y);

		if (i == 0)	// 0�ȏ�̂Ƃ���������Ȃ�����
			continue;
		
		// �R�����̈ʒu��ݒ�
		int nIdxColon = i - 1;

		if (m_aColon[nIdxColon] != nullptr)
		{
			float fPosXLast = m_aNumber[i - 1]->GetPosition().x + aDigit[i - 1] * aSize[i - 1].x;
			D3DXVECTOR3 posColon = { (pos.x + fPosXLast) / 2, pos.y, 0.0f };
			m_aColon[nIdxColon]->SetPosition(posColon);	// �ʒu
			m_aColon[nIdxColon]->SetSize(aSize[i].x, aSize[i].y);	// �T�C�Y
			m_aColon[nIdxColon]->SetVtx();
		}
	}
}

//=====================================================
// �ʒu�̐ݒ�
//=====================================================
void CTimer::SetPosition(D3DXVECTOR3 pos)
{
	CGameObject::SetPosition(pos);

	// �����̃g�����X�t�H�[���̐ݒ�
	TransformNumber();
}

//=====================================================
// �����̃X�P�[���̐ݒ�
//=====================================================
void CTimer::SetScaleNumber(float fScale)
{
	m_fScaleNumber = fScale;

	// �����̃g�����X�t�H�[���̐ݒ�
	TransformNumber();
}

//=====================================================
// �F�̐ݒ�
//=====================================================
void CTimer::SetColor(E_Number number, D3DXCOLOR col)
{
	if (number < 0 || number > E_Number::NUMBER_MAX)
		return;

	if (number == E_Number::NUMBER_MAX)
	{// �S�����̐F�ݒ�
		for (auto it : m_aNumber)	// ����
			it->SetColor(col);

		for (auto it : m_aColon)	// �R����
			it->SetCol(col);
	}
	else
	{// �e�����̐F�ݒ�
		m_aNumber[number]->SetColor(col);
	}
}

//=====================================================
// �F�̎擾
//=====================================================
D3DXCOLOR CTimer::GetColor(E_Number number)
{
	if (number < 0 || number >= E_Number::NUMBER_MAX)
		return D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	return m_aNumber[number]->GetColor();
}

//=====================================================
// �`�揈��
//=====================================================
void CTimer::Draw()
{

}