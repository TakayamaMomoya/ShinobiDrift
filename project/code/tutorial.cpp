//*****************************************************
//
// チュートリアル処理[tutorial.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
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
// 定数定義
//*****************************************************
namespace
{
const char* PATH_ROAD = "data\\MAP\\road01.bin";	// チュートリアルメッシュロードのパス
const D3DXVECTOR3 POS_DEFAULT_UI = { SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.5f, 0.0f };	// UIのデフォルト位置
const D3DXVECTOR2 SIZE_DEFAULT_UI = { SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f};	// UIのデフォルトサイズ
const float LINE_INPUT = 0.3f;	// 入力と判定するスピード
const float TIME_ACCELE = 5.0f;	// アクセルに必要な時間
const float TIME_BRAKE = 3.0f;	// ブレーキに必要な時間
}

//=====================================================
// コンストラクタ
//=====================================================
CTutorial::CTutorial() : CObject(1), m_pState(nullptr)
{

}

//=====================================================
// デストラクタ
//=====================================================
CTutorial::~CTutorial()
{

}

//=====================================================
// 生成処理
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
// 初期化処理
//=====================================================
HRESULT CTutorial::Init(void)
{
	CMeshRoad::Create(PATH_ROAD);

	// 初期ステイトに設定
	ChangeState(new CStateTutorialMove);

	return S_OK;
}

//=====================================================
// 終了処理
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
// 更新処理
//=====================================================
void CTutorial::Update(void)
{
	if (m_pState != nullptr)
	{
		m_pState->Update(this);
	}

	if (IsEnd())
	{// チュートリアルの終了
		StartGame();

		Uninit();

		return;
	}
}

//=====================================================
// 描画処理
//=====================================================
void CTutorial::Draw(void)
{

}

//=====================================================
// ゲームの開始
//=====================================================
void CTutorial::StartGame(void)
{
	// タイマーの生成
	CTimer::Create();
}

//=====================================================
// ステイトの変更
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
// 制限値の追加
//=====================================================
void CTutorial::AddLimit(int nIdx, float fValue)
{
	m_mapLimit[nIdx] = fValue;
}

//=====================================================
// ステイトの終了
//=====================================================
void CStateTutorial::Uninit(CTutorial *pTutorial)
{
	// UIのマップコンテナクリア
	std::map<int, CUI*> *pMapUI = pTutorial->GetMap();

	for (auto it : *pMapUI)
	{
		it.second->Uninit();
	}

	pMapUI->clear();

	// カウンターのマップコンテナクリア
	std::map<int, float> mapFloat;
	mapFloat.clear();
	pTutorial->SetMapCounter(mapFloat);
}

//=====================================================
// 終了判定
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
// 移動チュートリアル
//********************************************************************************
//=====================================================
// コンストラクタ
//=====================================================
CStateTutorialMove::CStateTutorialMove()
{

}

//=====================================================
// デストラクタ
//=====================================================
CStateTutorialMove::~CStateTutorialMove()
{

}

//=====================================================
// 初期化
//=====================================================
void CStateTutorialMove::Init(CTutorial *pTutorial)
{
	std::map<int, CUI*> *pMapUI = pTutorial->GetMap();
	std::map<int, CUI*> mapUI = *pMapUI;

	// パスの一覧
	const char* apPath[MENU_MAX] =
	{
		"data\\TEXTURE\\UI\\tutorial00.png",
		"data\\TEXTURE\\UI\\tutorial01.png"
	};

	// 制限値の一覧
	float aTime[MENU_MAX] =
	{
		TIME_ACCELE,
		TIME_BRAKE
	};

	for (int i = 0; i < MENU_MAX; i++)
	{
		// 各UIの設定
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

		// 制限値の設定
		pTutorial->AddLimit(i, aTime[i]);
	}

	*pMapUI = mapUI;
}

//=====================================================
// 終了
//=====================================================
void CStateTutorialMove::Uninit(CTutorial *pTutorial)
{
	CStateTutorial::Uninit(pTutorial);
}

//=====================================================
// 更新
//=====================================================
void CStateTutorialMove::Update(CTutorial *pTutorial)
{
	CInputManager *pInputManager = CInputManager::GetInstance();
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pInputManager == nullptr || pPlayer == nullptr)
		return;

	std::map<int, float> mapCounter = pTutorial->GetMapCounter();
	float fDeltaTime = CManager::GetDeltaTime();

	// アクセルの判定
	float fAccele = pInputManager->GetAccele();
	
	if (fAccele > LINE_INPUT)
	{// アクセルのカウンターを加算
		mapCounter[MENU_ACCELE] += fDeltaTime;
	}

	// ブレーキの判定
	float fBrake = pInputManager->GetBrake();

	if (fBrake > LINE_INPUT)
	{// ブレーキのカウンターを加算
		mapCounter[MENU_BRAKE] += fDeltaTime;
	}

	pTutorial->SetMapCounter(mapCounter);

	CDebugProc::GetInstance()->Print("\nアクセルカウンター[%f]ブレーキカウンター[%f]", mapCounter[MENU_ACCELE], mapCounter[MENU_BRAKE]);
	
	if (IsEndInput(MENU_MAX,pTutorial))
	{// 移動チュートリアルを終了
		pTutorial->ChangeState(new CStateTutorialDrift);
	}
}

//********************************************************************************
// ドリフトチュートリアル
//********************************************************************************
//=====================================================
// コンストラクタ
//=====================================================
CStateTutorialDrift::CStateTutorialDrift()
{

}

//=====================================================
// デストラクタ
//=====================================================
CStateTutorialDrift::~CStateTutorialDrift()
{

}

//=====================================================
// 初期化
//=====================================================
void CStateTutorialDrift::Init(CTutorial *pTutorial)
{
	std::map<int, CUI*> *pMapUI = pTutorial->GetMap();
	std::map<int, CUI*> mapUI = *pMapUI;

	// パスの一覧
	const char* apPath[MENU_MAX] =
	{
		"data\\TEXTURE\\UI\\tutorial02.png",
	};

	// 制限値の一覧
	float aTime[MENU_MAX] =
	{
		TIME_ACCELE,
	};

	for (int i = 0; i < MENU_MAX; i++)
	{
		// 各UIの設定
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

		// 制限値の設定
		pTutorial->AddLimit(i, aTime[i]);
	}

	*pMapUI = mapUI;
}

//=====================================================
// 終了
//=====================================================
void CStateTutorialDrift::Uninit(CTutorial *pTutorial)
{
	CStateTutorial::Uninit(pTutorial);
}

//=====================================================
// 更新
//=====================================================
void CStateTutorialDrift::Update(CTutorial *pTutorial)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;

	std::map<int, float> mapCounter = pTutorial->GetMapCounter();
	float fDeltaTime = CManager::GetDeltaTime();

	// ドリフトの判定
	bool bDrift = pPlayer->IsDrift();

	if (bDrift)
	{// ドリフトのカウンターを加算
		mapCounter[MENU_DRIFT] += fDeltaTime;
	}

	pTutorial->SetMapCounter(mapCounter);

	CDebugProc::GetInstance()->Print("\nドリフトカウンター[%f]", mapCounter[MENU_DRIFT]);

	if (IsEndInput(MENU_MAX, pTutorial))
	{// ドリフトチュートリアルを終了
		pTutorial->ChangeState(new CStateTutorialParry);
	}
}

//********************************************************************************
// パリィチュートリアル
//********************************************************************************
//=====================================================
// コンストラクタ
//=====================================================
CStateTutorialParry::CStateTutorialParry()
{

}

//=====================================================
// デストラクタ
//=====================================================
CStateTutorialParry::~CStateTutorialParry()
{

}

//=====================================================
// 初期化
//=====================================================
void CStateTutorialParry::Init(CTutorial *pTutorial)
{
	std::map<int, CUI*> *pMapUI = pTutorial->GetMap();
	std::map<int, CUI*> mapUI = *pMapUI;

	// パスの一覧
	const char* apPath[MENU_MAX] =
	{
		"data\\TEXTURE\\UI\\tutorial03.png",
	};

	// 制限値の一覧
	float aTime[MENU_MAX] =
	{
		TIME_ACCELE,
	};

	for (int i = 0; i < MENU_MAX; i++)
	{
		// 各UIの設定
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

		// 制限値の設定
		pTutorial->AddLimit(i, aTime[i]);
	}

	*pMapUI = mapUI;
}

//=====================================================
// 終了
//=====================================================
void CStateTutorialParry::Uninit(CTutorial *pTutorial)
{
	CStateTutorial::Uninit(pTutorial);
}

//=====================================================
// 更新
//=====================================================
void CStateTutorialParry::Update(CTutorial *pTutorial)
{
	CInputManager *pInputManager = CInputManager::GetInstance();
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pInputManager == nullptr || pPlayer == nullptr)
		return;

	std::map<int, float> mapCounter = pTutorial->GetMapCounter();
	float fDeltaTime = CManager::GetDeltaTime();

	// パリィの判定
	int nMotion = pPlayer->GetMotion();

	if (pInputManager->GetTrigger(CInputManager::BUTTON_KATANA) && (nMotion != CPlayer::MOTION_NINJA::MOTION_NINJA_SLASHDOWN || nMotion != CPlayer::MOTION_NINJA::MOTION_NINJA_SLASHUP))
	{// パリィのカウンターを加算
		mapCounter[MENU_PARRY] += 1.0f;
	}

	pTutorial->SetMapCounter(mapCounter);

	CDebugProc::GetInstance()->Print("\nパリィカウンター[%f]", mapCounter[MENU_PARRY]);

	if (IsEndInput(MENU_MAX, pTutorial))
	{// パリィチュートリアルを終了
		pTutorial->ChangeState(new CStateTutorialFree);
	}
}


//********************************************************************************
// フリーチュートリアル
//********************************************************************************
//=====================================================
// コンストラクタ
//=====================================================
CStateTutorialFree::CStateTutorialFree()
{

}

//=====================================================
// デストラクタ
//=====================================================
CStateTutorialFree::~CStateTutorialFree()
{

}

//=====================================================
// 初期化
//=====================================================
void CStateTutorialFree::Init(CTutorial *pTutorial)
{
	std::map<int, CUI*> *pMapUI = pTutorial->GetMap();
	std::map<int, CUI*> mapUI = *pMapUI;

	// パスの一覧
	const char* apPath[MENU_MAX] =
	{
		"data\\TEXTURE\\UI\\tutorial04.png",
	};

	// 制限値の一覧
	float aTime[MENU_MAX] =
	{
		TIME_ACCELE,
	};

	for (int i = 0; i < MENU_MAX; i++)
	{
		// 各UIの設定
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

		// 制限値の設定
		pTutorial->AddLimit(i, aTime[i]);
	}

	*pMapUI = mapUI;
}

//=====================================================
// 終了
//=====================================================
void CStateTutorialFree::Uninit(CTutorial *pTutorial)
{
	CStateTutorial::Uninit(pTutorial);
}

//=====================================================
// 更新
//=====================================================
void CStateTutorialFree::Update(CTutorial *pTutorial)
{
	CInputManager *pInputManager = CInputManager::GetInstance();
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pInputManager == nullptr || pPlayer == nullptr)
		return;
	
	if (pInputManager->GetTrigger(CInputManager::BUTTON_ENTER))
	{// チュートリアルを終了
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