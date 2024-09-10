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
// 定数定義
//*****************************************************
namespace
{
const char* PATH_ROAD = "data\\MAP\\road01.bin";	// チュートリアルメッシュロードのパス
const D3DXVECTOR3 POS_DEFAULT_UI = { 0.8f, 0.1f, 0.0f };	// UIのデフォルト位置
const D3DXVECTOR2 SIZE_DEFAULT_UI = { 0.05f, 0.05f};	// UIのデフォルトサイズ
const float LINE_INPUT = 0.3f;	// 入力と判定するスピード
const float TIME_ACCELE = 5.0f;	// アクセルに必要な時間
const float TIME_BRAKE = 3.0f;	// ブレーキに必要な時間
const D3DXVECTOR2 SIZE_GATE = { 3000.0f,3000.0f };	// ゲートのサイズ
const float DIST_GATE = 3000.0f;	// ゲートの距離
const D3DXVECTOR3 ROT_GATE = { D3DX_PI * 0.5f, D3DX_PI * 0.5f, 0.0f };	// ゲートの向き
const float SPEED_RATE_PLAYER = 0.8f;	// プレイヤーがゲートに入るときのスピードの割合
const float SPEED_EXPAND_GATE = 0.2f;	// ゲートの拡張速度
const float SIZE_GATE_EFFECT = 1000.0f;	// ゲートエフェクトの目標サイズ
const float HEIGTH_GATE = 300.0f;	// ゲートの高さ
const D3DXVECTOR3 POS_PLAYER_INITIAL = { -11409.0f,0.0f,26395.0f };	// チュートリアルのプレイヤー初期位置
const D3DXVECTOR3 ROT_PLAYER_INITIAL = { 0.0f,1.77f,0.0f };	// チュートリアルのプレイヤー初期向き
const string PATH_TEXTURE_GATE = "data\\TEXTURE\\EFFECT\\gate00.png";	// ゲートのテクスチャパス
const float SPEED_ROTATE_GATE = 0.05f;	// ゲートの回る速度
const D3DXVECTOR3 POS_PLAYER_END = { -11409.0f, -14.0f,26395.0f };	// プレイヤーのチュートリアル終了時の位置
const D3DXVECTOR3 ROT_PLAYER_END = { 0.0f, 1.77f,0.0f };	// プレイヤーのチュートリアル終了時の位置
const D3DXCOLOR COL_GAUGE_LIMIT = { 0.0f,1.0f,1.0f,1.0f };	// ゲージが満ちた時の色
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

	// プレイヤーをチュートリアルマップにテレポート
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
	// ゲームタイマーの生成
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		pGame->CreateGameTimer();
	}

	// ランクタイマーの生成
	CUIManager *pUIManager = CUIManager::GetInstance();

	if (pUIManager != nullptr)
		pUIManager->CreateRankTImer();

	// プレイヤーのトランスフォームを設定
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;

	pPlayer->SetPosition(Player::DEFAULT_POS);
	pPlayer->SetRotation(Player::DEFAULT_ROT);

	pPlayer->MultiplyMtx(false);

	// カメラの位置を設定
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
		return;

	pCamera->ChangeState(new CFollowPlayer);
	pCamera->SkipToDest();	// 目標位置までカメラを飛ばす
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

	// ゲージの破棄
	for (auto it : m_aGauge)
	{
		it->Uninit();
	}

	m_aGauge.clear();
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

//=====================================================
// UIの生成
//=====================================================
void CStateTutorial::CreateUI(vector<string> aPathTexture, vector<float> aLimit, int nNumMenu, CTutorial *pTutorial)
{
	if (nNumMenu <= 0)
		assert(("チュートリアルのUI生成で不正な数を生成しようとしています", false));

	std::map<int, CUI*> *pMapUI = pTutorial->GetMap();
	std::map<int, CUI*> mapUI = *pMapUI;
	vector<CGauge*> aGauge = GetArrayGauge();
	aGauge.resize(nNumMenu);

	for (int i = 0; i < nNumMenu; i++)
	{
		// 各UIの設定
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

		// ゲージの生成
		aGauge[i] = CGauge::Create(aLimit[i]);
		D3DXVECTOR3 posGauge = { posUI.x, posUI.y + SIZE_DEFAULT_UI.y * 2,0.0f }; // 位置の設定
		aGauge[i]->SetPosition(posGauge);

		// 制限値の設定
		pTutorial->AddLimit(i, aLimit[i]);
	}

	// ゲージ配列の設定
	SetArrayGauge(aGauge);

	*pMapUI = mapUI;
}

//=====================================================
// ゲージのパラメーター設定
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
		{// パラメーターが埋まったら色を変える
			CUI *pUI = aGauge[i]->GetGauge();
			pUI->SetCol(COL_GAUGE_LIMIT);
		}
	}

	SetArrayGauge(aGauge);
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
	// パスの一覧
	vector<string> aPath(MENU_MAX);
	aPath =
	{
		"data\\TEXTURE\\UI\\tutorial00.png",
		"data\\TEXTURE\\UI\\tutorial01.png"
	};

	// 制限値の一覧
	vector<float> aLimit(MENU_MAX);
	aLimit =
	{
		TIME_ACCELE,
		TIME_BRAKE
	};

	CreateUI(aPath, aLimit, MENU_MAX, pTutorial);
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
	std::map<int, float> mapLimit = pTutorial->GetMapLimit();

	float fDeltaTime = CManager::GetDeltaTime();

	// アクセルの判定
	float fAccele = pInputManager->GetAccele();
	
	if (fAccele > LINE_INPUT)
	{// アクセルのカウンターを加算
		mapCounter[MENU_ACCELE] += fDeltaTime;

		universal::LimitValuefloat(&mapCounter[MENU_ACCELE], mapLimit[MENU_ACCELE], 0.0f);
	}

	// ブレーキの判定
	float fBrake = pInputManager->GetBrake();

	if (fBrake > LINE_INPUT)
	{// ブレーキのカウンターを加算
		mapCounter[MENU_BRAKE] += fDeltaTime;

		universal::LimitValuefloat(&mapCounter[MENU_BRAKE], mapLimit[MENU_BRAKE], 0.0f);
	}

	// ゲージパラメーターの設定
	SetParamGauge(MENU_MAX, pTutorial);

	pTutorial->SetMapCounter(mapCounter);

	CDebugProc::GetInstance()->Print("\nアクセルカウンター[%f]ブレーキカウンター[%f]", mapCounter[MENU_ACCELE], mapCounter[MENU_BRAKE]);
	
	if (IsEndInput(MENU_MAX,pTutorial))
	{// 移動チュートリアルを終了
		pTutorial->ChangeState(new CStateTutorialEnd);
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
	// パスの一覧
	vector<string> aPath(MENU_MAX);
	aPath =
	{
		"data\\TEXTURE\\UI\\tutorial02.png",
	};

	// 制限値の一覧
	vector<float> aLimit(MENU_MAX);
	aLimit =
	{
		1.0f,
	};

	CreateUI(aPath, aLimit, MENU_MAX, pTutorial);
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

	// ゲージパラメーターの設定
	SetParamGauge(MENU_MAX, pTutorial);

	pTutorial->SetMapCounter(mapCounter);

	if (IsEndInput(MENU_MAX, pTutorial))
	{// ドリフトチュートリアルを終了
		pTutorial->ChangeState(new CStateTutorialEnd);
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
	// パスの一覧
	vector<string> aPath(MENU_MAX);
	aPath =
	{
		"data\\TEXTURE\\UI\\tutorial03.png",
	};

	// 制限値の一覧
	vector<float> aLimit(MENU_MAX);
	aLimit =
	{
		TIME_ACCELE,
	};

	CreateUI(aPath, aLimit, MENU_MAX, pTutorial);
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

	// ゲージパラメーターの設定
	SetParamGauge(MENU_MAX, pTutorial);

	pTutorial->SetMapCounter(mapCounter);

	CDebugProc::GetInstance()->Print("\nパリィカウンター[%f]", mapCounter[MENU_PARRY]);

	if (IsEndInput(MENU_MAX, pTutorial))
	{// パリィチュートリアルを終了
		pTutorial->ChangeState(new CStateTutorialEnd);
	}
}

//********************************************************************************
// フリーチュートリアル
//********************************************************************************
//=====================================================
// コンストラクタ
//=====================================================
CStateTutorialEnd::CStateTutorialEnd() : m_pGate(nullptr), m_bFade(false)
{

}

//=====================================================
// デストラクタ
//=====================================================
CStateTutorialEnd::~CStateTutorialEnd()
{

}

//=====================================================
// 初期化
//=====================================================
void CStateTutorialEnd::Init(CTutorial *pTutorial)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;

	// プレイヤーのトランスフォームの設定
	pPlayer->SetPosition(POS_PLAYER_END);
	pPlayer->SetRotation(ROT_PLAYER_END);
	pPlayer->MultiplyMtx(false);

	// カメラのステイトを設定
	Camera::ChangeState(new CCameraStateTutorialEnd);

	// ゲート生成のために準備
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
	D3DXVECTOR3 posGate = posPlayer + pPlayer->GetForward() * DIST_GATE;
	posGate.y += HEIGTH_GATE;

	float fAngle = atan2f(pPlayer->GetForward().x, pPlayer->GetForward().z);	// プレイヤーの方を向かせる

	// ゲートの生成
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

	// プレイヤーを操作不可にする
	pPlayer->SetEnableInput(false);

	// フレーム演出生成
	CFrame::Create(20, 120, 40);
}

//=====================================================
// 終了
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
// 更新
//=====================================================
void CStateTutorialEnd::Update(CTutorial *pTutorial)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;

	// ゲートのスケーリングの補正
	ScalingGate();

	// プレイヤーを直進させる処理
	ForwardPlayer();

	// ゲートとプレイヤーの判定
	CollidePlayer(pTutorial);
}

//=====================================================
// ゲートのスケーリング補正
//=====================================================
void CStateTutorialEnd::ScalingGate(void)
{
	if (m_pGate == nullptr)
		return;

	// ゲートサイズの補正
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
// ゲートとプレイヤーとの判定
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

	bool bHit = universal::IsCross(posPlayer,		// プレイヤーの位置
		posStart,		// ゴールの始点
		posEnd,			// ゴールの終点
		&fCross,		// 交点の割合
		posPlayer + movePlayer);	// プレイヤーの移動量

	bool bHitNext = universal::IsCross(posPlayer + movePlayer,		// プレイヤーの次回の位置
		posStart,		// ゴールの始点
		posEnd,			// ゴールの終点
		nullptr,		// 交点の割合
		posPlayer + movePlayer);	// プレイヤーの移動量

	// 白フェードをかける
	CFade *pFade = CFade::GetInstance();

	if (pFade == nullptr)
		return;

	if (bHit)
	{
		pFade->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pFade->SetFade(CScene::MODE_GAME, false);

		// ブラーをかける
		CBlurEvent::Create(1.0f, 0.8f, 10.0f);

		m_bFade = true;
	}

	if (pFade->GetState() == CFade::FADE::FADE_OUT && m_bFade)
	{// フェードが消え始める瞬間でゲームをスタートする
		pTutorial->StartGame();

		pTutorial->Uninit();

		// プレイヤーを操作可能にする
		pPlayer->SetEnableInput(true);

		return;
	}

#ifdef _DEBUG
#endif
}

//=====================================================
// プレイヤーを直進させる処理
//=====================================================
void CStateTutorialEnd::ForwardPlayer(void)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;
	
	// プレイヤーを直進させる
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();

	float fSpeed = pPlayer->GetSpeed();

	posPlayer += pPlayer->GetForward() * fSpeed;

	pPlayer->SetPosition(posPlayer);

	// 最大速度まで加速させる
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