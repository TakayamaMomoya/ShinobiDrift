//*****************************************************
//
// �S�[������[goal.cpp]
// Author:�X��x��
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "goal.h"
#include "debugproc.h"
#include "effect3D.h"
#include "fade.h"
#include "game.h"
#include "timer.h"
#include "result.h"
#include "texture.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float MOVESPEED = 4.0f;	// �ړ����x
const float WIDTH_GOAL = 100.0f;	// �S�[���̕�
const string PATH_TEX = "data\\TEXTURE\\UI\\goal.jpg";	// �S�[���̃e�N�X�`��
}

//*****************************************************
// �ÓI�����o�ϐ�
//*****************************************************
CGoal *CGoal::m_pGoal = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CGoal::CGoal(int nPriority)
{
	m_nTransitionTime = 0;		// �J�ڃJ�E���^�[
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_posStart = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �S�[���̎n�_
	m_posEnd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �S�[���̏I�_
	m_fRot = 0.0f;		// ����
	m_pObj3D = nullptr;		// �I�u�W�F�N�g3D�̃|�C���^
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CGoal::~CGoal()
{

}

//=====================================================
// ����
//=====================================================
CGoal* CGoal::Create(D3DXVECTOR3 pos,float fRot, float fLength)
{
	if (m_pGoal != nullptr)
		return m_pGoal;

	m_pGoal = new CGoal;

	if (m_pGoal != nullptr)
	{
		m_pGoal->m_pos = pos;
		m_pGoal->m_fRot = fRot;
		m_pGoal->m_fLength = fLength;

		// ������
		m_pGoal->Init();
	}

	return m_pGoal;
}

//=====================================================
// ������
//=====================================================
HRESULT CGoal::Init()
{
	// �S�[���e�[�v�̐���
	m_pObj3D = CPolygon3D::Create(m_pos);

	// �S�[���̐ݒ�
	SetGoal();

	return S_OK;
}

//=====================================================
// �S�[���̐ݒ�
//=====================================================
void CGoal::SetGoal(void)
{
	// �n�_�E�I�_�̌v�Z
	D3DXVECTOR3 vec = { sinf(m_fRot)* m_fLength ,0.0f,cosf(m_fRot) * m_fLength };

	m_posStart = m_pos + vec;
	m_posEnd = m_pos - vec;

	if (m_pObj3D != nullptr)
	{
		// �T�C�Y�ݒ�
		m_pObj3D->SetSize(m_fLength, WIDTH_GOAL);

		m_pObj3D->SetRotation(D3DXVECTOR3(0.0f, m_fRot + D3DX_PI * 0.5f, 0.0f));
		m_pObj3D->SetPosition(m_pos);

		// �e�N�X�`���ݒ�
		int nIdx = Texture::GetIdx(&PATH_TEX[0]);
		m_pObj3D->SetIdxTexture(nIdx);
	}
}

//=====================================================
// �I��
//=====================================================
void CGoal::Uninit()
{
	m_pGoal = nullptr;

	if (m_pObj3D != nullptr)
	{
		m_pObj3D->Uninit();
		m_pObj3D = nullptr;
	}

	// ���g�̍폜
	Release();
}

//=====================================================
// �X�V
//=====================================================
void CGoal::Update()
{
	// �v���C���[���擾
	CPlayer* pPlayer = CPlayer::GetInstance();

	// �t�F�[�h���擾
	CFade* pFade = CFade::GetInstance();

	// �ʒu�擾
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();

	// ��_�̊���
	float fCross = 0.0f;

	bool bHit = universal::IsCross(posPlayer,		// �v���C���[�̈ʒu
		m_posStart,		// �S�[���̎n�_
		m_posEnd,			// �S�[���̏I�_
		&fCross,		// ��_�̊���
		posPlayer + movePlayer);	// �v���C���[�̈ړ���

	bool bHitNext = universal::IsCross(posPlayer + movePlayer,		// �v���C���[�̎���̈ʒu
		m_posStart,		// �S�[���̎n�_
		m_posEnd,			// �S�[���̏I�_
		nullptr,		// ��_�̊���
		posPlayer + movePlayer);	// �v���C���[�̈ړ���

	// �O�ς̔���
	if (!bHit && bHitNext)
	{
		if (fCross >= 0.0f && fCross <= 1.0f)
		{// �n�_�ƏI�_�̊Ԃ�ʂ�����
			pPlayer->SetEnableResultFlag(true);
			pPlayer->SEtEnableBike(true);

			// ���U���g�̐���
			CResult::Create();
		}
	}
}

//=====================================================
// �`��
//=====================================================
void CGoal::Draw()
{

}
