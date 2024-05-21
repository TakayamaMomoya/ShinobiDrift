//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:髙山桃也
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
#include "inputjoypad.h"
#include "pause.h"
#include "debugproc.h"
#include <string>
#include "blockManager.h"
#include "effect3D.h"
#include "object3D.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const std::string PATH_PARAM = "data\\TEXT\\playerParam.txt";	// パラメーターデータのパス
const float NOTROTATE = 1.0f;		// 回転しないようにする値
const float DIST_LIMIT = 3000.0f;	// ワイヤー制限距離
const float LINE_CORRECT_DRIFT = 40.0f;	// ドリフト補正のしきい値
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
	// 継承クラスの初期化
	CMotion::Init();

	SetMotion(MOTION_WALK_FRONT);

	// カメラの行動設定
	Camera::ChangeState(new CFollowPlayer);

	// 読込
	Load();

	// モデルの設定
	CMotion::Load(&m_param.aPathBody[0]);

	m_info.pRoap = CObject3D::Create(GetPosition());

	m_info.fLengthDrift = 1500.0f;

	m_info.bGrabOld = true;

	return S_OK;
}

//=====================================================
// 読込処理
//=====================================================
void CPlayer::Load(void)
{
	std::ifstream file(PATH_PARAM);

	if (file.is_open())
	{
		std::string temp;

		while (std::getline(file, temp))
		{// 読み込むものがなくなるまで読込
			std::istringstream iss(temp);
			std::string key;
			iss >> key;

			if (key == "BODY_PATH")
			{// 見た目のパス
				iss >> m_param.aPathBody;
			}

			if (key == "SPEED_MAX")
			{// 最大速度
				iss >> m_param.fSpeedMax;
			}

			if (key == "FACT_ACCELE")
			{// 加速係数
				iss >> m_param.fFactAccele;
			}

			if (key == "FACT_ATTENU")
			{// 減速係数
				iss >> m_param.fFactAttenu;
			}

			if (key == "FACT_BRAKE")
			{// ブレーキ減速係数
				iss >> m_param.fFactBrake;
			}

			if (key == "ANGLE_MAX_CURVE")
			{// カーブ最大角度
				iss >> m_param.fAngleMaxCurve;
			}

			if (file.eof())
			{// 読み込み終了
				break;
			}
		}
		
		file.close();
	}
	else
	{
		assert(("ランキングファイルが開けませんでした", false));
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

	InputWire();

	// スピードの管理
	ManageSpeed();


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

	m_info.fSpeedDest = fAccele * m_param.fSpeedMax;

	CDebugProc::GetInstance()->Print("\nアクセル値[%f]", fAccele);

	if (m_info.pBlock == nullptr)
	{
		// ハンドルの操作
		CInputManager::SAxis axis = pInputManager->GetAxis();
		m_info.fAngleHandle = axis.axisMove.x;
	}

	// ブレーキ値の取得
	float fBrake = pInputManager->GetBrake();

	m_info.fSpeed += (0.0f - m_info.fSpeed) * m_param.fFactBrake * fBrake;

	CDebugProc::GetInstance()->Print("\nブレーキ値[%f]", fBrake);
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
// ワイヤーの操作
//=====================================================
void CPlayer::InputWire(void)
{
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();

	if (pJoypad == nullptr)
		return;

	D3DXVECTOR2 vecStickR =
	{
		pJoypad->GetJoyStickRX(0),
		pJoypad->GetJoyStickRY(0)
	};

	float fAngleInput = atan2f(vecStickR.x, vecStickR.y);

	universal::LimitRot(&fAngleInput);

	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	// ブロックのチェック
	CBlock *pBlock = pBlockManager->GetHead();
	D3DXVECTOR3 posPlayer = GetPosition();
	D3DXVECTOR3 rotCamera = CManager::GetCamera()->GetCamera()->rot;

	float fAngle = fAngleInput + rotCamera.y + D3DX_PI;
	universal::LimitRot(&fAngle);

#ifdef _DEBUG
	D3DXVECTOR3 pole = universal::PolarCoordinates(D3DXVECTOR3(GetRotation().x + D3DX_PI * 0.5f , fAngle, 0.0f));

	D3DXVECTOR3 posEffect = GetPosition() + pole * 500.0f;

	CEffect3D::Create(posEffect, 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
#endif


	CBlock *pBlockGrab = nullptr;
	float fAngleMin = D3DX_PI;


	float fLength = sqrtf(vecStickR.x * vecStickR.x + vecStickR.y * vecStickR.y);

	if (m_info.pBlock != nullptr)
	{
		m_info.pBlock->EnableCurrent(true);
	}

	//if (pJoypad->GetPress(CInputJoypad::PADBUTTONS_LB, 0))
	if (m_info.pBlock != nullptr)
	{
		//if (fLength > 0.5f)
		{// 操作している判定
			D3DXVECTOR3 posPlayer = GetPosition();
			D3DXVECTOR3 posBlock = m_info.pBlock->GetPosition();
			D3DXVECTOR3 vecDiff = posBlock - posPlayer;

			universal::VecConvertLength(&vecDiff, 20.0f);

			D3DXVECTOR3 move = GetMove();
			D3DXVECTOR3 rot = GetRotation();

			move += vecDiff;

			SetMove(move);

			float fAngleDiff = atan2f(vecDiff.x, vecDiff.z);
			float fDiff = rot.y - fAngleDiff;

			universal::LimitRot(&fDiff);

			if (m_info.fTimerDriftChange > 0.0f)
			{
				m_info.fTimerDriftChange -= CManager::GetDeltaTime();

				if (pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_DOWN, 0) ||
					pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_LEFT, 0) ||
					pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_UP, 0) ||
					pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_RIGHT, 0))
				{// 弾いた瞬間
					m_info.fTimerFlip = 0.8f;

					m_info.nCntFlip++;

					float fDiffInput = fAngle - fAngleDiff;

					if(fDiffInput * fDiffInput < D3DX_PI * 0.4f * D3DX_PI * 0.4f)
						m_info.fLengthDrift = 25.0f;
				}
				else
				{
					if (m_info.fTimerFlip > 0.0f)
					{// 弾きタイマー減算
						m_info.fTimerFlip -= CManager::GetDeltaTime();
					}
					else
					{// 猶予時間が過ぎると弾きカウンターリセット
						//if (fLength <= 0.5f)
						{// 何も掴んでいなければリセット
							m_info.nCntFlip = 0;
						}
					}
				}
			}

			//if (m_info.nCntFlip >= 1)
			{
				D3DXVECTOR3 rotDest = rot;

				if (fDiff > 0.0f)
				{
					rotDest.y = fAngleDiff + D3DX_PI * 0.5f;

					// カメラロール
					Camera::ControlRoll(0.3f, 0.04f);
				}
				else
				{
					rotDest.y = fAngleDiff - D3DX_PI * 0.5f;

					// カメラロール
					Camera::ControlRoll(-0.3f, 0.04f);
				}

				universal::LimitRot(&rotDest.y);

				universal::FactingRot(&rot.y, rotDest.y, 0.1f);

				SetRotation(rot);

				bool bGrab = m_info.pBlock->CanGrab(posPlayer);

				if (!m_info.bGrabOld && bGrab)
				{
					m_info.nCntFlip = 0;
					m_info.fCntAngle = 0.0f;

					m_info.pBlock = nullptr;

					m_info.fLengthDrift = 1500.0f;
				}

				m_info.bGrabOld = bGrab;

				if (m_info.fLengthDrift <= 50.0f)
				{
					CEffect3D::Create(GetPosition(), 100.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				}
				else
				{
					CEffect3D::Create(GetPosition(), 100.0f, 3, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
				}

				// ドリフトの補正
				LimitDrift(m_info.fLengthDrift);
			}
			//else
			{
				//m_info.fAngleHandle *= 1.9f;

				//CEffect3D::Create(GetPosition(), 100.0f, 3, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
			}

			if (m_info.pRoap != nullptr)
			{
				LPDIRECT3DVERTEXBUFFER9 pVtxBuff = m_info.pRoap->GetVtxBuff();

				//頂点情報のポインタ
				VERTEX_3D *pVtx;

				//頂点バッファをロックし、頂点情報へのポインタを取得
				pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//頂点座標の設定
				float fHeight = 100.0f;

				D3DXVECTOR3 vec = { vecDiff.z, 0.0f, -vecDiff.x };

				D3DXVec3Normalize(&vec, &vec);

				pVtx[0].pos = D3DXVECTOR3(posBlock.x - vec.x * 20.0f, fHeight, posBlock.z);
				pVtx[1].pos = D3DXVECTOR3(posBlock.x + vec.x * 20.0f, fHeight, posBlock.z);
				pVtx[2].pos = D3DXVECTOR3(posPlayer.x - vec.x * 20.0f, fHeight, posPlayer.z);
				pVtx[3].pos = D3DXVECTOR3(posPlayer.x + vec.x * 20.0f, fHeight, posPlayer.z);

				//頂点バッファをアンロック
				pVtxBuff->Unlock();
			}

		}
	}
	else
	{
		// カメラのロール値をまっすぐに戻す
		Camera::ControlRoll(0.0f, 0.1f);

		//if (m_info.nCntFlip == 0)
		{
			while (pBlock != nullptr)
			{
				// 次のアドレスを保存
				CBlock *pBlockNext = pBlock->GetNext();

				D3DXVECTOR3 posBlock = pBlock->GetPosition();
				D3DXVECTOR3 vecDiff = posBlock - posPlayer;
				float fAngleDiff = atan2f(vecDiff.x, vecDiff.z);
				float fDiff = fAngle - fAngleDiff;

				universal::LimitRot(&fDiff);

				pBlock->EnableCurrent(false);

				if (fDiff * fDiff < fAngleMin * fAngleMin)
				{
					float fLengthDiff = sqrtf(vecDiff.x * vecDiff.x + vecDiff.z * vecDiff.z);

					if (/*pBlock->CanGrab(posPlayer) && */fLengthDiff <= DIST_LIMIT)
					{
						pBlockGrab = pBlock;

						fAngleMin = fDiff;
					}
				}

				// 次のアドレスを代入
				pBlock = pBlockNext;
			}

			if (pBlockGrab != nullptr)
			{
				if (pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_DOWN, 0) ||
					pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_LEFT, 0) ||
					pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_UP, 0) ||
					pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_RIGHT, 0))
				{// 弾いた瞬間
					m_info.pBlock = pBlockGrab;

					m_info.fTimerDriftChange = 0.7f;
				}
			}
		}
	}

	CDebugProc::GetInstance()->Print("\n掴んでるブロックはある？[%d]", m_info.pBlock != nullptr);
	CDebugProc::GetInstance()->Print("\nロックオン方向[%f]", fAngle);
}

//=====================================================
// ドリフトの補正
//=====================================================
void CPlayer::LimitDrift(float fLength)
{
	if (m_info.pBlock == nullptr)
		return;

	D3DXVECTOR3 posPlayer = GetPosition();
	D3DXVECTOR3 posBlock = m_info.pBlock->GetPosition();
	D3DXVECTOR3 vecDiff = posPlayer - posBlock;

	vecDiff.y = 0.0f;

	float fLengthDiff = sqrtf(vecDiff.x * vecDiff.x + vecDiff.z * vecDiff.z);

	if (fLengthDiff < DIST_LIMIT - LINE_CORRECT_DRIFT)
	{
		//m_info.fAngleHandle = 0.2f;

		/*universal::VecConvertLength(&vecDiff, fLength);

		D3DXVECTOR3 posDest = posBlock + vecDiff;

		universal::MoveToDest(&posPlayer, posDest, 0.1f);

		SetPosition(posPlayer);*/
	}
	/*else if(fLengthDiff >= fLength + LINE_CORRECT_DRIFT)
	{
		m_info.fAngleHandle = 0.2f;
	}
	else
	{
		m_info.fAngleHandle = 0.0f;
	}*/
}

//=====================================================
// スピードの管理
//=====================================================
void CPlayer::ManageSpeed(void)
{
	CSlow* pSlow = CSlow::GetInstance();

	// スピードの増減
	if (m_info.fSpeedDest >= m_info.fSpeed)
	{// 加速しているとき
		m_info.fSpeed += (m_info.fSpeedDest - m_info.fSpeed) * m_param.fFactAccele;

		CDebugProc::GetInstance()->Print("\n加速中");
	}
	else
	{// 減速しているとき
		m_info.fSpeed += (m_info.fSpeedDest - m_info.fSpeed) * m_param.fFactAttenu;

		CDebugProc::GetInstance()->Print("\n減速中");
	}

	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRotation();

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

	if (m_info.fSpeed >= NOTROTATE)
	{// ハンドルの回転を追加
		rot.y += m_info.fAngleHandle * m_param.fAngleMaxCurve;
		universal::LimitRot(&rot.y);
	}

	SetRotation(rot);

	// 極座標が上を向いている分を補正
	rot.x += D3DX_PI * 0.5f;

	D3DXVECTOR3 vecForward = universal::PolarCoordinates(rot);

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
	pDebugProc->Print("\nプレイヤーの向き[%f,%f,%f]", GetRotation().x, GetRotation().y, GetRotation().z);
	pDebugProc->Print("\n目標速度[%f]", m_info.fSpeedDest);
	pDebugProc->Print("\n現在の速度[%f]", m_info.fSpeed);
	pDebugProc->Print("\n弾きカウンター[%d]", m_info.nCntFlip);
	pDebugProc->Print("\n角度カウンター[%f]", m_info.fCntAngle);
}