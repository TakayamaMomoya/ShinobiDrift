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
#include "effect3D.h"
#include "camera.h"
#include "fade.h"
#include "blurEvent.h"
#include "MyEffekseer.h"
#include "gauge.h"
#include "frame.h"
#include "game.h"
#include "UIManager.h"
#include "cameraState.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const char* PATH_ROAD = "data\\MAP\\road01.bin";	// �`���[�g���A�����b�V�����[�h�̃p�X
const D3DXVECTOR3 POS_DEFAULT_UI = { 0.8f, 0.1f, 0.0f };	// UI�̃f�t�H���g�ʒu
const D3DXVECTOR2 SIZE_DEFAULT_UI = { 0.05f, 0.05f};	// UI�̃f�t�H���g�T�C�Y
const float LINE_INPUT = 0.3f;	// ���͂Ɣ��肷��X�s�[�h
const float TIME_ACCELE = 5.0f;	// �A�N�Z���ɕK�v�Ȏ���
const float TIME_BRAKE = 3.0f;	// �u���[�L�ɕK�v�Ȏ���
const D3DXVECTOR2 SIZE_GATE = { 3000.0f,3000.0f };	// �Q�[�g�̃T�C�Y
const float DIST_GATE = 3000.0f;	// �Q�[�g�̋���
const D3DXVECTOR3 ROT_GATE = { D3DX_PI * 0.5f, D3DX_PI * 0.5f, 0.0f };	// �Q�[�g�̌���
const float SPEED_RATE_PLAYER = 0.8f;	// �v���C���[���Q�[�g�ɓ���Ƃ��̃X�s�[�h�̊���
const float SPEED_EXPAND_GATE = 0.2f;	// �Q�[�g�̊g�����x
const float SIZE_GATE_EFFECT = 1000.0f;	// �Q�[�g�G�t�F�N�g�̖ڕW�T�C�Y
const float HEIGTH_GATE = 300.0f;	// �Q�[�g�̍���
const D3DXVECTOR3 POS_PLAYER_INITIAL = { -11409.0f,0.0f,26395.0f };	// �`���[�g���A���̃v���C���[�����ʒu
const D3DXVECTOR3 ROT_PLAYER_INITIAL = { 0.0f,1.77f,0.0f };	// �`���[�g���A���̃v���C���[��������
const string PATH_TEXTURE_GATE = "data\\TEXTURE\\EFFECT\\gate00.png";	// �Q�[�g�̃e�N�X�`���p�X
const float SPEED_ROTATE_GATE = 0.05f;	// �Q�[�g�̉�鑬�x
const D3DXVECTOR3 POS_PLAYER_END = { -11409.0f, -14.0f,26395.0f };	// �v���C���[�̃`���[�g���A���I�����̈ʒu
const D3DXVECTOR3 ROT_PLAYER_END = { 0.0f, 1.77f,0.0f };	// �v���C���[�̃`���[�g���A���I�����̈ʒu
const D3DXCOLOR COL_GAUGE_LIMIT = { 0.0f,1.0f,1.0f,1.0f };	// �Q�[�W�����������̐F
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

	// �v���C���[���`���[�g���A���}�b�v�Ƀe���|�[�g
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer != nullptr)
	{
		pPlayer->SetPosition(POS_PLAYER_INITIAL);
		pPlayer->SetRotation(ROT_PLAYER_INITIAL);
		pPlayer->MultiplyMtx(false);

		CCamera *pCamera = CManager::GetCamera();

		if (pCamera != nullptr)
		{
			pCamera->SkipToDest();
		}
	}

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
	// �Q�[���^�C�}�[�̐���
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		pGame->CreateGameTimer();
	}

	// �����N�^�C�}�[�̐���
	CUIManager *pUIManager = CUIManager::GetInstance();

	if (pUIManager != nullptr)
		pUIManager->CreateRankTImer();

	// �v���C���[�̃g�����X�t�H�[����ݒ�
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;

	pPlayer->SetPosition(Player::DEFAULT_POS);
	pPlayer->SetRotation(Player::DEFAULT_ROT);

	pPlayer->MultiplyMtx(false);

	// �J�����̈ʒu��ݒ�
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
		return;

	pCamera->ChangeState(new CFollowPlayer);
	pCamera->SkipToDest();	// �ڕW�ʒu�܂ŃJ�������΂�
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

	// �Q�[�W�̔j��
	for (auto it : m_aGauge)
	{
		it->Uninit();
	}

	m_aGauge.clear();
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

//=====================================================
// UI�̐���
//=====================================================
void CStateTutorial::CreateUI(vector<string> aPathTexture, vector<float> aLimit, int nNumMenu, CTutorial *pTutorial)
{
	if (nNumMenu <= 0)
		assert(("�`���[�g���A����UI�����ŕs���Ȑ��𐶐����悤�Ƃ��Ă��܂�", false));

	std::map<int, CUI*> *pMapUI = pTutorial->GetMap();
	std::map<int, CUI*> mapUI = *pMapUI;
	vector<CGauge*> aGauge = GetArrayGauge();
	aGauge.resize(nNumMenu);

	for (int i = 0; i < nNumMenu; i++)
	{
		// �eUI�̐ݒ�
		CUI *pUI = Tutorial::CreateUIDefault();

		if (pUI == nullptr)
			continue;

		int nIdx = Texture::GetIdx(&aPathTexture[i][0]);
		pUI->SetIdxTexture(nIdx);
		mapUI[i] = pUI;

		D3DXVECTOR3 posUI = pUI->GetPosition();
		posUI.y = POS_DEFAULT_UI.y + SIZE_DEFAULT_UI.y * i * 4;
		pUI->SetPosition(posUI);
		pUI->SetVtx();

		// �Q�[�W�̐���
		aGauge[i] = CGauge::Create(aLimit[i]);
		D3DXVECTOR3 posGauge = { posUI.x, posUI.y + SIZE_DEFAULT_UI.y * 2,0.0f }; // �ʒu�̐ݒ�
		aGauge[i]->SetPosition(posGauge);

		// �����l�̐ݒ�
		pTutorial->AddLimit(i, aLimit[i]);
	}

	// �Q�[�W�z��̐ݒ�
	SetArrayGauge(aGauge);

	*pMapUI = mapUI;
}

//=====================================================
// �Q�[�W�̃p�����[�^�[�ݒ�
//=====================================================
void CStateTutorial::SetParamGauge(int nNumMenu, CTutorial *pTutorial)
{
	std::map<int, float> mapCounter = pTutorial->GetMapCounter();
	std::map<int, float> mapLimit = pTutorial->GetMapLimit();
	vector<CGauge*> aGauge = GetArrayGauge();

	if (aGauge.empty())
		return;

	for (int i = 0; i < nNumMenu;i++)
	{
		aGauge[i]->SetParam(mapCounter[i]);

		float fParam = aGauge[i]->GetParam();

		if (fParam >= mapLimit[i])
		{// �p�����[�^�[�����܂�����F��ς���
			CUI *pUI = aGauge[i]->GetGauge();
			pUI->SetCol(COL_GAUGE_LIMIT);
		}
	}

	SetArrayGauge(aGauge);
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
	// �p�X�̈ꗗ
	vector<string> aPath(MENU_MAX);
	aPath =
	{
		"data\\TEXTURE\\UI\\tutorial00.png",
		"data\\TEXTURE\\UI\\tutorial01.png"
	};

	// �����l�̈ꗗ
	vector<float> aLimit(MENU_MAX);
	aLimit =
	{
		TIME_ACCELE,
		TIME_BRAKE
	};

	CreateUI(aPath, aLimit, MENU_MAX, pTutorial);
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
	std::map<int, float> mapLimit = pTutorial->GetMapLimit();

	float fDeltaTime = CManager::GetDeltaTime();

	// �A�N�Z���̔���
	float fAccele = pInputManager->GetAccele();
	
	if (fAccele > LINE_INPUT)
	{// �A�N�Z���̃J�E���^�[�����Z
		mapCounter[MENU_ACCELE] += fDeltaTime;

		universal::LimitValuefloat(&mapCounter[MENU_ACCELE], mapLimit[MENU_ACCELE], 0.0f);
	}

	// �u���[�L�̔���
	float fBrake = pInputManager->GetBrake();

	if (fBrake > LINE_INPUT)
	{// �u���[�L�̃J�E���^�[�����Z
		mapCounter[MENU_BRAKE] += fDeltaTime;

		universal::LimitValuefloat(&mapCounter[MENU_BRAKE], mapLimit[MENU_BRAKE], 0.0f);
	}

	// �Q�[�W�p�����[�^�[�̐ݒ�
	SetParamGauge(MENU_MAX, pTutorial);

	pTutorial->SetMapCounter(mapCounter);

	CDebugProc::GetInstance()->Print("\n�A�N�Z���J�E���^�[[%f]�u���[�L�J�E���^�[[%f]", mapCounter[MENU_ACCELE], mapCounter[MENU_BRAKE]);
	
	if (IsEndInput(MENU_MAX,pTutorial))
	{// �ړ��`���[�g���A�����I��
		pTutorial->ChangeState(new CStateTutorialEnd);
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
	// �p�X�̈ꗗ
	vector<string> aPath(MENU_MAX);
	aPath =
	{
		"data\\TEXTURE\\UI\\tutorial02.png",
	};

	// �����l�̈ꗗ
	vector<float> aLimit(MENU_MAX);
	aLimit =
	{
		1.0f,
	};

	CreateUI(aPath, aLimit, MENU_MAX, pTutorial);
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

	// �Q�[�W�p�����[�^�[�̐ݒ�
	SetParamGauge(MENU_MAX, pTutorial);

	pTutorial->SetMapCounter(mapCounter);

	if (IsEndInput(MENU_MAX, pTutorial))
	{// �h���t�g�`���[�g���A�����I��
		pTutorial->ChangeState(new CStateTutorialEnd);
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
	// �p�X�̈ꗗ
	vector<string> aPath(MENU_MAX);
	aPath =
	{
		"data\\TEXTURE\\UI\\tutorial03.png",
	};

	// �����l�̈ꗗ
	vector<float> aLimit(MENU_MAX);
	aLimit =
	{
		TIME_ACCELE,
	};

	CreateUI(aPath, aLimit, MENU_MAX, pTutorial);
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

	// �Q�[�W�p�����[�^�[�̐ݒ�
	SetParamGauge(MENU_MAX, pTutorial);

	pTutorial->SetMapCounter(mapCounter);

	CDebugProc::GetInstance()->Print("\n�p���B�J�E���^�[[%f]", mapCounter[MENU_PARRY]);

	if (IsEndInput(MENU_MAX, pTutorial))
	{// �p���B�`���[�g���A�����I��
		pTutorial->ChangeState(new CStateTutorialEnd);
	}
}

//********************************************************************************
// �t���[�`���[�g���A��
//********************************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CStateTutorialEnd::CStateTutorialEnd() : m_pGate(nullptr), m_bFade(false)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CStateTutorialEnd::~CStateTutorialEnd()
{

}

//=====================================================
// ������
//=====================================================
void CStateTutorialEnd::Init(CTutorial *pTutorial)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;

	// �v���C���[�̃g�����X�t�H�[���̐ݒ�
	pPlayer->SetPosition(POS_PLAYER_END);
	pPlayer->SetRotation(ROT_PLAYER_END);
	pPlayer->MultiplyMtx(false);

	// �J�����̃X�e�C�g��ݒ�
	Camera::ChangeState(new CCameraStateTutorialEnd);

	// �Q�[�g�����̂��߂ɏ���
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
	D3DXVECTOR3 posGate = posPlayer + pPlayer->GetForward() * DIST_GATE;
	posGate.y += HEIGTH_GATE;

	float fAngle = atan2f(pPlayer->GetForward().x, pPlayer->GetForward().z);	// �v���C���[�̕�����������

	// �Q�[�g�̐���
	m_pGate = CPolygon3D::Create(D3DXVECTOR3());
	
	if (m_pGate != nullptr)
	{
		m_pGate->SetRotation(D3DXVECTOR3(-D3DX_PI * 0.5f, fAngle, 0.0f));
		posGate.y += HEIGTH_GATE;
		m_pGate->SetPosition(posGate);
		m_pGate->SetSize(0.0f, 0.0f);
		m_pGate->EnableZtest(true);

		int nIdxTexture = Texture::GetIdx(&PATH_TEXTURE_GATE[0]);
		m_pGate->SetIdxTexture(nIdxTexture);
	}

	// �v���C���[�𑀍�s�ɂ���
	pPlayer->SetEnableInput(false);

	// �t���[�����o����
	CFrame::Create(20, 120, 40);
}

//=====================================================
// �I��
//=====================================================
void CStateTutorialEnd::Uninit(CTutorial *pTutorial)
{
	if (m_pGate != nullptr)
	{
		m_pGate->Uninit();
		m_pGate = nullptr;
	}

	CStateTutorial::Uninit(pTutorial);
}

//=====================================================
// �X�V
//=====================================================
void CStateTutorialEnd::Update(CTutorial *pTutorial)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;

	// �Q�[�g�̃X�P�[�����O�̕␳
	ScalingGate();

	// �v���C���[�𒼐i�����鏈��
	ForwardPlayer();

	// �Q�[�g�ƃv���C���[�̔���
	CollidePlayer(pTutorial);
}

//=====================================================
// �Q�[�g�̃X�P�[�����O�␳
//=====================================================
void CStateTutorialEnd::ScalingGate(void)
{
	if (m_pGate == nullptr)
		return;

	// �Q�[�g�T�C�Y�̕␳
	D3DXVECTOR3 size =
	{
		m_pGate->GetWidth(),
		m_pGate->GetHeight(),
		0.0f,
	};

	size.x += (SIZE_GATE_EFFECT - size.x) * SPEED_EXPAND_GATE;
	size.y += (SIZE_GATE_EFFECT - size.y) * SPEED_EXPAND_GATE;

	m_pGate->SetSize(size.x, size.y);
}

//=====================================================
// �Q�[�g�ƃv���C���[�Ƃ̔���
//=====================================================
void CStateTutorialEnd::CollidePlayer(CTutorial *pTutorial)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;

	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();
	D3DXVECTOR3 pos = m_pGate->GetPosition();
	D3DXVECTOR3 rot = m_pGate->GetRotation();
	float fWidth = SIZE_GATE_EFFECT;

	D3DXVECTOR3 posStart = { pos.x + sinf(rot.y + D3DX_PI * 0.5f) * fWidth, pos.y, pos.z + cosf(rot.y + D3DX_PI * 0.5f) * fWidth };
	D3DXVECTOR3 posEnd = { pos.x - sinf(rot.y + D3DX_PI * 0.5f) * fWidth, pos.y, pos.z - cosf(rot.y + D3DX_PI * 0.5f) * fWidth };

	float fCross = 0.0f;

	bool bHit = universal::IsCross(posPlayer,		// �v���C���[�̈ʒu
		posStart,		// �S�[���̎n�_
		posEnd,			// �S�[���̏I�_
		&fCross,		// ��_�̊���
		posPlayer + movePlayer);	// �v���C���[�̈ړ���

	bool bHitNext = universal::IsCross(posPlayer + movePlayer,		// �v���C���[�̎���̈ʒu
		posStart,		// �S�[���̎n�_
		posEnd,			// �S�[���̏I�_
		nullptr,		// ��_�̊���
		posPlayer + movePlayer);	// �v���C���[�̈ړ���

	// ���t�F�[�h��������
	CFade *pFade = CFade::GetInstance();

	if (pFade == nullptr)
		return;

	if (bHit)
	{
		pFade->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pFade->SetFade(CScene::MODE_GAME, false);

		// �u���[��������
		CBlurEvent::Create(1.0f, 0.8f, 10.0f);

		m_bFade = true;
	}

	if (pFade->GetState() == CFade::FADE::FADE_OUT && m_bFade)
	{// �t�F�[�h�������n�߂�u�ԂŃQ�[�����X�^�[�g����
		pTutorial->StartGame();

		pTutorial->Uninit();

		// �v���C���[�𑀍�\�ɂ���
		pPlayer->SetEnableInput(true);

		return;
	}

#ifdef _DEBUG
#endif
}

//=====================================================
// �v���C���[�𒼐i�����鏈��
//=====================================================
void CStateTutorialEnd::ForwardPlayer(void)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;
	
	// �v���C���[�𒼐i������
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();

	float fSpeed = pPlayer->GetSpeed();

	posPlayer += pPlayer->GetForward() * fSpeed;

	pPlayer->SetPosition(posPlayer);

	// �ő呬�x�܂ŉ���������
	float fSpeedMax = pPlayer->GetParam().fSpeedMaxInitial;
	float fFactAccele = pPlayer->GetParam().fFactAccele;
	fSpeed += (fSpeedMax - fSpeed) * fFactAccele;

	pPlayer->SetSpeed(fSpeed);
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