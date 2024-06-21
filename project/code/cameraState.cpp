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
#include "block.h"
#include "manager.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float MOVE_SPEED = 3.0f;	//�ړ��X�s�[�h
const float ROLL_SPEED = 0.02f;	//��]�X�s�[�h
const float FACT_CORRECT_POS = 0.2f;	// �ʒu�␳�W��
const float LENGTH_FOLLOW = 412.0f;	// �Ǐ]���̃J��������
const float ANGLE_FOLLOW = 0.73f;	// �Ǐ]���̃J�����p�x
const float LENGTHPOSR_FOLLOW = 4126.0f;	// �Ǐ]���̐�����鋗��
const float FOV_FOLLOW = 93.0f;	// �Ǐ]���̎���p
}

//***********************************************************************************
// �v���C���[�̒Ǐ]
//***********************************************************************************
//=====================================================
// �R���X�g���N�^
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
// �X�V
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

	// �����_�̐ݒ�
	CBlock *pBlock = pPlayer->GetBlock();

	if (pBlock != nullptr)
	{// �u���b�N��͂�ł���ꍇ�A���ԂɎ��_��������
		D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
		D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();
		D3DXVECTOR3 posBlock = pBlock->GetPosition();
		D3DXVECTOR3 vecDiff = posBlock - posPlayer;
		
		// ���_�̐ݒ�
		float fAngleDiff = atan2f(vecDiff.x, vecDiff.z);
		float fDiff = rotPlayer.y - fAngleDiff;
		universal::LimitRot(&fDiff);

		universal::FactingRot(&pInfoCamera->rot.y, fAngleDiff + D3DX_PI, 0.04f);

		D3DXVECTOR3 vecPole = universal::PolarCoordinates(pInfoCamera->rot);

#ifdef _DEBUG
		CEffect3D::Create(pPlayer->GetMtxPos(2) + vecPole * 500.0f, 20.0f, 3, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
#endif
		// �Ǐ]���̎��_���烉�[�v(���_)
		D3DXVECTOR3 vecPoleOld = universal::PolarCoordinates(m_rotROld);
		D3DXVECTOR3 posOld = pPlayer->GetMtxPos(2) + vecPoleOld * pInfoCamera->fLength;
		D3DXVECTOR3 posDest = pPlayer->GetMtxPos(2) + vecPole * pInfoCamera->fLength;

		m_fTimerPosR += CManager::GetDeltaTime();

		float fTime = m_fTimerPosR / 1.0f;
		universal::LimitValue(&fTime, 1.0f, 0.0f);

		pInfoCamera->posVDest = pos + vecPole * pInfoCamera->fLength;

		// �����_�̐ݒ�
		D3DXVECTOR3 posOldR = pPlayer->GetMtxPos(2);
		D3DXVECTOR3 posDestR = posPlayer + vecDiff * 0.3f;
		pInfoCamera->posRDest = universal::Lerp(posOldR, posDestR, fTime);

		// �ڕW�ʒu�ɕ␳
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

		pInfoCamera->posRDest.y += 50.0f;	// ��U�ނ��肿����ƍ�������

		// �ڕW�̎��_�ݒ�
		D3DXVECTOR3 vecPole = universal::PolarCoordinates(pInfoCamera->rot);
		pInfoCamera->posVDest = pos + vecPole * pInfoCamera->fLength;

		pCamera->MoveDist(FACT_CORRECT_POS);

		m_rotROld = pInfoCamera->rot;
	}

#ifdef _DEBUG
	CEffect3D::Create(pInfoCamera->posRDest, 20.0f, 1, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	CDebugProc::GetInstance()->Print("\n�J�����̓v���C���[�Ǐ]�ł�");

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

		CDebugProc::GetInstance()->Print("\n[�����J�����l]");
		CDebugProc::GetInstance()->Print("\n����p[%f]", pInfoCamera->fViewAngle);
		CDebugProc::GetInstance()->Print("\n�J��������[%f]", pInfoCamera->fLength);
		CDebugProc::GetInstance()->Print("\n�p�x[%f]", pInfoCamera->rot.x);
		CDebugProc::GetInstance()->Print("\n������鋗��[%f]", m_fLengthPosR);
		CDebugProc::GetInstance()->Print("\n[�����J�����l]");
	}
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