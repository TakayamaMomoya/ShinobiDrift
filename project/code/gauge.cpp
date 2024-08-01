//*****************************************************
//
// �Q�[�W�̏���[gauge.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "gauge.h"
#include "UI.h"
#include "texture.h"
#include "debugproc.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const D3DXVECTOR2 SIZE_GAUGE_INITIAL = { 0.1f, 0.05f };	// �Q�[�W�̏����T�C�Y
const D3DXVECTOR2 SIZE_FRAME_INITIAL = { SIZE_GAUGE_INITIAL.x * 1.0f, SIZE_GAUGE_INITIAL.y * 1.0f };	// �t���[���̏����T�C�Y
const D3DXVECTOR3 POS_INITIAL = { SIZE_FRAME_INITIAL.x,SIZE_FRAME_INITIAL.y,0.0f };	// �����ʒu
const float TIMELIMIT_TRANSGAUGE_INITIAL = 2.0f;	// �Q�[�W�̕ϓ��ɂ����鎞�Ԃ̏����l
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CGauge::CGauge() : m_fParam(0.0f), m_fParamMax(0.0f), m_fTimerTransGauge(0.0f), m_fTimeLimitTransGauge(0.0f), m_fWidthOld(0.0f)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CGauge::~CGauge()
{

}

//=====================================================
// ��������
//=====================================================
CGauge *CGauge::Create(float fParamMax)
{
	CGauge *pGauge = nullptr;

	pGauge = new CGauge;

	if (pGauge != nullptr)
	{
		pGauge->m_fParamMax = fParamMax;
		pGauge->Init();
	}

	return pGauge;
}

//=====================================================
// ����������
//=====================================================
HRESULT CGauge::Init(void)
{
	// �Q�[�W�{�̂̏����ݒ�
	SetPosition(POS_INITIAL);
	m_fTimeLimitTransGauge = TIMELIMIT_TRANSGAUGE_INITIAL;

	// �|���S���̐���
	CreatePolygon();

	return S_OK;
}

//=====================================================
// �|���S���̐���
//=====================================================
void CGauge::CreatePolygon(void)
{
	m_aPolygon.resize(E_Polygon::POLYGON_MAX);

	m_sizeGauge = SIZE_GAUGE_INITIAL;

	D3DXVECTOR2 aSize[E_Polygon::POLYGON_MAX] = { SIZE_FRAME_INITIAL,SIZE_GAUGE_INITIAL };	// �|���S���̃T�C�Y
	string aPath[E_Polygon::POLYGON_MAX] = 
	{
		"data\\TEXTURE\\UI\\frame00.png",
		"data\\TEXTURE\\UI\\gauge00.png"
	};

	// �|���S���̐���
	for (int i = 0; i < E_Polygon::POLYGON_MAX; i++)
	{
		m_aPolygon[i] = CUI::Create();

		if (m_aPolygon[i] == nullptr)
			continue;

		m_aPolygon[i]->SetSize(aSize[i].x, aSize[i].y);
		m_aPolygon[i]->SetPosition(POS_INITIAL);
		m_aPolygon[i]->SetVtx();

		int nIdx = Texture::GetIdx(&aPath[i][0]);
		m_aPolygon[i]->SetIdxTexture(nIdx);
	}
}

//=====================================================
// �I������
//=====================================================
void CGauge::Uninit(void)
{
	for (auto it : m_aPolygon)
	{
		if (it != nullptr)
		{
			it->Uninit();
			it = nullptr;
		}
	}

	m_aPolygon.clear();

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CGauge::Update(void)
{
	if (m_aPolygon[E_Polygon::POLYGON_GAUGE] == nullptr)
		return;

	// �ŏ��͂Ƃ肠�����x�^�ɕ���ݒ�
	float fRate = m_fParam / m_fParamMax;
	float fWidth = m_sizeGauge.x * fRate;

	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posGauge = pos;
	posGauge.x += fWidth;
	posGauge.x -= m_sizeGauge.x;

	// �g�����X�t�H�[���̐ݒ�
	m_aPolygon[E_Polygon::POLYGON_GAUGE]->SetSize(fWidth, m_sizeGauge.y);
	m_aPolygon[E_Polygon::POLYGON_GAUGE]->SetPosition(posGauge);
	m_aPolygon[E_Polygon::POLYGON_GAUGE]->SetVtx();

	// �e�N�X�`�����W�̐ݒ�
	m_aPolygon[E_Polygon::POLYGON_GAUGE]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(fRate, 1.0f));
}

//=====================================================
// �`�揈��
//=====================================================
void CGauge::Draw(void)
{

}

//=====================================================
// �p�����[�^�[�̉��Z����	// ���肩��
//=====================================================
void CGauge::AddParam(float fValue)
{
	m_fParam += fValue;

	// �Q�[�W�������悤�ɐݒ�
	if (m_aPolygon[E_Polygon::POLYGON_GAUGE] == nullptr)
		return;

	m_fWidthOld = m_aPolygon[E_Polygon::POLYGON_GAUGE]->GetWidth();
}