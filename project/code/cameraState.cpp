//*****************************************************
//
// �J�����X�e�C�g[CameraState.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "CameraState.h"
#include "camera.h"
#include "player.h"
#include "effect3D.h"
#include "inputmouse.h"
#include "inputkeyboard.h"
#include "debugproc.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float MOVE_SPEED = 3.0f;	//�ړ��X�s�[�h
const float ROLL_SPEED = 0.02f;	//��]�X�s�[�h
const float DIST_CAMERA = 400.0f;	// �J�����̋���
const float FACT_CORRECT_POS = 0.2f;	// �ʒu�␳�W��
}

//=====================================================
// �o�����̃J�����̓���
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
// �v���C���[�̒Ǐ]
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

	D3DXVECTOR3 vecPole = universal::PolarCoordinates(pInfoCamera->rot);

	//�ڕW�̎��_�ݒ�
	pInfoCamera->posVDest = pos + vecPole * pInfoCamera->fLength;

	pCamera->MoveDist(FACT_CORRECT_POS);

#ifdef _DEBUG
	CEffect3D::Create(pInfoCamera->posRDest, 20.0f, 1, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	CDebugProc::GetInstance()->Print("\n�J�����̓v���C���[�Ǐ]�ł�");
#endif
}

//=====================================================
// ���삷��
//=====================================================
void CMoveControl::Update(CCamera *pCamera)
{
	if (pCamera == nullptr)
		return;

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();

	// ���͎擾
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse *pMouse = CInputMouse::GetInstance();

	float fMove = MOVE_SPEED;

	//�}�E�X����======================================================
	if (pMouse->GetPress(CInputMouse::BUTTON_RMB) == true)
	{//�E�N���b�N���A���_����
		D3DXVECTOR3 rot;

		//�}�E�X�̈ړ��ʑ��
		rot = { (float)pMouse->GetMoveIX() * ROLL_SPEED, (float)pMouse->GetMoveIY() * ROLL_SPEED, 0.0f };

		D3DXVec3Normalize(&rot, &rot);

		//���_�̐���
		pInfoCamera->rot.y += rot.x * ROLL_SPEED;
		pInfoCamera->rot.x -= rot.y * ROLL_SPEED;

		if (pKeyboard->GetPress(DIK_LSHIFT) == true)
		{//����
			fMove *= 3;
		}

		D3DXVECTOR3 rotMove = pInfoCamera->rot;
		D3DXVECTOR3 vecPole = { 0.0f,0.0f,0.0f };

		//���_�ړ�===============================================
		if (pKeyboard->GetPress(DIK_A) == true)
		{//���ړ�
			rotMove.y += D3DX_PI * 0.5f;

			universal::LimitRot(&rotMove.y);

			vecPole += universal::PolarCoordinates(rotMove);
			vecPole.y = 0.0f;
		}
		if (pKeyboard->GetPress(DIK_D) == true)
		{//�E�ړ�
			rotMove.y -= D3DX_PI * 0.5f;

			universal::LimitRot(&rotMove.y);

			vecPole += universal::PolarCoordinates(rotMove);
			vecPole.y = 0.0f;
		}
		if (pKeyboard->GetPress(DIK_W) == true)
		{//�O�ړ�
			vecPole -= universal::PolarCoordinates(rotMove);
		}
		if (pKeyboard->GetPress(DIK_S) == true)
		{//��ړ�
			vecPole += universal::PolarCoordinates(rotMove);
		}

		pInfoCamera->posVDest += vecPole * fMove;

		if (pKeyboard->GetPress(DIK_E) == true)
		{//�㏸
			pInfoCamera->posVDest.y += fMove;
		}
		if (pKeyboard->GetPress(DIK_Q) == true)
		{//���~
			pInfoCamera->posVDest.y -= fMove;
		}

		pCamera->SetPosR();
	}

	pCamera->MoveDist(FACT_CORRECT_POS);
}