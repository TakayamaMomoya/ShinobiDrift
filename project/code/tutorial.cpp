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
#include "texture.h"

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
CTutorial::CTutorial() : CObject(1), m_pState(nullptr)
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
// �����l�̒ǉ�
//=====================================================
void CTutorial::AddLimit(int nIdx, float fValue)
{
	m_mapLimit[nIdx] = fValue;
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

//=====================================================
// �I������
//=====================================================
bool CStateTutorial::IsEndInput(int nNum, CTutorial *pTutorial)
{
	std::map<int, float> mapCounter = pTutorial->GetMapCounter();
	std::map<int, float> mapLimit = pTutorial->GetMapLimit();

	for (int i = 0; i < nNum; i++)
	{
		if (mapLimit[i] > mapCounter[i])
		{
			return false;
		}
	}

	return true;
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

	// �p�X�̈ꗗ
	const char* apPath[MENU_MAX] =
	{
		"data\\TEXTURE\\UI\\tutorial00.png",
		"data\\TEXTURE\\UI\\tutorial01.png"
	};

	// �����l�̈ꗗ
	float aTime[MENU_MAX] =
	{
		TIME_ACCELE,
		TIME_BRAKE
	};

	for (int i = 0; i < MENU_MAX; i++)
	{
		// �eUI�̐ݒ�
		CUI *pUI = Tutorial::CreateUIDefault();

		if (pUI == nullptr)
			continue;

		int nIdx = Texture::GetIdx(apPath[i]);
		pUI->SetIdxTexture(nIdx);
		mapUI[i] = pUI;
		
		D3DXVECTOR3 posUI = pUI->GetPosition();
		posUI.y = POS_DEFAULT_UI.y + SIZE_DEFAULT_UI.y * i * 2;
		pUI->SetPosition(posUI);
		pUI->SetVtx();

		// �����l�̐ݒ�
		pTutorial->AddLimit(i, aTime[i]);
	}

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
	
	if (IsEndInput(MENU_MAX,pTutorial))
	{// �ړ��`���[�g���A�����I��
		pTutorial->ChangeState(new CStateTutorialDrift);
	}
}

//********************************************************************************
// �h���t�g�`���[�g���A��
//********************************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CStateTutorialDrift::CStateTutorialDrift()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CStateTutorialDrift::~CStateTutorialDrift()
{

}

//=====================================================
// ������
//=====================================================
void CStateTutorialDrift::Init(CTutorial *pTutorial)
{
	std::map<int, CUI*> *pMapUI = pTutorial->GetMap();
	std::map<int, CUI*> mapUI = *pMapUI;

	// �p�X�̈ꗗ
	const char* apPath[MENU_MAX] =
	{
		"data\\TEXTURE\\UI\\tutorial02.png",
	};

	// �����l�̈ꗗ
	float aTime[MENU_MAX] =
	{
		TIME_ACCELE,
	};

	for (int i = 0; i < MENU_MAX; i++)
	{
		// �eUI�̐ݒ�
		CUI *pUI = Tutorial::CreateUIDefault();

		if (pUI == nullptr)
			continue;

		int nIdx = Texture::GetIdx(apPath[i]);
		pUI->SetIdxTexture(nIdx);
		mapUI[i] = pUI;

		D3DXVECTOR3 posUI = pUI->GetPosition();
		posUI.y = POS_DEFAULT_UI.y + SIZE_DEFAULT_UI.y * i * 2;
		pUI->SetPosition(posUI);
		pUI->SetVtx();

		// �����l�̐ݒ�
		pTutorial->AddLimit(i, aTime[i]);
	}

	*pMapUI = mapUI;
}

//=====================================================
// �I��
//=====================================================
void CStateTutorialDrift::Uninit(CTutorial *pTutorial)
{
	CStateTutorial::Uninit(pTutorial);
}

//=====================================================
// �X�V
//=====================================================
void CStateTutorialDrift::Update(CTutorial *pTutorial)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;

	std::map<int, float> mapCounter = pTutorial->GetMapCounter();
	float fDeltaTime = CManager::GetDeltaTime();

	// �h���t�g�̔���
	bool bDrift = pPlayer->IsDrift();

	if (bDrift)
	{// �h���t�g�̃J�E���^�[�����Z
		mapCounter[MENU_DRIFT] += fDeltaTime;
	}

	pTutorial->SetMapCounter(mapCounter);

	CDebugProc::GetInstance()->Print("\n�h���t�g�J�E���^�[[%f]", mapCounter[MENU_DRIFT]);

	if (IsEndInput(MENU_MAX, pTutorial))
	{// �h���t�g�`���[�g���A�����I��
		pTutorial->ChangeState(new CStateTutorialParry);
	}
}

//********************************************************************************
// �p���B�`���[�g���A��
//********************************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CStateTutorialParry::CStateTutorialParry()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CStateTutorialParry::~CStateTutorialParry()
{

}

//=====================================================
// ������
//=====================================================
void CStateTutorialParry::Init(CTutorial *pTutorial)
{
	std::map<int, CUI*> *pMapUI = pTutorial->GetMap();
	std::map<int, CUI*> mapUI = *pMapUI;

	// �p�X�̈ꗗ
	const char* apPath[MENU_MAX] =
	{
		"data\\TEXTURE\\UI\\tutorial03.png",
	};

	// �����l�̈ꗗ
	float aTime[MENU_MAX] =
	{
		TIME_ACCELE,
	};

	for (int i = 0; i < MENU_MAX; i++)
	{
		// �eUI�̐ݒ�
		CUI *pUI = Tutorial::CreateUIDefault();

		if (pUI == nullptr)
			continue;

		int nIdx = Texture::GetIdx(apPath[i]);
		pUI->SetIdxTexture(nIdx);
		mapUI[i] = pUI;

		D3DXVECTOR3 posUI = pUI->GetPosition();
		posUI.y = POS_DEFAULT_UI.y + SIZE_DEFAULT_UI.y * i * 2;
		pUI->SetPosition(posUI);
		pUI->SetVtx();

		// �����l�̐ݒ�
		pTutorial->AddLimit(i, aTime[i]);
	}

	*pMapUI = mapUI;
}

//=====================================================
// �I��
//=====================================================
void CStateTutorialParry::Uninit(CTutorial *pTutorial)
{
	CStateTutorial::Uninit(pTutorial);
}

//=====================================================
// �X�V
//=====================================================
void CStateTutorialParry::Update(CTutorial *pTutorial)
{
	CInputManager *pInputManager = CInputManager::GetInstance();
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pInputManager == nullptr || pPlayer == nullptr)
		return;

	std::map<int, float> mapCounter = pTutorial->GetMapCounter();
	float fDeltaTime = CManager::GetDeltaTime();

	// �p���B�̔���
	int nMotion = pPlayer->GetMotion();

	if (pInputManager->GetTrigger(CInputManager::BUTTON_KATANA) && (nMotion != CPlayer::MOTION_NINJA::MOTION_NINJA_SLASHDOWN || nMotion != CPlayer::MOTION_NINJA::MOTION_NINJA_SLASHUP))
	{// �p���B�̃J�E���^�[�����Z
		mapCounter[MENU_PARRY] += 1.0f;
	}

	pTutorial->SetMapCounter(mapCounter);

	CDebugProc::GetInstance()->Print("\n�p���B�J�E���^�[[%f]", mapCounter[MENU_PARRY]);

	if (IsEndInput(MENU_MAX, pTutorial))
	{// �p���B�`���[�g���A�����I��
		pTutorial->ChangeState(new CStateTutorialFree);
	}
}


//********************************************************************************
// �t���[�`���[�g���A��
//********************************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CStateTutorialFree::CStateTutorialFree()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CStateTutorialFree::~CStateTutorialFree()
{

}

//=====================================================
// ������
//=====================================================
void CStateTutorialFree::Init(CTutorial *pTutorial)
{
	std::map<int, CUI*> *pMapUI = pTutorial->GetMap();
	std::map<int, CUI*> mapUI = *pMapUI;

	// �p�X�̈ꗗ
	const char* apPath[MENU_MAX] =
	{
		"data\\TEXTURE\\UI\\tutorial04.png",
	};

	// �����l�̈ꗗ
	float aTime[MENU_MAX] =
	{
		TIME_ACCELE,
	};

	for (int i = 0; i < MENU_MAX; i++)
	{
		// �eUI�̐ݒ�
		CUI *pUI = Tutorial::CreateUIDefault();

		if (pUI == nullptr)
			continue;

		int nIdx = Texture::GetIdx(apPath[i]);
		pUI->SetIdxTexture(nIdx);
		mapUI[i] = pUI;

		D3DXVECTOR3 posUI = pUI->GetPosition();
		posUI.y = POS_DEFAULT_UI.y + SIZE_DEFAULT_UI.y * i * 2;
		pUI->SetPosition(posUI);
		pUI->SetVtx();

		// �����l�̐ݒ�
		pTutorial->AddLimit(i, aTime[i]);
	}

	*pMapUI = mapUI;
}

//=====================================================
// �I��
//=====================================================
void CStateTutorialFree::Uninit(CTutorial *pTutorial)
{
	CStateTutorial::Uninit(pTutorial);
}

//=====================================================
// �X�V
//=====================================================
void CStateTutorialFree::Update(CTutorial *pTutorial)
{
	CInputManager *pInputManager = CInputManager::GetInstance();
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pInputManager == nullptr || pPlayer == nullptr)
		return;
	
	if (pInputManager->GetTrigger(CInputManager::BUTTON_ENTER))
	{// �`���[�g���A�����I��
		pTutorial->EnableEnd(true);
	}
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