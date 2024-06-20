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
#include "inputjoypad.h"
#include "inputkeyboard.h"
#include "pause.h"
#include "debugproc.h"
#include "blockManager.h"
#include "effect3D.h"
#include "object3D.h"
#include "blur.h"
#include "renderer.h"
#include "meshRoad.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const std::string PATH_PARAM = "data\\TEXT\\playerParam.txt";	// パラメーターデータのパス
const float NOTROTATE = 1.0f;		// 回転しないようにする値
const float DIST_LIMIT = 3000.0f;	// ワイヤー制限距離
const float LINE_CORRECT_DRIFT = 40.0f;	// ドリフト補正のしきい値
const float SIZE_BLUR = -20.0f;	// ブラーのサイズ
const float DENSITY_BLUR = 0.5f;	// ブラーの濃さ
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
	// ブラーをかけない設定にする
	EnableBlur(false);

	// 継承クラスの初期化
	CMotion::Init();

	SetMotion(MOTION_WALK_FRONT);

	// カメラの行動設定
	Camera::ChangeState(new CFollowPlayer);

	// 読込
	Load();

	// モデルの設定
	CMotion::Load(&m_param.aPathBody[0]);

	// バイクに乗っている忍者の初期化とモデルの設定
	if (m_pPlayerNinja == nullptr)
	{
		m_pPlayerNinja = new CMotion;

		if (m_pPlayerNinja != nullptr)
		{
			m_pPlayerNinja->Init();
			m_pPlayerNinja->Load("data\\MOTION\\motionPlayer.txt");
			m_pPlayerNinja->SetMatrix(*GetMatrix());
		}
	}

	m_info.pRoap = CObject3D::Create(GetPosition());

	m_info.fLengthDrift = 1500.0f;
	m_info.bGrabOld = true;
	m_info.fDesityBlurDrift = DENSITY_BLUR;
	m_info.fSizeBlurDrift = SIZE_BLUR;

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

	//当たり判定
	Collision();

	// 前回の位置を保存
	D3DXVECTOR3 pos = GetPosition();
	SetPositionOld(pos);

	// 状態管理
	ManageState();

	// モーション管理
	ManageMotion();

	// 継承クラスの更新
	CMotion::Update();

	if (m_pPlayerNinja != nullptr)
	{
		m_pPlayerNinja->SetPosition(D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z));
		m_pPlayerNinja->SetRotation(GetRotation());
		m_pPlayerNinja->Update();
	}
		

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

	// ワイヤーの操作
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

	if (m_info.pBlockGrab == nullptr)
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
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	if (pJoypad == nullptr)
		return;

	D3DXVECTOR2 vecStickR =
	{
		pJoypad->GetJoyStickRX(0),
		pJoypad->GetJoyStickRY(0)
	};

	// スティック入力角度
	float fAngleInput = atan2f(vecStickR.x, vecStickR.y);

	// 入力角度とカメラ角度を足した角度
	D3DXVECTOR3 rotCamera = CManager::GetCamera()->GetCamera()->rot;

	float fAngle = fAngleInput + rotCamera.y + D3DX_PI;
	universal::LimitRot(&fAngle);

	// スティック入力の強さ
	float fLength = sqrtf(vecStickR.x * vecStickR.x + vecStickR.y * vecStickR.y);

	universal::LimitRot(&fAngleInput);

	// ブロックのチェック
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	CBlock *pBlock = pBlockManager->GetHead();

	if (m_info.pBlockGrab != nullptr)
	{
		m_info.pBlockGrab->EnableCurrent(true);

		// ブラーをかける
		Blur::AddParameter(0.0f, 0.01f, 15.0f, 0.0f, 0.7f);

		// 差分角度の計算
		D3DXVECTOR3 posPlayer = GetPosition();
		D3DXVECTOR3 posBlock = m_info.pBlockGrab->GetPosition();
		D3DXVECTOR3 vecDiff = posBlock - posPlayer;
		float vecLength = D3DXVec3Length(&(posBlock - posPlayer));

		D3DXVECTOR3 vecDiffNormal = vecDiff;
		D3DXVec3Normalize(&vecDiffNormal, &vecDiff);

		D3DXVECTOR3 move = GetMove();
		universal::VecConvertLength(&vecDiff, fabs(D3DXVec3Dot(&move, &vecDiffNormal)));

		// ワイヤーに沿って進める
		ForwardFollowWire(vecLength, vecDiff);

		float fAngleDiff = atan2f(vecDiff.x, vecDiff.z);

		// ドリフトを変えるかの判定
		JudgeChangeDrift(fAngle, fAngleDiff, fLength);

		// 回転の制御
		ManageRotateGrab(fAngleDiff);

		// ワイヤーを外すかの判定
		JudgeRemoveWire(fLength);

		// ドリフトの補正
		LimitDrift(m_info.fLengthDrift);

		// ロープの制御
		ControlRoap();
	}
	else
	{
		// カメラのロール値をまっすぐに戻す
		Camera::ControlRoll(0.0f, 0.1f);

		// 掴むブロックの探知
		SarchGrab();
	}

	if (CInputKeyboard::GetInstance() != nullptr)
	{
		if (CInputKeyboard::GetInstance()->GetTrigger(DIK_F4))
		{// 操作方法変更
			m_info.bManual = m_info.bManual ? false : true;
		}
	}

	CDebugProc::GetInstance()->Print("\n掴んでるブロックはある？[%d]", m_info.pBlockGrab != nullptr);
	CDebugProc::GetInstance()->Print("\nロックオン方向[%f]", fAngleInput);
}

//=====================================================
// ワイヤーに沿って進める
//=====================================================
void CPlayer::ForwardFollowWire(float vecLength,D3DXVECTOR3 vecDiff)
{
	D3DXVECTOR3 move = GetMove();

	if (vecLength < 1000.0f && m_info.fLengthDrift < 500.0f)
	{
		move -= vecDiff * 0.1f;
	}
	else
	{
		move += vecDiff;
	}

	SetMove(move);
}

//=====================================================
// ドリフトを変えるかの判定
//=====================================================
void CPlayer::JudgeChangeDrift(float fAngle, float fAngleDiff, float fLength)
{
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	if (pJoypad == nullptr)
		return;

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

			m_info.fAngleDrift = 0.29f;

			Blur::AddParameter(5.0f, 0.5f, 15.0f, 0.0f, 0.7f);
		}
		else
		{
			if (m_info.fTimerFlip > 0.0f)
			{// 弾きタイマー減算
				m_info.fTimerFlip -= CManager::GetDeltaTime();
			}
			else
			{// 猶予時間が過ぎると弾きカウンターリセット
				if (fLength <= 0.5f)
				{// 何も掴んでいなければリセット
					m_info.nCntFlip = 0;
				}
			}
		}
	}
}

//=====================================================
// ブロックを掴んでるときの回転制御
//=====================================================
void CPlayer::ManageRotateGrab(float fAngleDiff)
{
	D3DXVECTOR3 rot = GetRotation();

	float fDiff = rot.y - fAngleDiff;

	universal::LimitRot(&fDiff);

	D3DXVECTOR3 rotDest = rot;

	if (fDiff > 0.0f)
	{
		rotDest.y = fAngleDiff + D3DX_PI * m_info.fAngleDrift;

		// カメラロール
		Camera::ControlRoll(0.3f, 0.04f);
	}
	else
	{
		rotDest.y = fAngleDiff - D3DX_PI * m_info.fAngleDrift;

		// カメラロール
		Camera::ControlRoll(-0.3f, 0.04f);
	}

	universal::LimitRot(&rotDest.y);

	universal::FactingRot(&rot.y, rotDest.y, 0.15f);

	SetRotation(rot);
}

//=====================================================
// ワイヤーを外すかの判定
//=====================================================
void CPlayer::JudgeRemoveWire(float fLength)
{
	// ブロックのエリア内かの判定
	D3DXVECTOR3 posPlayer = GetPosition();
	bool bGrab = m_info.pBlockGrab->CanGrab(posPlayer);

	if (m_info.bManual)
	{
		if (fLength <= 0.5f)
		{// スティックを離したらワイヤーを外す
			RemoveWire();
		}
	}
	else
	{
		if (m_info.bGrabOld && !bGrab)
		{// ブロック指定のエリアを回り切ったらワイヤーを外す
			RemoveWire();
		}
	}

	// 現在のエリア内かの判定を保存
	m_info.bGrabOld = bGrab;
}

//=====================================================
// ロープの制御
//=====================================================
void CPlayer::ControlRoap(void)
{
	if (m_info.pRoap != nullptr && m_info.pBlockGrab != nullptr)
	{
		D3DXVECTOR3 posPlayer = GetPosition();
		D3DXVECTOR3 posBlock = m_info.pBlockGrab->GetPosition();
		D3DXVECTOR3 vecDiff = posBlock - posPlayer;

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

//=====================================================
// 掴むブロックの探知
//=====================================================
void CPlayer::SarchGrab(void)
{
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	if (pJoypad == nullptr)
		return;

	// 入力角度の計算
	D3DXVECTOR2 vecStickR =
	{
		pJoypad->GetJoyStickRX(0),
		pJoypad->GetJoyStickRY(0)
	};

	float fAngleInput = atan2f(vecStickR.x, vecStickR.y);

	// ブロックマネージャーの取得
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	// 計算用変数
	CBlockGrab *pBlockGrab = nullptr;	
	CBlockGrab* pBlockMin = nullptr;
	float fLengthMin = 0.0f;
	float fAngleMin = D3DX_PI;

	// ブロックリスト取得
	std::list<CBlockGrab*> *pListGrab = pBlockManager->GetListGrab();

	for (CBlockGrab *pBlock : *pListGrab)
	{
		D3DXVECTOR3 posPlayer = GetPosition();
		D3DXVECTOR3 rotPlayer = GetRotation();
		D3DXVECTOR3 posBlock = pBlock->GetPosition();
		D3DXVECTOR3 vecBlockDiff = posBlock - posPlayer;
		float fAngleDiff = atan2f(vecBlockDiff.x, vecBlockDiff.z) - rotPlayer.y;
		float fDiff = fabs(fAngleInput - fAngleDiff);

		universal::LimitRot(&fDiff);
		pBlock->EnableCurrent(false);

		if (fDiff < D3DX_PI * 0.5f && fDiff > -D3DX_PI * 0.5f)
		{
			float fLengthDiff = sqrtf(vecBlockDiff.x * vecBlockDiff.x + vecBlockDiff.z * vecBlockDiff.z);

			if (fLengthDiff <= DIST_LIMIT && (pBlockMin == nullptr || fLengthMin > fLengthDiff))
			{
				pBlockMin = pBlock;

				fAngleMin = fDiff;

				fLengthMin = fLengthDiff;
			}
		}
	}

	if (pBlockMin != nullptr)
	{
		pBlockGrab = pBlockMin;

		m_info.fLengthDrift = fLengthMin;

		if (fLengthMin < 500.0f)
		{
			m_info.fAngleDrift = 0.4f;
		}
		else
		{
			m_info.fAngleDrift = 0.4f;
		}
	}

	if (pBlockGrab != nullptr)
	{
		if (pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_DOWN, 0) ||
			pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_LEFT, 0) ||
			pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_UP, 0) ||
			pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_RIGHT, 0))
		{// 弾いた瞬間
			m_info.pBlockGrab = pBlockGrab;

			m_info.fTimerDriftChange = 0.7f;
		}
	}
}

//=====================================================
// ワイヤーを外す
//=====================================================
void CPlayer::RemoveWire(void)
{
	m_info.nCntFlip = 0;
	m_info.fCntAngle = 0.0f;

	m_info.pBlockGrab = nullptr;

	m_info.fLengthDrift = 0.0f;

	// ブラーを戻す
	Blur::ResetBlur();
}

//=====================================================
// ドリフトの補正
//=====================================================
void CPlayer::LimitDrift(float fLength)
{
	if (m_info.pBlockGrab == nullptr)
		return;

	D3DXVECTOR3 posPlayer = GetPosition();
	D3DXVECTOR3 posBlock = m_info.pBlockGrab->GetPosition();
	D3DXVECTOR3 vecDiff = posPlayer - posBlock;

	vecDiff.y = 0.0f;

	float fLengthDiff = sqrtf(vecDiff.x * vecDiff.x + vecDiff.z * vecDiff.z);

	//if (fLengthDiff < DIST_LIMIT - LINE_CORRECT_DRIFT)
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
// 当たり判定処理
//=====================================================
void CPlayer::Collision(void)
{
	// 前回の位置を保存
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posOld = GetPositionOld();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRotation();
	D3DXVECTOR3 posParts[2];
	D3DXVECTOR3 posOldParts[2];
	D3DXVECTOR3 posDef, posDefOld;
	bool bRoad[2];

	// タイヤの位置保存
	posParts[0].x = GetParts(2)->pParts->GetMatrix()->_41 + (pos.x - posOld.x);
	posParts[0].y = GetParts(2)->pParts->GetMatrix()->_42 + (pos.y - posOld.y) - 41.05f;
	posParts[0].z = GetParts(2)->pParts->GetMatrix()->_43 + (pos.z - posOld.z);
	posParts[1].x = GetParts(3)->pParts->GetMatrix()->_41 + (pos.x - posOld.x);
	posParts[1].y = GetParts(3)->pParts->GetMatrix()->_42 + (pos.y - posOld.y) - 41.1f;
	posParts[1].z = GetParts(3)->pParts->GetMatrix()->_43 + (pos.z - posOld.z);

	// タイヤの過去位置保存
	posOldParts[0].x = GetParts(2)->pParts->GetMatrixOld()->_41 + (pos.x - posOld.x);
	posOldParts[0].y = GetParts(2)->pParts->GetMatrixOld()->_42 + (pos.y - posOld.y) - 41.05f;
	posOldParts[0].z = GetParts(2)->pParts->GetMatrixOld()->_43 + (pos.z - posOld.z);
	posOldParts[1].x = GetParts(3)->pParts->GetMatrixOld()->_41 + (pos.x - posOld.x);
	posOldParts[1].y = GetParts(3)->pParts->GetMatrixOld()->_42 + (pos.y - posOld.y) - 41.1f;
	posOldParts[1].z = GetParts(3)->pParts->GetMatrixOld()->_43 + (pos.z - posOld.z);

	//// タイヤの中点を計算
	posDef = posParts[0] + posParts[1] * 0.5f;

	// タイヤそれぞれで当たり判定をとる
	bRoad[0] = CMeshRoad::GetInstance()->CollisionRoad(&posParts[0], posOldParts[0]);
	bRoad[1] = CMeshRoad::GetInstance()->CollisionRoad(&posParts[1], posOldParts[1]);

	// プレイヤーの高さを調整
	pos.y += (posParts[0] + posParts[1] * 0.5f).y - posDef.y;

	// タイヤの位置関係から角度を計算
	if ((posParts[1].y - posParts[0].y) < D3DXVec3Length(&(posParts[0] - posParts[1])))
		rot.x = asinf((posParts[1].y - posParts[0].y) / D3DXVec3Length(&(posParts[0] - posParts[1])));

	if (bRoad[0] && bRoad[1])
	{// タイヤが両方道に触れているとき

		// 角度によって重力変更
		if (rot.x < 0.0f)
		{
			move.y = -20.0f;
		}
		else
		{
			move.y = -20.0f;
		}
	}
	else if (bRoad[0])
	{// タイヤが片方だけ道に触れているとき
		rot.x -= 0.01f;
	}
	else if (bRoad[1])
	{// タイヤが片方だけ道に触れているとき
		rot.x += 0.01f;
	}
	else
	{// タイヤがどちらも道に触れていないとき
		rot.x += 0.015f;
	}

	if (CInputKeyboard::GetInstance() != nullptr)
	{
		if (CInputKeyboard::GetInstance()->GetPress(DIK_SPACE))
		{// 操作方法変更
			pos.y += 15.0f;
			move.y = 0.0f;
			rot.x = 0.0f;
		}
	}

	// 位置と移動量と角度を代入
	SetPosition(pos);
	SetMove(move);
	SetRotation(rot);
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
	move.x = vecForward.x * m_info.fSpeed;
	move.z = vecForward.z * m_info.fSpeed;

	// 移動量に重力を適用
	move.y += -0.6f;

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
	pDebugProc->Print("\nブラーのサイズ[%f]", m_info.fSizeBlurDrift);
	pDebugProc->Print("\nブラーの濃さ[%f]", m_info.fDesityBlurDrift);

	// ブラーのサイズ調整
	if (CInputKeyboard::GetInstance()->GetPress(DIK_UP))
	{
		m_info.fSizeBlurDrift += 0.3f;
	}
	else if (CInputKeyboard::GetInstance()->GetPress(DIK_DOWN))
	{
		m_info.fSizeBlurDrift -= 0.3f;
	}

	// ブラーの濃さ調整
	if (CInputKeyboard::GetInstance()->GetPress(DIK_LEFT))
	{
		m_info.fDesityBlurDrift += 0.03f;
	}
	else if (CInputKeyboard::GetInstance()->GetPress(DIK_RIGHT))
	{
		m_info.fDesityBlurDrift -= 0.03f;
	}
}