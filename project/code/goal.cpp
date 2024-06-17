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
	const D3DXVECTOR3 STARTPOS = D3DXVECTOR3(15000.0f, 00.0f, -15000.0f);		// �n�_�̈ʒu
	const D3DXVECTOR3 ENDPOS = D3DXVECTOR3(17000.0f, 00.0f, -12000.0f);		// �I�_�̈ʒu
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CGoal::CGoal(int nPriority)
{
	m_pPlayer = nullptr;
	m_pObj3D = nullptr;
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
CGoal* CGoal::Create()
{
	CGoal* pGoal = new CGoal;

	// ������
	pGoal->Init();

	return pGoal;
}

//=====================================================
// ������
//=====================================================
HRESULT CGoal::Init()
{
	// ����
	m_pObj3D = CObject3D::Create(STARTPOS);

	// �F�ݒ�
	m_pObj3D->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f));

	// �T�C�Y�ݒ�
	m_pObj3D->SetSize(2000.0f, 100.0f);

	// �x�N�g��
	D3DXVECTOR3 vec = ENDPOS - STARTPOS;

	// �ʒu�ݒ�
	m_pObj3D->SetPosition(D3DXVECTOR3(STARTPOS + vec * 0.5f));

	// �����ݒ�
	m_pObj3D->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.75f, 0.0f));

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
	// �m�F�p�ϐ�
	int n = 0;

	// ��_�̊���
	float fCross = 0.0f;

	// �v���C���[���擾
	CPlayer* pPlayer = CPlayer::GetInstance();

	// �t�F�[�h���擾
	CFade* pFade = CFade::GetInstance();

	// �ʒu�擾
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// �ړ��ʎ擾
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();

	// �O�ς̔���
	if (universal::IsCross(posPlayer,		// �v���C���[�̈ʒu
		STARTPOS,		// �S�[���̎n�_
		ENDPOS,			// �S�[���̏I�_
		&fCross,		// ��_�̊���
		movePlayer))	// �v���C���[�̈ړ���
	{
		if (fCross > 0.0f && fCross < 1.0f)
		{// �n�_�ƏI�_�̊Ԃ�ʂ�����
			n = 1;

			// �J�E���g���Z
			m_nTransitionTime++;

			if (m_nTransitionTime >= Transition)
			{
				// ��ʑJ��
				//pFade->SetFade(CScene::MODE_RESULT);

				// �J�E���g���Z�b�g
				m_nTransitionTime = 0;
			}

			CDebugProc::GetInstance()->Print("\n�S�[������");
		}
	}

#ifdef _DEBUG
	CEffect3D::Create(STARTPOS, 200.0f, 3, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	CEffect3D::Create(ENDPOS, 200.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
#endif

	CDebugProc::GetInstance()->Print("\nn�̒l[%d]", n);
	CDebugProc::GetInstance()->Print("\nfCross�̒l[%f]", fCross);
	CDebugProc::GetInstance()->Print("\nstartPos�̈ʒu[%f, %f, %f]", STARTPOS.x, STARTPOS.y, STARTPOS.z);
	CDebugProc::GetInstance()->Print("\nendPos�̈ʒu[%f, %f, %f]", ENDPOS.x, ENDPOS.y, ENDPOS.z);
}

//=====================================================
// �`��
//=====================================================
void CGoal::Draw()
{
	m_pObj3D->Draw();
}
