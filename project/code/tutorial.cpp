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
CTutorial::CTutorial() : m_pState(nullptr)
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

	// UIの追加
	// アクセル
	CUI *pAccel = Tutorial::CreateUIDefault();
	mapUI[(int)MENU_ACCELE] = pAccel;

	// ブレーキ
	CUI *pBrake = Tutorial::CreateUIDefault();
	mapUI[(int)MENU_BRAKE] = pBrake;

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
	
	if (IsEndInput(pTutorial))
	{// 移動チュートリアルを終了
		pTutorial->EnableEnd(true);
	}
}

//=====================================================
// 終了判定
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