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

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float DIST_CYLINDER = 1000.0f;
const float DIST_LOOK = 1500.0f;
const float MOVE_SPEED = 3.0f;						//移動スピード
const float ROLL_SPEED = 0.02f;						//回転スピード
const float DIST_CAMERA = 400.0f;	// カメラの距離
}

//=====================================================
// 出現時のカメラの動き
//=====================================================
void CApperPlayer::Update(CCamera *pCamera)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;

	D3DXVECTOR3 posPlayer = pPlayer->GetMtxPos(1);

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();

	pInfoCamera->posRDest = posPlayer;

	pInfoCamera->posV = posPlayer;
	pInfoCamera->posV.y = 10.0f;
	pInfoCamera->posV.x += 100.0f;
}

//=====================================================
// プレイヤーの追従
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

	D3DXVECTOR3 pos = pPlayer->GetMtxPos(2);

	pInfoCamera->posRDest = pos;

	//目標の視点設定
	pInfoCamera->posVDest =
	{
		pInfoCamera->posRDest.x,
		pInfoCamera->posRDest.y + DIST_CAMERA,
		pInfoCamera->posRDest.z - DIST_CAMERA
	};

#ifdef _DEBUG
	CEffect3D::Create(pInfoCamera->posRDest, 20.0f, 1, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	CDebugProc::GetInstance()->Print("\nカメラはプレイヤー追従です");
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

		//注視点を相対位置に設定
		pCamera->SetPosR();

		if (pKeyboard->GetPress(DIK_LSHIFT) == true)
		{//加速
			fMove *= 3;
		}

		//視点移動===============================================
		if (pKeyboard->GetPress(DIK_A) == true)
		{//左移動
			pInfoCamera->posVDest.x += sinf(pInfoCamera->rot.y - D3DX_PI * 0.5f) * fMove;
			pInfoCamera->posVDest.z += cosf(pInfoCamera->rot.y - D3DX_PI * 0.5f) * fMove;
			pCamera->SetPosR();
		}
		if (pKeyboard->GetPress(DIK_D) == true)
		{//右移動
			pInfoCamera->posVDest.x += sinf(pInfoCamera->rot.y - D3DX_PI * -0.5f) * fMove;
			pInfoCamera->posVDest.z += cosf(pInfoCamera->rot.y - D3DX_PI * -0.5f) * fMove;
			pCamera->SetPosR();
		}
		if (pKeyboard->GetPress(DIK_W) == true)
		{//前移動
			pInfoCamera->posVDest.x -= sinf(pInfoCamera->rot.x + D3DX_PI) * sinf(pInfoCamera->rot.y) * fMove;
			pInfoCamera->posVDest.y += cosf(pInfoCamera->rot.x + D3DX_PI) * MOVE_SPEED;
			pInfoCamera->posVDest.z -= sinf(pInfoCamera->rot.x + D3DX_PI) * cosf(pInfoCamera->rot.y) * fMove;
			pCamera->SetPosR();
		}
		if (pKeyboard->GetPress(DIK_S) == true)
		{//後移動
			pInfoCamera->posVDest.x -= sinf(pInfoCamera->rot.x) * sinf(pInfoCamera->rot.y) * fMove;
			pInfoCamera->posVDest.y += cosf(pInfoCamera->rot.x) * MOVE_SPEED;
			pInfoCamera->posVDest.z -= sinf(pInfoCamera->rot.x) * cosf(pInfoCamera->rot.y) * fMove;
			pCamera->SetPosR();
		}
		if (pKeyboard->GetPress(DIK_E) == true)
		{//上昇
			pInfoCamera->posVDest.y += fMove;
			pCamera->SetPosR();
		}
		if (pKeyboard->GetPress(DIK_Q) == true)
		{//下降
			pInfoCamera->posVDest.y -= fMove;
			pCamera->SetPosR();
		}
	}
}