//*****************************************************
//
// ゲーム処理[game.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "manager.h"
#include "game.h"
#include "object.h"
#include "inputkeyboard.h"
#include "inputManager.h"
#include "fade.h"
#include "camera.h"
#include "sound.h"
#include "scene.h"
#include "debugproc.h"
#include "UIManager.h"
#include "object3D.h"
#include "texture.h"
#include "skybox.h"
#include "block.h"
#include "renderer.h"
#include "animEffect3D.h"
#include "pause.h"
#include "player.h"
#include "slow.h"
#include "blockManager.h"
#include "meshfield.h"
#include "CameraState.h"
#include "particle.h"
#include "timer.h"
#include "meter.h"
#include "meshRoad.h"
#include "goal.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define TRANS_TIME	(300)	// 終了までの余韻のフレーム数

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CGame::STATE CGame::m_state = STATE_NONE;	// 状態
CGame *CGame::m_pGame = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CGame::CGame()
{
	m_nAddReward = 0;
	m_nCntState = 0;
	m_bStop = false;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CGame::Init(void)
{
	m_pGame = this;

	m_state = STATE_NORMAL;
	m_bStop = false;

	// UIマネージャーの追加
	CUIManager::Create();

	// スカイボックスの生成
	CSkybox::Create();

	// ３Dアニメーション管理の生成
	CAnimEffect3D::Create();

	Sound::Play(CSound::LABEL_BGM_GAME01);

	// フォグをかける
	CRenderer *pRenderer = CRenderer::GetInstance();

	if (pRenderer != nullptr)
	{
		pRenderer->EnableFog(true);
	}

	// 
	CBlockManager::Create();

	// プレイヤーの生成
	CPlayer::Create();

	// スロー管理の生成
	CSlow::Create();

	// タイマー生成
	CTimer::Create();

	// メーター生成
	CMeter::Create();

	// ゴール生成
	CGoal::Create();

	// メッシュロード生成
	CMeshRoad::Create();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CGame::Uninit(void)
{
	// オブジェクト全棄
	CObject::ReleaseAll();

	m_pGame = nullptr;
}

//=====================================================
// 更新処理
//=====================================================
void CGame::Update(void)
{
	CFade *pFade = CFade::GetInstance();
	CInputManager *pInputManager = CInputManager::GetInstance();
	CSound* pSound = CSound::GetInstance();

	if (m_bStop == false)
	{
		// シーンの更新
		CScene::Update();

		//CParticle::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), CParticle::TYPE::TYPE_BEAM_BLADE);

		// カーソルを中心に固定
		SetCursorPos((int)(SCREEN_WIDTH * 0.5f), (int)(SCREEN_HEIGHT * 0.5f));
	}
	else
	{
		// 停止しないオブジェクトの更新
		CObject::UpdateNotStop();
	}

	// カメラ更新
	UpdateCamera();

	// 状態管理
	ManageState();

#ifdef _DEBUG
	Debug();
#endif
}

//=====================================================
// カメラの更新
//=====================================================
void CGame::UpdateCamera(void)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	pCamera->Update();
}

//=====================================================
// 状態管理
//=====================================================
void CGame::ManageState(void)
{
	CFade *pFade = CFade::GetInstance();

	switch (m_state)
	{
	case CGame::STATE_NORMAL:
		break;

		break;
	case CGame::STATE_END:

		m_nCntState++;

		if (m_nCntState >= TRANS_TIME && pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_TITLE);
		}

		break;
	default:
		break;
	}
}

//=====================================================
// デバッグ処理
//=====================================================
void CGame::Debug(void)
{
	// 入力取得
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard == nullptr)
	{
		return;
	}

	if (pKeyboard->GetTrigger(DIK_F))
	{
		m_bStop = m_bStop ? false : true;

		if (m_bStop)
		{
			Camera::ChangeState(new CMoveControl);
		}
		else
		{
			Camera::ChangeState(new CFollowPlayer);
		}
	}
}

//=====================================================
// 描画処理
//=====================================================
void CGame::Draw(void)
{
#ifndef _DEBUG

	return;

#endif

	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	char *apString[STATE::STATE_MAX] =
	{
		"NONE",
		"NORMAL",
		"END",
	};

	pDebugProc->Print("\nゲームの状態[%s]\n", apString[m_state]);
	pDebugProc->Print("停止[%d]\n", m_bStop);
}