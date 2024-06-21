//*****************************************************
//
// カメラステイト[CameraState.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "CameraState.h"
#include "camera.h"
#include "player.h"
#include "effect3D.h"
#include "inputmouse.h"
#include "inputkeyboard.h"
#include "debugproc.h"
#include "block.h"
#include "manager.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float MOVE_SPEED = 3.0f;	//移動スピード
const float ROLL_SPEED = 0.02f;	//回転スピード
const float FACT_CORRECT_POS = 0.2f;	// 位置補正係数
const float LENGTH_FOLLOW = 412.0f;	// 追従時のカメラ距離
const float ANGLE_FOLLOW = 0.73f;	// 追従時のカメラ角度
const float LENGTHPOSR_FOLLOW = 4126.0f;	// 追従時の先を見る距離
const float FOV_FOLLOW = 93.0f;	// 追従時の視野角
}

//***********************************************************************************
// プレイヤーの追従
//***********************************************************************************
//=====================================================
// コンストラクタ
//=====================================================
CFollowPlayer::CFollowPlayer() : m_fTimerPosR(0.0f), m_fLengthPosR(0.0f),m_bDebug(false)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		CCamera::Camera *pInfoCamera = pCamera->GetCamera();

		pInfoCamera->fLength = LENGTH_FOLLOW;

		pInfoCamera->rot.x = ANGLE_FOLLOW;
	}

	m_fLengthPosR = LENGTHPOSR_FOLLOW;
}

//=====================================================
// 更新
//=====================================================
void CFollowPlayer::Update(CCamera *pCamera)
{
	if (pCamera == nullptr)
		return;

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
	{
		return;
	}

	D3DXVECTOR3 pos = pPlayer->GetMtxPos(0);

	// 注視点の設定
	CBlock *pBlock = pPlayer->GetBlock();

	if (pBlock != nullptr)
	{// ブロックを掴んでいる場合、中間に視点を向ける
		D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
		D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();
		D3DXVECTOR3 posBlock = pBlock->GetPosition();
		D3DXVECTOR3 vecDiff = posBlock - posPlayer;
		
		// 視点の設定
		float fAngleDiff = atan2f(vecDiff.x, vecDiff.z);
		float fDiff = rotPlayer.y - fAngleDiff;
		universal::LimitRot(&fDiff);

		universal::FactingRot(&pInfoCamera->rot.y, fAngleDiff + D3DX_PI, 0.04f);

		D3DXVECTOR3 vecPole = universal::PolarCoordinates(pInfoCamera->rot);

#ifdef _DEBUG
		CEffect3D::Create(pPlayer->GetMtxPos(2) + vecPole * 500.0f, 20.0f, 3, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
#endif
		// 追従時の視点からラープ(視点)
		D3DXVECTOR3 vecPoleOld = universal::PolarCoordinates(m_rotROld);
		D3DXVECTOR3 posOld = pPlayer->GetMtxPos(2) + vecPoleOld * pInfoCamera->fLength;
		D3DXVECTOR3 posDest = pPlayer->GetMtxPos(2) + vecPole * pInfoCamera->fLength;

		m_fTimerPosR += CManager::GetDeltaTime();

		float fTime = m_fTimerPosR / 1.0f;
		universal::LimitValue(&fTime, 1.0f, 0.0f);

		pInfoCamera->posVDest = pos + vecPole * pInfoCamera->fLength;

		// 注視点の設定
		D3DXVECTOR3 posOldR = pPlayer->GetMtxPos(2);
		D3DXVECTOR3 posDestR = posPlayer + vecDiff * 0.3f;
		pInfoCamera->posRDest = universal::Lerp(posOldR, posDestR, fTime);

		// 目標位置に補正
		pInfoCamera->posV += (pInfoCamera->posVDest - pInfoCamera->posV) * 0.2f;
		pInfoCamera->posR += (pInfoCamera->posRDest - pInfoCamera->posR) * 0.3f;
	}
	else
	{
		m_fTimerPosR = 0.0f;

		universal::FactingRot(&pInfoCamera->rot.y, pPlayer->GetRotation().y + D3DX_PI, 0.1f);

		universal::LimitRot(&pInfoCamera->rot.y);

		D3DXMATRIX *pMtx = pPlayer->GetMatrix();

		D3DXVECTOR3 vecAddPosR = { pMtx->_31, pMtx->_32, pMtx->_33 };

		pInfoCamera->posRDest = pos + vecAddPosR * m_fLengthPosR;

		pInfoCamera->posRDest.y += 50.0f;	// 一旦むりやりちょっと高くする

		// 目標の視点設定
		D3DXVECTOR3 vecPole = universal::PolarCoordinates(pInfoCamera->rot);
		pInfoCamera->posVDest = pos + vecPole * pInfoCamera->fLength;

		pCamera->MoveDist(FACT_CORRECT_POS);

		m_rotROld = pInfoCamera->rot;
	}

#ifdef _DEBUG
	CEffect3D::Create(pInfoCamera->posRDest, 20.0f, 1, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	CDebugProc::GetInstance()->Print("\nカメラはプレイヤー追従です");

	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard != nullptr)
	{
		if (pKeyboard->GetPress(DIK_U))
			pInfoCamera->fViewAngle += 5.5f;
		if (pKeyboard->GetPress(DIK_J))
			pInfoCamera->fViewAngle -= 5.5f;

		if (pKeyboard->GetPress(DIK_Y))
			pInfoCamera->fLength += 10.5f;
		if (pKeyboard->GetPress(DIK_H))
			pInfoCamera->fLength -= 10.5f;

		if (pKeyboard->GetPress(DIK_T))
			pInfoCamera->rot.x += 0.03f;
		if (pKeyboard->GetPress(DIK_G))
			pInfoCamera->rot.x -= 0.03f;

		if (pKeyboard->GetPress(DIK_N))
			m_fLengthPosR += 10.5f;
		if (pKeyboard->GetPress(DIK_M))
			m_fLengthPosR -= 10.5f;

		if (pKeyboard->GetTrigger(DIK_K))
		{
			if (m_bDebug)
			{
				pInfoCamera->fViewAngle = FOV_FOLLOW;
				pInfoCamera->fLength = LENGTH_FOLLOW;
				pInfoCamera->rot.x = ANGLE_FOLLOW;
				m_fLengthPosR = LENGTHPOSR_FOLLOW;

				m_bDebug = false;
			}
			else
			{
				pInfoCamera->fViewAngle = 65.0f;
				pInfoCamera->fLength = 1462.0f;
				pInfoCamera->rot.x = 1.18f;
				m_fLengthPosR = 241.0f;

				m_bDebug = true;
			}
		}

		CDebugProc::GetInstance()->Print("\n[調整カメラ値]");
		CDebugProc::GetInstance()->Print("\n視野角[%f]", pInfoCamera->fViewAngle);
		CDebugProc::GetInstance()->Print("\nカメラ距離[%f]", pInfoCamera->fLength);
		CDebugProc::GetInstance()->Print("\n角度[%f]", pInfoCamera->rot.x);
		CDebugProc::GetInstance()->Print("\n先を見る距離[%f]", m_fLengthPosR);
		CDebugProc::GetInstance()->Print("\n[調整カメラ値]");
	}
#endif
}

//=====================================================
// 操作する
//=====================================================
void CMoveControl::Update(CCamera *pCamera)
{
	if (pCamera == nullptr)
		return;

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();

	// 入力取得
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse *pMouse = CInputMouse::GetInstance();

	float fMove = MOVE_SPEED;

	//マウス操作======================================================
	if (pMouse->GetPress(CInputMouse::BUTTON_RMB) == true)
	{//右クリック中、視点旋回
		D3DXVECTOR3 rot;

		//マウスの移動量代入
		rot = { (float)pMouse->GetMoveIX() * ROLL_SPEED, (float)pMouse->GetMoveIY() * ROLL_SPEED, 0.0f };

		D3DXVec3Normalize(&rot, &rot);

		//視点の旋回
		pInfoCamera->rot.y += rot.x * ROLL_SPEED;
		pInfoCamera->rot.x -= rot.y * ROLL_SPEED;

		if (pKeyboard->GetPress(DIK_LSHIFT) == true)
		{//加速
			fMove *= 3;
		}

		D3DXVECTOR3 rotMove = pInfoCamera->rot;
		D3DXVECTOR3 vecPole = { 0.0f,0.0f,0.0f };

		//視点移動===============================================
		if (pKeyboard->GetPress(DIK_A) == true)
		{//左移動
			rotMove.y += D3DX_PI * 0.5f;

			universal::LimitRot(&rotMove.y);

			vecPole += universal::PolarCoordinates(rotMove);
			vecPole.y = 0.0f;
		}
		if (pKeyboard->GetPress(DIK_D) == true)
		{//右移動
			rotMove.y -= D3DX_PI * 0.5f;

			universal::LimitRot(&rotMove.y);

			vecPole += universal::PolarCoordinates(rotMove);
			vecPole.y = 0.0f;
		}
		if (pKeyboard->GetPress(DIK_W) == true)
		{//前移動
			vecPole -= universal::PolarCoordinates(rotMove);
		}
		if (pKeyboard->GetPress(DIK_S) == true)
		{//後移動
			vecPole += universal::PolarCoordinates(rotMove);
		}

		pInfoCamera->posVDest += vecPole * fMove;

		if (pKeyboard->GetPress(DIK_E) == true)
		{//上昇
			pInfoCamera->posVDest.y += fMove;
		}
		if (pKeyboard->GetPress(DIK_Q) == true)
		{//下降
			pInfoCamera->posVDest.y -= fMove;
		}

		pCamera->SetPosR();
	}

	pCamera->MoveDist(FACT_CORRECT_POS);
}