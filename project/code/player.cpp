//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "player.h"
#include "manager.h"
#include "cameraState.h"
#include "camera.h"
#include "slow.h"
#include "inputManager.h"
#include "pause.h"
#include "debugproc.h"
#include <stdio.h>

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const char* BODY_PATH = "data\\MOTION\\motionArms01.txt";	// 見た目のパス
const float SPEED_MOVE = 0.3f;	// 移動速度
const float SPEED_MAX = 30.0f;	// 最大移動速度
const float FACT_ACCELE = 0.01f;	// 加速係数
const float FACT_ATTENU = 0.01f;	// 減速係数
const float FACT_BRAKE = 0.02f;	// ブレーキ係数
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CPlayer *CPlayer::m_pPlayer = nullptr;	// 自身のポインタ

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CPlayer::CPlayer(int nPriority)
{
	m_pPlayer = this;

	ZeroMemory(&m_info, sizeof(CPlayer::SInfo));
	ZeroMemory(&m_param, sizeof(CPlayer::SParam));
	ZeroMemory(&m_fragMotion, sizeof(CPlayer::SFragMotion));
}

//=====================================================
// デストラクタ
//=====================================================
CPlayer::~CPlayer()
{

}

//=====================================================
// 生成処理
//=====================================================
CPlayer *CPlayer::Create(void)
{
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new CPlayer;

		if (m_pPlayer != nullptr)
		{
			m_pPlayer->Init();
		}
	}

	return m_pPlayer;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CPlayer::Init(void)
{
	// モデルの設定
	CMotion::Load((char*)BODY_PATH);

	// 継承クラスの初期化
	CMotion::Init();

	// パラメーターに初期値を入れる
	m_param.fSpeedMove = SPEED_MOVE;

	SetMotion(MOTION_WALK_FRONT);

	// カメラの行動設定
	Camera::ChangeState(new CFollowPlayer);

	// 読込
	Load();

	return S_OK;
}

//=====================================================
// 読込処理
//=====================================================
void CPlayer::Load(void)
{
	char cTemp[256];
	int nThruster = 0;

	FILE *pFile = fopen("data\\TEXT\\playerParam.txt", "r");

	if (pFile != nullptr)
	{
		while (true)
		{
			// ここで読み込んだ文字によって下記のIFにかかる
			(void)fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{
				break;
			}
		}

		fclose(pFile);
	}
}

//=====================================================
// 終了処理
//=====================================================
void CPlayer::Uninit(void)
{
	m_pPlayer = nullptr;

	// 継承クラスの終了
	CMotion::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CPlayer::Update(void)
{
	// 入力
	Input();

	// 前回の位置を保存
	D3DXVECTOR3 pos = GetPosition();
	SetPositionOld(pos);

	// 状態管理
	ManageState();

	// モーション管理
	ManageMotion();

	// 継承クラスの更新
	CMotion::Update();

// デバッグ処理
#if _DEBUG
	Debug();
#endif // _DEBUG
}

//=====================================================
// 入力処理
//=====================================================
void CPlayer::Input(void)
{
	// 移動操作
	InputMove();

	// カメラ操作
	InputCamera();

	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager != nullptr)
	{
		if (pInputManager->GetTrigger(CInputManager::BUTTON_PAUSE))
		{
			CPause::Create();
		}
	}
}

//=====================================================
// 移動の入力
//=====================================================
void CPlayer::InputMove(void)
{
	CSlow *pSlow = CSlow::GetInstance();
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager == nullptr)
	{
		return;
	}

	// アクセル値の取得
	float fAccele = pInputManager->GetAccele();

	m_info.fSpeedDest = fAccele * SPEED_MAX;

	CDebugProc::GetInstance()->Print("\nアクセル値[%f]", fAccele);

	// ブレーキ値の取得
	float fBrake = pInputManager->GetBrake();

	m_info.fSpeed += (0.0f - m_info.fSpeed) * FACT_BRAKE * fBrake;

	CDebugProc::GetInstance()->Print("\nブレーキ値[%f]", fBrake);

	// スピードの管理
	ManageSpeed();
}

//=====================================================
// カメラ操作
//=====================================================
void CPlayer::InputCamera(void)
{
	// 入力マネージャー取得
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager == nullptr)
	{
		return;
	}

	// カメラ取得
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();


}

//=====================================================
// スピードの管理
//=====================================================
void CPlayer::ManageSpeed(void)
{
	CSlow *pSlow = CSlow::GetInstance();

	// スピードの増減
	if (m_info.fSpeedDest >= m_info.fSpeed)
	{// 加速しているとき
		m_info.fSpeed += (m_info.fSpeedDest - m_info.fSpeed) * FACT_ACCELE;

		CDebugProc::GetInstance()->Print("\n加速中");
	}
	else
	{// 減速しているとき
		m_info.fSpeed += (m_info.fSpeedDest - m_info.fSpeed) * FACT_ATTENU;

		CDebugProc::GetInstance()->Print("\n減速中");
	}

	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 vecForward = GetForward();

	// スロー状態を考慮した移動量の調整
	if (pSlow != nullptr)
	{
		float fScale = pSlow->GetScale();

		pos += move * fScale;
		SetPosition(pos);
	}
	else
	{
		pos += move;
		SetPosition(pos);
	}

	// 現在のスピードと前方ベクトルをかけて移動量に適用
	move = vecForward * m_info.fSpeed;

	SetMove(move);
}

//=====================================================
// 状態管理
//=====================================================
void CPlayer::ManageState(void)
{
	switch (m_info.state)
	{
	case STATE_NORMAL:
	{// 通常状態

	}
	default:
		break;
	}
}

//=====================================================
// モーション管理
//=====================================================
void CPlayer::ManageMotion(void)
{
	int nMotion = GetMotion();
	bool bFinish = IsFinish();

	if (m_fragMotion.bMove)
	{// 歩きモーション
		if (nMotion != MOTION_WALK_FRONT)
		{
			SetMotion(MOTION_WALK_FRONT);
		}
	}
	else
	{// 待機モーション
		if (nMotion != MOTION_NEUTRAL)
		{
			SetMotion(MOTION_NEUTRAL);
		}
	}
}

//=====================================================
// イベントの管理
//=====================================================
void CPlayer::Event(EVENT_INFO *pEventInfo)
{
	int nMotion = GetMotion();

	D3DXVECTOR3 offset = pEventInfo->offset;
	D3DXMATRIX mtxParent;
	D3DXMATRIX mtxPart = *GetParts(pEventInfo->nIdxParent)->pParts->GetMatrix();

	universal::SetOffSet(&mtxParent, mtxPart, offset);

	D3DXVECTOR3 pos = { mtxParent._41,mtxParent._42 ,mtxParent._43 };

}

//=====================================================
// 描画処理
//=====================================================
void CPlayer::Draw(void)
{
	// 継承クラスの描画
	CMotion::Draw();

	// デバッグ表示
	Debug();
}

//=====================================================
// ヒット処理
//=====================================================
void CPlayer::Hit(float fDamage)
{

}

//=====================================================
// デバッグ表示
//=====================================================
void CPlayer::Debug(void)
{
#ifndef _DEBUG

	return;

#endif

	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\nプレイヤーの位置[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	pDebugProc->Print("\nプレイヤーの移動量[%f,%f,%f]", GetMove().x, GetMove().y, GetMove().z);
	pDebugProc->Print("\n目標速度[%f]", m_info.fSpeedDest);
	pDebugProc->Print("\n現在の速度[%f]", m_info.fSpeed);
}