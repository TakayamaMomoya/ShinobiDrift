//*****************************************************
//
// ���U���g����[result.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "result.h"
#include "player.h"
#include "camera.h"
#include "manager.h"
#include "cameraState.h"
#include "inputManager.h"
#include "game.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{

}

//=====================================================
// �R���X�g���N�^
//=====================================================
CResult::CResult() : CObject(1), m_pState(nullptr)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CResult::~CResult()
{

}

//=====================================================
// ��������
//=====================================================
CResult *CResult::Create(void)
{
	CResult *pResult = nullptr;

	pResult = new CResult;

	if (pResult != nullptr)
	{
		pResult->Init();
	}

	return pResult;
}

//=====================================================
// ����������
//=====================================================
HRESULT CResult::Init(void)
{
	// �v���C���[�̐ݒ�
	SetPlayer();

	// �J�����ʒu�̐ݒ�
	SetCamera();

	// �X�e�C�g�̕ύX
	ChangeState(new CStateResultDispTime);

	return S_OK;
}

//=====================================================
// �v���C���[�ݒ�
//=====================================================
void CResult::SetPlayer(void)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;
	
	// �v���C���[�𑀍�ł��Ȃ��悤�ɂ���
	pPlayer->SetEnableInput(false);
}

//=====================================================
// �J�����ݒ�
//=====================================================
void CResult::SetCamera(void)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
		return;
	
	pCamera->ChangeState(new CCameraStateResult);
}

//=====================================================
// �I������
//=====================================================
void CResult::Uninit(void)
{
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CResult::Update(void)
{
	if (m_pState != nullptr)
	{
		m_pState->Update(this);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CResult::Draw(void)
{

}

//=====================================================
// �X�e�C�g�̕ύX
//=====================================================
void CResult::ChangeState(CStateResult *pState)
{
	if (m_pState != nullptr)
	{
		m_pState->Uninit(this);
		delete m_pState;
		m_pState = nullptr;
	}

	m_pState = pState;

	if (m_pState != nullptr)
	{
		m_pState->Init(this);
	}
}

//=====================================================
// �t�F�[�h���n�߂鏈��
//=====================================================
void CResult::StartFade(void)
{
	CGame *pGame = CGame::GetInstance();

	if (pGame == nullptr)
		return;

	pGame->SetState(CGame::STATE::STATE_END);
}

//=====================================================
// �X�e�C�g�̏I��
//=====================================================
void CStateResult::Uninit(CResult *pResult)
{

}

//********************************************************************************
// �^�C���\��
//********************************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CStateResultDispTime::CStateResultDispTime()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CStateResultDispTime::~CStateResultDispTime()
{

}

//=====================================================
// ������
//=====================================================
void CStateResultDispTime::Init(CResult *pResult)
{

}

//=====================================================
// �I��
//=====================================================
void CStateResultDispTime::Uninit(CResult *pResult)
{
	CStateResult::Uninit(pResult);
}

//=====================================================
// �X�V
//=====================================================
void CStateResultDispTime::Update(CResult *pResult)
{
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager == nullptr)
		return;

	// �t�F�[�h���n�߂�
	if (pInputManager->GetTrigger(CInputManager::BUTTON_ENTER))
		pResult->StartFade();
}