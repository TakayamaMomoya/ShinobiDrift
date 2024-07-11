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
        m_pState->Uninit();
        m_pState = nullptr;
    }

    Release();
}

//=====================================================
// �X�V����
//=====================================================
void CManipulater::Update(void)
{
    if (m_pState != nullptr)
    {
        m_pState->Update();
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
        m_pState->Uninit();
        m_pState = nullptr;
    }

    m_pState = pState;

    if (m_pState != nullptr)
    {
        m_pState->Init();
    }
}

//********************************************************************************
// �ړ��̃X�e�C�g
//********************************************************************************
//=====================================================
// ������
//=====================================================
void CStateManipulaterTranslate::Init(void)
{

}

//=====================================================
// �I��
//=====================================================
void CStateManipulaterTranslate::Uninit(void)
{

}

//=====================================================
// �X�V
//=====================================================
void CStateManipulaterTranslate::Update(void)
{

}
