//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "player.h"
#include "collision.h"
#include "motion.h"
#include "inputManager.h"
#include "inputkeyboard.h"
#include "debugproc.h"
#include "universal.h"
#include "slow.h"
#include "camera.h"
#include "manager.h"
#include "effect3D.h"
#include "meshfield.h"
#include "CameraState.h"
#include "particle.h"
#include "debrisSpawner.h"
#include "game.h"
#include "animEffect3D.h"
#include "anim3D.h"
#include "pause.h"
#include "inpact.h"
#include "sound.h"
#include "UIManager.h"
#include "orbit.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const char* BODY_PATH = "data\\MOTION\\motionArms01.txt";	// 見た目のパス
const float INITIAL_BOOST = 200.0f;	// ブースト残量の初期値
const float REGEN_BOOST = 2.5f;	// ブースト回復量
const float GRAVITY = 0.50f;	// 重力
const float SPEED_ROLL_CAMERA = 0.03f;	// カメラ回転速度
const float SPEED_BULLET = 200.0f;	// 弾速
const float POW_JUMP = 20.0f;	// ジャンプ力
const float POW_STAMP = 30.0f;	// 踏みつけの推進力
const float SPEED_STAMP = 70.0f;	// 踏みつけ水平推進力
const float SPEED_MOVE = 1.6f;	// 移動速度
const float FACT_MOVE = 0.04f;	// 移動の減衰係数
const float SPEED_ASSAULT = 7.0f;	// 突進の移動速度
const float POW_ADDMELEE = 70.0f;	// 追撃の推進力
const float SPEED_DODGE = 100.0f;	// 回避推進力
const float POW_GRAB = 50.0f;	// 掴みの推進力
const float RADIUS_GRAB = 500.0f;	// 掴みの判定
const float POW_THROW = 200.0f;	// 投げの力
const float LENGTH_LOCKON = 5000.0f;	// ロックオンの長さ
const float ANGLE_LOCKON = D3DX_PI * 0.2f;	// ロックオンの角度
const float MELEE_DIST = 500.0f;	// 格闘に移る距離
const float MIN_ANGLE_CAMERA = D3DX_PI * 0.1f;	// カメラの下を見る制限
const float MAX_ANGLE_CAMERA = D3DX_PI * 0.9f;	// カメラの上を見る制限
const float DAMAGE_BULLET = 1.0f;	// 弾の威力
const float DECREASE_PARAM = 2.0f;	// パラメータ全回復にかかる時間
const D3DXVECTOR3 POS_PARAM[CPlayer::PARAM_MAX] =
{// パラメータ表示の位置
	{SCREEN_WIDTH * 0.5f - 370.0f,SCREEN_HEIGHT * 0.5f - 100.0f,0.0f},// 銃
	{SCREEN_WIDTH * 0.5f + 370.0f,SCREEN_HEIGHT * 0.5f - 100.0f,0.0f},// 近接
	{SCREEN_WIDTH * 0.5f + 370.0f,SCREEN_HEIGHT * 0.5f + 100.0f,0.0f},// 掴み
};
const char* PATH_PARAM[CPlayer::PARAM_MAX] =
{// パラメータUIのテクスチャパス
	"data\\TEXTURE\\UI\\frame00.png",
	"data\\TEXTURE\\UI\\frame01.png",
	"data\\TEXTURE\\UI\\frame02.png",
};
const int RAND_SHOT = 60;	// 射撃精度のランダム幅
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

	m_info.rotDest = D3DXVECTOR3(0.0f, 1.57f, 0.0f);
	SetRotation(D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	// 当たり判定の生成
	if (m_info.pCollisionSphere == nullptr)
	{
		m_info.pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_PLAYER, CCollision::TYPE_SPHERE, this);

		if (m_info.pCollisionSphere != nullptr)
		{
			m_info.pCollisionSphere->SetRadius(50.0f);
		}
	}

	if (m_info.pClsnAttack == nullptr)
	{// 球の当たり判定生成
		m_info.pClsnAttack = CCollisionSphere::Create(CCollision::TAG_NONE, CCollision::TYPE_SPHERE, this);

		if (m_info.pClsnAttack != nullptr)
		{// 情報の設定
			m_info.pClsnAttack->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_info.pClsnAttack->SetRadius(0.0f);
		}
	}

	if (m_info.pCollisionCube == nullptr)
	{// 当たり判定生成
		m_info.pCollisionCube = CCollisionCube::Create(CCollision::TAG_PLAYER, this);

		if (m_info.pCollisionCube != nullptr)
		{
			D3DXVECTOR3 vtxMax = { 20.0f,100.0f,20.0f };
			D3DXVECTOR3 vtxMin = { -20.0f,0.0f,-20.0f };

			m_info.pCollisionCube->SetPosition(GetPosition());

			m_info.pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	// パラメーターに初期値を入れる
	m_param.fInitialLife = 300.0f;
	m_info.fLife = m_param.fInitialLife;
	m_param.fSpeedMove = SPEED_MOVE;
	m_param.fInitialBoost = INITIAL_BOOST;
	m_info.state = STATE_NORMAL;
	m_info.bLand = true;

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

	Object::DeleteObject((CObject**)&m_info.pCollisionSphere);
	Object::DeleteObject((CObject**)&m_info.pCollisionCube);
	Object::DeleteObject((CObject**)&m_info.pClsnAttack);

	// 継承クラスの終了
	CMotion::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CPlayer::Update(void)
{
	CSlow *pSlow = CSlow::GetInstance();

	if (m_info.state != CPlayer::STATE::STATE_DEATH)
	{
		// 入力
		Input();

		// プレイヤーの回転
		Rotation();
	}

	// 位置の反映
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	
	// 前回の位置を保存
	SetPositionOld(pos);

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

	move.x += (0 - move.x) * 0.05f;
	move.z += (0 - move.z) * 0.05f;

	SetMove(move);

	// 当たり判定の管理
	ManageCollision();

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

	// 攻撃操作
	InputAttack();

	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		CInputManager *pInputManager = CInputManager::GetInstance();

		if (pInputManager != nullptr)
		{
			if (pInputManager->GetTrigger(CInputManager::BUTTON_PAUSE))
			{
				CPause::Create();
			}
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

	// カメラ取得
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();

	// 目標方向の設定
	CInputManager::SAxis axis = pInputManager->GetAxis();
	D3DXVECTOR3 axisMove = axis.axisMove;

	float fLengthAxis = D3DXVec3Length(&axisMove);

	int nMotion = GetMotion();

	if (fLengthAxis >= 0.3f)
	{// 通常移動時の目標向き設定
		m_info.rotDest.y = atan2f(axisMove.x, axisMove.z);

		CDebugProc *pDebugProc = CDebugProc::GetInstance();

		pDebugProc->Print("\n通常移動");
	}

	D3DXVECTOR3 vecMove = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 rot = GetRotation();

	if (m_fragMotion.bMove && fLengthAxis <= 0.3f)
	{// 急停止フラグ
		m_fragMotion.bStop = true;
	}

	fLengthAxis *= SPEED_MOVE;

	vecMove -= {sinf(rot.y) * fLengthAxis, 0.0f, cosf(rot.y) * fLengthAxis};

	// 移動速度の設定
	D3DXVECTOR3 move = GetMove();

	D3DXVec3Normalize(&vecMove, &vecMove);
	vecMove *= m_param.fSpeedMove;

	if (pSlow != nullptr)
	{
		float fScale = pSlow->GetScale();

		vecMove *= fScale;
	}

	if (m_info.bLand)
	{
		if (pInputManager->GetTrigger(CInputManager::BUTTON_JUMP))
		{// ジャンプ操作
			m_fragMotion.bJump = true;
			m_fragMotion.bMove = false;

			Sound::Play(CSound::LABEL_SE_BOOST00);
		};
	}

	float fAngleInput = atan2f(axisMove.x, axisMove.z);

	move += vecMove;

	SetMove(move);

#ifdef _DEBUG
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard != nullptr)
	{
		if (pKeyboard->GetTrigger(DIK_RETURN))
		{// スローにする
			if (pSlow != nullptr)
			{
				pSlow->SetScale(0.25f);
			}
		}

		if (pKeyboard->GetRelease(DIK_RETURN))
		{// スロー解除
			CSlow *pSlow = CSlow::GetInstance();

			if (pSlow != nullptr)
			{
				pSlow->SetScale(1.0f);
			}
		}

		if (pKeyboard->GetTrigger(DIK_O))
		{// 可動パーツリセット
			ResetEnableMotion();
		}
	}
#endif
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
	
	// 方向入力の取得
	CInputManager::SAxis axis = pInputManager->GetAxis();
	D3DXVECTOR3 axisCamera = axis.axisCamera;

	// カメラの回転
	pInfoCamera->rot.x += axisCamera.y * SPEED_ROLL_CAMERA;
	pInfoCamera->rot.y += axisCamera.x * SPEED_ROLL_CAMERA;

	universal::LimitValue(&pInfoCamera->rot.x, MAX_ANGLE_CAMERA, MIN_ANGLE_CAMERA);

	universal::LimitRot(&pInfoCamera->rot.x);
	universal::LimitRot(&pInfoCamera->rot.y);
}

//=====================================================
// 攻撃の入力
//=====================================================
void CPlayer::InputAttack(void)
{
	CInputManager *pInputManager = CInputManager::GetInstance();
	int nMotion = GetMotion();

	if (pInputManager == nullptr)
	{
		return;
	}
}

//=====================================================
// プレイヤーの回転
//=====================================================
void CPlayer::Rotation(void)
{
	// 移動方向の取得
	D3DXVECTOR3 move = GetMove();

	float fAngleMove = atan2f(-move.x, -move.z);
	float fLenghtMove = sqrtf(move.x * move.x + move.z * move.z);

	int nMotion = GetMotion();

	if (fLenghtMove >= 6.0f)
	{
		// 向きの補正
		D3DXVECTOR3 rot = GetRotation();

		SetRotation(rot);

		if (m_info.bLand)
		{
			m_fragMotion.bMove = true;
		}
	}
	else
	{
		m_fragMotion.bMove = false;
	}

	m_info.rotDest.x = 0.0f;

	// 向きの補正
	D3DXVECTOR3 rot = GetRotation();

	float fFact = 0.1f;

	universal::FactingRot(&rot.y, m_info.rotDest.y + D3DX_PI, fFact);
	universal::FactingRot(&rot.x, m_info.rotDest.x, fFact);

	SetRotation(rot);
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
		break;
	case STATE_DAMAGE:
	{// ダメージ状態

	}
		break;
	case STATE_DEATH:
	{// 死亡状態

	}
		break;
	default:
		break;
	}
}

//=====================================================
// 当たり判定管理
//=====================================================
void CPlayer::ManageCollision(void)
{
	// 当たり判定の追従
	if (m_info.pCollisionSphere != nullptr)
	{
		bool bLandMesh = false;
		bool bLandBlock = false;
		int nMotion = GetMotion();

		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 posWaist = GetMtxPos(0);
		D3DXVECTOR3 move = GetMove();

		// 敵との接触判定
		m_info.pCollisionSphere->SetPosition(posWaist + move);

		if (m_info.pCollisionCube != nullptr)
		{
			pos = GetPosition();
			D3DXVECTOR3 posCollision = m_info.pCollisionCube->GetPosition();

			// 判定の追従
			m_info.pCollisionCube->SetPositionOld(posCollision);
			m_info.pCollisionCube->SetPosition(pos);

			// ブロックとの押し出し判定
			bLandBlock = m_info.pCollisionCube->CubeCollision(CCollision::TAG_BLOCK, &move);

			// メッシュフィールドとの当たり判定
			pos = GetPosition();
			D3DXVECTOR3 posOld = GetPositionOld();

			CMeshField *pMesh = CMeshField::GetInstance();

			if (pMesh != nullptr)
			{
				float fHeight = pMesh->GetHeight(pos,&move);

				if (pos.y <= fHeight)
				{
					pos.y = fHeight;
					move.y = 0.0f;

					SetPosition(pos);

					bool bFinish = IsFinish();

					bLandMesh = true;
				}
			}

			SetMove(move);
		}

		m_info.pCollisionSphere->PushCollision(&pos, CCollision::TAG::TAG_FLOWER);

		if (pos.y > 4000.0f)
		{
			pos.y = 4000.0f;
		}

		SetPosition(pos);

		m_info.bLand = bLandMesh || bLandBlock;
		m_fragMotion.bAir = !m_info.bLand;
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
// 前方に移動量を加える
//=====================================================
void CPlayer::AddMoveForward(float fSpeed)
{
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 vecMove = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 rot = GetRotation();

	vecMove =
	{
		sinf(rot.x - D3DX_PI * 0.5f) * sinf(rot.y) * fSpeed,
		cosf(rot.x - D3DX_PI * 0.5f) * fSpeed,
		sinf(rot.x - D3DX_PI * 0.5f) * cosf(rot.y) * fSpeed
	};

	move += vecMove;

	SetMove(move);
}

//=====================================================
// 上に移動量を加える
//=====================================================
void CPlayer::AddMoveUp(float fSpeed)
{
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 vecMove = { 0.0f,0.0f,0.0f };

	vecMove.y += fSpeed;

	move += vecMove;

	SetMove(move);
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
// 死亡処理
//=====================================================
void CPlayer::Death(void)
{
	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		pSound->Stop(CSound::LABEL_SE_WARNING00);
	}

	Sound::Play(CSound::LABEL_SE_EXPLOSION01);

	D3DXVECTOR3 pos = GetMtxPos(0);

	// エフェクト発生
	CAnimEffect3D *pAnimManager = CAnimEffect3D::GetInstance();

	if (pAnimManager != nullptr)
	{
		CAnim3D *pAnim = pAnimManager->CreateEffect(pos, CAnimEffect3D::TYPE_EXPLOSION);

		if (pAnim != nullptr)
		{
			pAnim->SetSize(600.0f, 600.0f);
		}
	}

	// 破片生成
	CDebrisSpawner::Create(pos, CDebrisSpawner::TYPE::TYPE_DEATH);
	
	Uninit();
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
	pDebugProc->Print("\n体力[%f]", m_info.fLife);
	for (int i = 0; i < PARAM_MAX; i++)

	int nMotion = GetMotion();

	pDebugProc->Print("\n着地[%d]", m_info.bLand);
	pDebugProc->Print("\n空中[%d]", m_fragMotion.bAir);

	CInputKeyboard *pKey = CInputKeyboard::GetInstance();

	if (pKey != nullptr)
	{
		if (pKey->GetTrigger(DIK_O))
		{
			m_info.fLife = 1.0f;
		}
	}
}