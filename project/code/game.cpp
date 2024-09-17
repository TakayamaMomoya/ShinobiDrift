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
#include "polygon3D.h"
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
#include "edit.h"
#include "editMesh.h"
#include "editMeshfield.h"
#include "editBlock.h"
#include "editGoal.h"
#include "enemy.h"
#include "meshCube.h"
#include "enemySpawner.h"
#include "tutorial.h"
#include "blur.h"
#include "rankTime.h"
#include "light.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define TRANS_TIME	(100)	// 終了までの余韻のフレーム数
namespace
{
const char* PATH_GAME_ROAD = "data\\MAP\\road00.bin";	// ゲームメッシュロードのパス
const D3DXVECTOR3 POS_MESHFIELD = { 342028.0f,1000.0f, -30640.0f };	// メッシュフィールドの位置
const int NUM_LIGHT = 3;	// ライトの数
const D3DXCOLOR COL_LIGHT_DEFAULT = { 0.9f,0.9f,0.9f,1.0f };	// ライトのデフォルト色
const float SPEED_CHANGE_LIGHTCOL = 0.1f;	// ライトの色が変わる速度
}

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
	m_pEdit = nullptr;
	m_pGameTimer = nullptr;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CGame::Init(void)
{
	m_pGame = this;

	m_colLight = COL_LIGHT_DEFAULT;
	m_state = STATE_NORMAL;
	m_bStop = false;

	// UIマネージャーの追加
	CUIManager::Create();

	// スカイボックスの生成
	CSkybox::Create();

	// BGM再生
	CSound* pSound = CSound::GetInstance();

	if(pSound != nullptr)
		pSound->Play(pSound->LABEL_BGM_GAME01);

	// フォグをかける
	CRenderer *pRenderer = CRenderer::GetInstance();

	if (pRenderer != nullptr)
	{
		pRenderer->EnableFog(true);
		pRenderer->SetStart(50000);
		pRenderer->SetEnd(70000);
		pRenderer->SetCol(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
	}

	// ブロックマネージャー生成
	CBlockManager::Create();

	// プレイヤーの生成
	CPlayer::Create();

	// スロー管理の生成
	CSlow::Create();
	
	// メッシュロード生成
	CMeshRoad::Create(PATH_GAME_ROAD);

#if 0
	CGoal::Create(D3DXVECTOR3(432987.3f, -1721.7f, -301192.4f), D3DX_PI);
	// チュートリアルの生成
	CTutorial::Create();
#else
	// ゴール生成
	CGoal::Create(D3DXVECTOR3(12726.0f, 2500.7f, -27695.0f), D3DX_PI);
	CreateGameTimer();
	CRankTime::Create();
#endif

	// メッシュフィールドの生成
	CMeshField *pMeshField = CMeshField::Create();

	if (pMeshField != nullptr)
	{
		pMeshField->SetPosition(POS_MESHFIELD);
	}

	// ライトの生成
	CreateLight();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CGame::Uninit(void)
{
	ReleaseGameTimer();

	if (m_pEdit != nullptr)
	{
		m_pEdit->Uninit();
		delete m_pEdit;
		m_pEdit = nullptr;
	}

	CSound* pSound = CSound::GetInstance();

	if (pSound != nullptr)
		pSound->Stop();

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

	//if (!m_bStop)
	{
		// シーンの更新
		CScene::Update();
	}

	// カメラ更新
	UpdateCamera();

	// 状態管理
	ManageState();

	// タイマーの更新
	UpdateGameTimer();

	// ライトの更新
	UpdateLight();

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
	case CGame::STATE_RESULT:

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
// ゲームタイマーの更新
//=====================================================
void CGame::UpdateGameTimer(void)
{
	if (m_pGameTimer == nullptr || m_state != STATE::STATE_NORMAL)
		return;

	float fSecond = CManager::GetDeltaTime();

	m_pGameTimer->AddSecond(fSecond);
}

//=====================================================
// 停止状態の切り替え
//=====================================================
void CGame::ToggleStop(void)
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

//=====================================================
// エディターの変更
//=====================================================
void CGame::ChangeEdit(CEdit *pEdit)
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
// ライトの生成
//=====================================================
void CGame::CreateLight(void)
{
	D3DXVECTOR3 aDir[NUM_LIGHT] =
	{
		{ -1.4f, 0.24f, -2.21f, },
		{ 1.42f, -0.8f, 0.08f },
		{ -0.29f, -0.8f, 0.55f }
	};

	for (int i = 0; i < NUM_LIGHT; i++)
	{
		CLight *pLight = CLight::Create();

		if (pLight == nullptr)
			continue;

		D3DLIGHT9 infoLight = pLight->GetLightInfo();

		infoLight.Type = D3DLIGHT_DIRECTIONAL;
		infoLight.Diffuse = m_colLight;

		D3DXVECTOR3 vecDir = aDir[i];
		D3DXVec3Normalize(&vecDir, &vecDir);		//ベクトル正規化
		infoLight.Direction = vecDir;
		
		pLight->SetLightInfo(infoLight);
	}
}

//=====================================================
// ライトの更新
//=====================================================
void CGame::UpdateLight(void)
{
	for (auto it : m_aLight)
	{
		D3DLIGHT9 infoLight = it->GetLightInfo();

		D3DXCOLOR col = infoLight.Diffuse;

		col += (m_colLight - col) * SPEED_CHANGE_LIGHTCOL;

		infoLight.Diffuse = col;

		it->SetLightInfo(infoLight);
	}
}

//=====================================================
// ライトの色リセット
//=====================================================
void CGame::ResetDestColLight(void)
{
	m_colLight = COL_LIGHT_DEFAULT;
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
	{// 停止状態の切り替え
		ToggleStop();
	}

	if (pKeyboard->GetTrigger(DIK_F2))
	{// エディット削除
		ToggleStop();
	}

	if (pKeyboard->GetTrigger(DIK_F6))
	{// ランキングリセットボタン
		vector<float> aTime(3);

		aTime = { 200.0f,400.0f,500.0f };

		RankTime::SaveRankTime(aTime);
	}

	ImGui::Text("[EditMode]");

	if (ImGui::Button("MeshRoad", ImVec2(70, 30)))	// メッシュロードエディット
		ChangeEdit(new CEditMesh);

	if (ImGui::Button("MeshField", ImVec2(70, 30)))	// メッシュフィールドエディット
		ChangeEdit(new CEditMeshfield);

	if (ImGui::Button("Block", ImVec2(70, 30)))	// ブロックエディット
		ChangeEdit(new CEditBlock);

	if (ImGui::Button("Goal", ImVec2(70, 30)))	// ゴールエディット
		ChangeEdit(new CEditGoal);

	if (m_pEdit != nullptr)
		m_pEdit->Update();
}

//=====================================================
// ゲームタイマー生成
//=====================================================
void CGame::CreateGameTimer(void)
{
	if (m_pGameTimer != nullptr)
		return;

	m_pGameTimer = CTimer::Create();
}

//=====================================================
// ゲームタイマー解放
//=====================================================
void CGame::ReleaseGameTimer(void)
{
	if (m_pGameTimer != nullptr)
	{
		m_pGameTimer->Uninit();
		m_pGameTimer = nullptr;
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
}