//*****************************************************
//
// �S�[������[goal.cpp]
// Author:�X��x��
//
//*****************************************************

#include "goal.h"
#include "universal.h"
#include "debugproc.h"
#include "effect3D.h"
#include "fade.h"
#include "object3D.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const int Transition = 120;		// ��ʑJ�ڂ���܂ł̎���
	const float MOVESPEED = 4.0f;	// �ړ����x
	const float WIDTH_GOAL = 100.0f;	// �S�[���̕�
}

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
	m_pPlayer = nullptr;	// �v���C���[�̃|�C���^
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
	CGoal* pGoal = new CGoal;

	if (pGoal != nullptr)
	{
		pGoal->m_pos = pos;
		pGoal->m_fRot = fRot;
		pGoal->m_fLength = fLength;

		// ������
		pGoal->Init();
	}

	return pGoal;
}

//=====================================================
// ������
//=====================================================
HRESULT CGoal::Init()
{
	// �n�_�E�I�_�̌v�Z
	m_posStart.x = sinf(m_fRot) * m_fLength;
	m_posStart.z = cosf(m_fRot) * m_fLength;

	m_posEnd = -m_posStart;

	m_posStart += m_pos;
	m_posEnd += m_pos;

	// �S�[���e�[�v�̐���
	m_pObj3D = CObject3D::Create(m_pos);

	if (m_pObj3D != nullptr)
	{
		// �F�ݒ�
		m_pObj3D->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f));

		// �T�C�Y�ݒ�
		m_pObj3D->SetSize(WIDTH_GOAL, m_fLength);

		m_pObj3D->SetRotation(D3DXVECTOR3(0.0f, m_fRot, 0.0f));
	}

	return S_OK;
}

//=====================================================
// �I��
//=====================================================
void CGoal::Uninit()
{
	if (m_pObj3D != nullptr)
	{
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

	// �O�ς̔���
	if (universal::IsCross(posPlayer,		// �v���C���[�̈ʒu
		m_posStart,		// �S�[���̎n�_
		m_posEnd,			// �S�[���̏I�_
		&fCross,		// ��_�̊���
		movePlayer))	// �v���C���[�̈ړ���
	{
		if (fCross > 0.0f && fCross < 1.0f)
		{// �n�_�ƏI�_�̊Ԃ�ʂ�����
			// �J�E���g���Z
			m_nTransitionTime++;

			if (m_nTransitionTime >= Transition)
			{
				// ��ʑJ��
				pFade->SetFade(CScene::MODE_RESULT);

				// �J�E���g���Z�b�g
				m_nTransitionTime = 0;
			}

			CDebugProc::GetInstance()->Print("\n�S�[������");
		}
	}

#ifdef _DEBUG
	CEffect3D::Create(m_posStart, 200.0f, 3, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	CEffect3D::Create(m_posEnd, 200.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
#endif

	CDebugProc::GetInstance()->Print("\nfCross�̒l[%f]", fCross);
	CDebugProc::GetInstance()->Print("\nstartPos�̈ʒu[%f, %f, %f]", m_posStart.x, m_posStart.y, m_posStart.z);
	CDebugProc::GetInstance()->Print("\nendPos�̈ʒu[%f, %f, %f]", m_posEnd.x, m_posEnd.y, m_posEnd.z);
}

//=====================================================
// �`��
//=====================================================
void CGoal::Draw()
{

}