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
#include <stdio.h>
#include "UIManager.h"
#include "object3D.h"
#include "texture.h"
#include "skybox.h"
#include "editBlock.h"
#include "block.h"
#include "renderer.h"
#include "animEffect3D.h"
#include "pause.h"
#include "slow.h"
#include "blockManager.h"
#include "meshRoad.h"
#include "editMesh.h"
#include "effect3D.h"
#include "myLib.h"
#include "motion.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define TRANS_TIME	(60)	// 終了までの余韻のフレーム数

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
	m_nCntState = 0;
	m_bStop = false;
	m_bBlock = false;
	m_pEdit = nullptr;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CGame::Init(void)
{
	m_pGame = this;

	m_state = STATE_NORMAL;
	m_bStop = true;

	// UIマネージャーの追加
	CUIManager::Create();

	// スカイボックスの生成
	CSkybox::Create();

	// ３Dアニメーション管理の生成
	CAnimEffect3D::Create();

	// サウンドインスタンスの取得
	CSound* pSound = CSound::GetInstance();

	// ブロック管理の生成
	CBlockManager::Create();
	
	// フォグをかける
	CRenderer *pRenderer = CRenderer::GetInstance();

	// スロー管理の生成
	CSlow::Create();

	// メッシュロードの生成
	CMeshRoad::Create();

	m_pEdit = new CEditMesh;
	m_pEdit->Init();

	// プレイヤーのサイズ確認用のモデル生成
	CMotion::Create("data\\MOTION\\motionBike.txt");

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CGame::Uninit(void)
{
	m_pEdit->Uninit();

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

	m_pEdit->Update();

	// シーンの更新
	CScene::Update();

	if (m_bStop == false)
	{
		// カーソルを中心に固定
		SetCursorPos((int)(SCREEN_WIDTH * 0.5f), (int)(SCREEN_HEIGHT * 0.5f));

		if (pInputManager != nullptr)
		{
			if (pInputManager->GetTrigger(CInputManager::BUTTON_PAUSE))
			{
				CPause::Create();
			}
		}
	}
	else
	{
		// 停止しないオブジェクトの更新
		CObject::UpdateNotStop();

		CPause *pPause = CPause::GetInstance();

		if (pPause != nullptr)
		{
			pPause->Update();
		}
	}

	// カメラ更新
	UpdateCamera();

	// 状態管理
	ManageState();

	if (ImGui::Button("CreateEdge", ImVec2(70, 30)))	// メッシュ生成
		//ChangeState(new CStateEditMeshCreateMesh);

	if (CInputKeyboard::GetInstance()->GetTrigger(DIK_G))
	{
		if (m_pEdit != nullptr)
		{
			m_pEdit->Uninit();
			delete m_pEdit;
			m_pEdit = nullptr;
		}

		if (m_bBlock)
		{
			m_pEdit = new CEditMesh;

			m_bBlock = false;
		}
		else
		{
			m_pEdit = new CEditBlock;

			m_bBlock = true;
		}

		if (m_pEdit != nullptr)
			m_pEdit->Init();
	}

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

	// 操作
	pCamera->Control();
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
			pFade->SetFade(CScene::MODE_RANKING);
		}

		break;
	default:
		break;
	}
}

//=====================================================
// エディターの変更
//=====================================================
void CGame::ChangeEditer(CEdit *pEdit)
{
	if (m_pEdit != nullptr)
	{
		m_pEdit->Uninit();
		delete m_pEdit;
		m_pEdit = nullptr;
	}

	m_pEdit = pEdit;

	if (m_pEdit != nullptr)
	{
		m_pEdit->Init();
	}
}

//=====================================================
// イベントカメラの設定
//=====================================================
void CGame::SetEventCamera(float fTime, D3DXVECTOR3 posRDest, D3DXVECTOR3 posVDest)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->SetEventTimer(fTime);
		pCamera->SetPosRDest(posRDest);
		pCamera->SetPosVDest(posVDest);

		EnableStop(true);
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
}