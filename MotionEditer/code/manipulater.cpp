//*****************************************************
//
// �}�j�s�����[�^�[[manipulater.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "manipulater.h"
#include "motion.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{

}

//=====================================================
// �R���X�g���N�^
//=====================================================
CManipulater::CManipulater(int nPriority)
{
    m_nIdxPart = 0;
    m_pState = nullptr;
    m_pMotion = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CManipulater::~CManipulater()
{

}

//=====================================================
// ��������
//=====================================================
CManipulater* CManipulater::Create(int nIdxPart, CMotion *pMotion)
{
    CManipulater *pManipulater = nullptr;

	if (pManipulater == nullptr)
	{
        pManipulater = new CManipulater;

		if (pManipulater != nullptr)
		{
			// ������
            pManipulater->Init();

            pManipulater->m_nIdxPart = nIdxPart;
            pManipulater->m_pMotion = pMotion;
		}
	}

	return pManipulater;
}

//=====================================================
// ����������
//=====================================================
HRESULT CManipulater::Init(void)
{
    ChangeState(new CStateManipulaterTranslate);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CManipulater::Uninit(void)
{
    if (m_pState != nullptr)
    {
        m_pState->Uninit(this);
        m_pState = nullptr;
    }

    Release();
}

//=====================================================
// �X�V����
//=====================================================
void CManipulater::Update(void)
{
    // �p�[�c�̈ʒu�̎擾
    D3DXVECTOR3 posPart = m_pMotion->GetMtxPos(m_nIdxPart);
    D3DXVECTOR3 rotPart = universal::ExtractEulerAngles(*m_pMotion->GetParts(m_nIdxPart)->pParts->GetMatrix());
    int nIdxPartParent = m_pMotion->GetParts(m_nIdxPart)->nIdxParent;

    if (nIdxPartParent != -1)
    {// �e������ꍇ�͐e�̃}�g���b�N�X����������擾
        rotPart = universal::ExtractEulerAngles(*m_pMotion->GetParts(nIdxPartParent)->pParts->GetMatrix());
    }
    else
    {// �e�����Ȃ���������Z�b�g
        rotPart = { 0.0f,0.0f,0.0f };
    }

    SetPosition(posPart);
    SetRotation(rotPart);

    if (m_pState != nullptr)
    {
        m_pState->Update(this);
    }
}

//=====================================================
// �`�揈��
//=====================================================
void CManipulater::Draw(void)
{

}

//=====================================================
// �X�e�C�g�̕ύX
//=====================================================
void CManipulater::ChangeState(CStateManipulater *pState)
{
    if (m_pState != nullptr)
    {
        m_pState->Uninit(this);
        m_pState = nullptr;
    }

    m_pState = pState;

    if (m_pState != nullptr)
    {
        m_pState->Init(this);
    }
}

//********************************************************************************
// �ړ��̃X�e�C�g
//********************************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CStateManipulaterTranslate::CStateManipulaterTranslate()
{
    m_pManipulater = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CStateManipulaterTranslate::~CStateManipulaterTranslate()
{

}

//=====================================================
// ������
//=====================================================
void CStateManipulaterTranslate::Init(CManipulater *pManipulater)
{
    m_pManipulater = CObjectX::Create();

    int nIdx = CModel::Load("data\\MODEL\\manipulator.x");
    m_pManipulater->BindModel(nIdx);
    m_pManipulater->EnableZtest(true);
}

//=====================================================
// �I��
//=====================================================
void CStateManipulaterTranslate::Uninit(CManipulater *pManipulater)
{

}

//=====================================================
// �X�V
//=====================================================
void CStateManipulaterTranslate::Update(CManipulater *pManipulater)
{
    // ����
    Input(pManipulater);

    // ���f���̒Ǐ]
    FollowModel(pManipulater);
}

//=====================================================
// ���͏���
//=====================================================
void CStateManipulaterTranslate::Input(CManipulater *pManipulater)
{

}

//=====================================================
// ���f���̒Ǐ]
//=====================================================
void CStateManipulaterTranslate::FollowModel(CManipulater *pManipulater)
{
    // ���f���̒Ǐ]
    D3DXVECTOR3 posManipulater = pManipulater->GetPosition();
    D3DXVECTOR3 rotManipulater = pManipulater->GetRotation();

    m_pManipulater->SetPosition(posManipulater);
    m_pManipulater->SetRot(rotManipulater);
}
