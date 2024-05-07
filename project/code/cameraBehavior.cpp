//*****************************************************
//
// �J�����r�w�C�r�A[cameraBehavior.h]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "cameraBehavior.h"
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
const float DIST_CYLINDER = 1000.0f;
const float DIST_LOOK = 1500.0f;
const float MOVE_SPEED = 3.0f;						//�ړ��X�s�[�h
const float ROLL_SPEED = 0.02f;						//��]�X�s�[�h
const float DIST_CAMERA = 400.0f;	// �J�����̋���
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

	//�ڕW�̎��_�ݒ�
	pInfoCamera->posVDest =
	{
		pInfoCamera->posRDest.x,
		pInfoCamera->posRDest.y + DIST_CAMERA,
		pInfoCamera->posRDest.z - DIST_CAMERA
	};

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

		//�����_�𑊑Έʒu�ɐݒ�
		pCamera->SetPosR();

		if (pKeyboard->GetPress(DIK_LSHIFT) == true)
		{//����
			fMove *= 3;
		}

		//���_�ړ�===============================================
		if (pKeyboard->GetPress(DIK_A) == true)
		{//���ړ�
			pInfoCamera->posVDest.x += sinf(pInfoCamera->rot.y - D3DX_PI * 0.5f) * fMove;
			pInfoCamera->posVDest.z += cosf(pInfoCamera->rot.y - D3DX_PI * 0.5f) * fMove;
			pCamera->SetPosR();
		}
		if (pKeyboard->GetPress(DIK_D) == true)
		{//�E�ړ�
			pInfoCamera->posVDest.x += sinf(pInfoCamera->rot.y - D3DX_PI * -0.5f) * fMove;
			pInfoCamera->posVDest.z += cosf(pInfoCamera->rot.y - D3DX_PI * -0.5f) * fMove;
			pCamera->SetPosR();
		}
		if (pKeyboard->GetPress(DIK_W) == true)
		{//�O�ړ�
			pInfoCamera->posVDest.x -= sinf(pInfoCamera->rot.x + D3DX_PI) * sinf(pInfoCamera->rot.y) * fMove;
			pInfoCamera->posVDest.y += cosf(pInfoCamera->rot.x + D3DX_PI) * MOVE_SPEED;
			pInfoCamera->posVDest.z -= sinf(pInfoCamera->rot.x + D3DX_PI) * cosf(pInfoCamera->rot.y) * fMove;
			pCamera->SetPosR();
		}
		if (pKeyboard->GetPress(DIK_S) == true)
		{//��ړ�
			pInfoCamera->posVDest.x -= sinf(pInfoCamera->rot.x) * sinf(pInfoCamera->rot.y) * fMove;
			pInfoCamera->posVDest.y += cosf(pInfoCamera->rot.x) * MOVE_SPEED;
			pInfoCamera->posVDest.z -= sinf(pInfoCamera->rot.x) * cosf(pInfoCamera->rot.y) * fMove;
			pCamera->SetPosR();
		}
		if (pKeyboard->GetPress(DIK_E) == true)
		{//�㏸
			pInfoCamera->posVDest.y += fMove;
			pCamera->SetPosR();
		}
		if (pKeyboard->GetPress(DIK_Q) == true)
		{//���~
			pInfoCamera->posVDest.y -= fMove;
			pCamera->SetPosR();
		}
	}
}