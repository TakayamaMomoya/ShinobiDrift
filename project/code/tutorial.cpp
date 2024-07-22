//*****************************************************
//
// �`���[�g���A������[tutorial.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "tutorial.h"
#include "meshRoad.h"
#include "UI.h"
#include "timer.h"
#include "inputManager.h"
#include "player.h"
#include "debugproc.h"
#include "manager.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const char* PATH_ROAD = "data\\MAP\\road01.bin";	// �`���[�g���A�����b�V�����[�h�̃p�X
const D3DXVECTOR3 POS_DEFAULT_UI = { SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.5f, 0.0f };	// UI�̃f�t�H���g�ʒu
const D3DXVECTOR2 SIZE_DEFAULT_UI = { SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f};	// UI�̃f�t�H���g�T�C�Y
const float LINE_INPUT = 0.3f;	// ���͂Ɣ��肷��X�s�[�h
const float TIME_ACCELE = 5.0f;	// �A�N�Z���ɕK�v�Ȏ���
const float TIME_BRAKE = 3.0f;	// �u���[�L�ɕK�v�Ȏ���
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CTutorial::CTutorial() : m_pState(nullptr)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTutorial::~CTutorial()
{

}

//=====================================================
// ��������
//=====================================================
CTutorial *CTutorial::Create(void)
{
	CTutorial *pTutorial = nullptr;

	pTutorial = new CTutorial;

	if (pTutorial != nullptr)
	{
		pTutorial->Init();
	}

	return pTutorial;
}

//=====================================================
// ����������
//=====================================================
HRESULT CTutorial::Init(void)
{
	CMeshRoad::Create(PATH_ROAD);

	// �����X�e�C�g�ɐݒ�
	ChangeState(new CStateTutorialMove);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTutorial::Uninit(void)
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
void CTutorial::Update(void)
{
	if (m_pState != nullptr)
	{
		m_pState->Update(this);
	}

	if (IsEnd())
	{// �`���[�g���A���̏I��
		StartGame();

		Uninit();

		return;
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CTutorial::Draw(void)
{

}

//=====================================================
// �Q�[���̊J�n
//=====================================================
void CTutorial::StartGame(void)
{
	// �^�C�}�[�̐���
	CTimer::Create();
}

//=====================================================
// �X�e�C�g�̕ύX
//=====================================================
void CTutorial::ChangeState(CStateTutorial *pState)
{
	if (m_pState != nullptr)
	{
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
// �X�e�C�g�̏I��
//=====================================================
void CStateTutorial::Uninit(CTutorial *pTutorial)
{
	// UI�̃}�b�v�R���e�i�N���A
	std::map<int, CUI*> *pMapUI = pTutorial->GetMap();

	for (auto it : *pMapUI)
	{
		it.second->Uninit();
	}

	pMapUI->clear();

	// �J�E���^�[�̃}�b�v�R���e�i�N���A
	std::map<int, float> mapFloat;
	mapFloat.clear();
	pTutorial->SetMapCounter(mapFloat);
}

//********************************************************************************
// �ړ��`���[�g���A��
//********************************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CStateTutorialMove::CStateTutorialMove()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CStateTutorialMove::~CStateTutorialMove()
{

}

//=====================================================
// ������
//=====================================================
void CStateTutorialMove::Init(CTutorial *pTutorial)
{
	std::map<int, CUI*> *pMapUI = pTutorial->GetMap();
	std::map<int, CUI*> mapUI = *pMapUI;

	// UI�̒ǉ�
	// �A�N�Z��
	CUI *pAccel = Tutorial::CreateUIDefault();
	mapUI[(int)MENU_ACCELE] = pAccel;

	// �u���[�L
	CUI *pBrake = Tutorial::CreateUIDefault();
	mapUI[(int)MENU_BRAKE] = pBrake;

	*pMapUI = mapUI;
}

//=====================================================
// �I��
//=====================================================
void CStateTutorialMove::Uninit(CTutorial *pTutorial)
{
	CStateTutorial::Uninit(pTutorial);
}

//=====================================================
// �X�V
//=====================================================
void CStateTutorialMove::Update(CTutorial *pTutorial)
{
	CInputManager *pInputManager = CInputManager::GetInstance();
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pInputManager == nullptr || pPlayer == nullptr)
		return;

	std::map<int, float> mapCounter = pTutorial->GetMapCounter();
	float fDeltaTime = CManager::GetDeltaTime();

	// �A�N�Z���̔���
	float fAccele = pInputManager->GetAccele();
	
	if (fAccele > LINE_INPUT)
	{// �A�N�Z���̃J�E���^�[�����Z
		mapCounter[MENU_ACCELE] += fDeltaTime;
	}

	// �u���[�L�̔���
	float fBrake = pInputManager->GetBrake();

	if (fBrake > LINE_INPUT)
	{// �u���[�L�̃J�E���^�[�����Z
		mapCounter[MENU_BRAKE] += fDeltaTime;
	}

	pTutorial->SetMapCounter(mapCounter);

	CDebugProc::GetInstance()->Print("\n�A�N�Z���J�E���^�[[%f]�u���[�L�J�E���^�[[%f]", mapCounter[MENU_ACCELE], mapCounter[MENU_BRAKE]);
	
	if (IsEndInput(pTutorial))
	{// �ړ��`���[�g���A�����I��
		pTutorial->EnableEnd(true);
	}
}

//=====================================================
// �I������
//=====================================================
bool CStateTutorialMove::IsEndInput(CTutorial *pTutorial)
{
	float aTime[MENU_MAX] = 
	{
		TIME_ACCELE,
		TIME_BRAKE
	};

	std::map<int, float> mapCounter = pTutorial->GetMapCounter();

	for (int i = 0; i < MENU_MAX; i++)
	{
		if (aTime[i] > mapCounter[i])
		{
			return false;
		}
	}

	return true;
}

namespace Tutorial
{
CUI *CreateUIDefault(void)
{
	CUI *pUI = CUI::Create();
	pUI->SetPosition(POS_DEFAULT_UI);
	pUI->SetSize(SIZE_DEFAULT_UI.x, SIZE_DEFAULT_UI.y);
	pUI->SetVtx();

	return pUI;
}
}