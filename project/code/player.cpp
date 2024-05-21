//*****************************************************
//
// �v���C���[�̏���[player.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
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
// �萔��`
//*****************************************************
namespace
{
const std::string PATH_PARAM = "data\\TEXT\\playerParam.txt";	// �p�����[�^�[�f�[�^�̃p�X
const float NOTROTATE = 1.0f;		// ��]���Ȃ��悤�ɂ���l
const float DIST_LIMIT = 3000.0f;	// ���C���[��������
const float LINE_CORRECT_DRIFT = 40.0f;	// �h���t�g�␳�̂������l
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CPlayer *CPlayer::m_pPlayer = nullptr;	// ���g�̃|�C���^

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CPlayer::CPlayer(int nPriority)
{
	m_pPlayer = this;

	ZeroMemory(&m_info, sizeof(CPlayer::SInfo));
	ZeroMemory(&m_param, sizeof(CPlayer::SParam));
	ZeroMemory(&m_fragMotion, sizeof(CPlayer::SFragMotion));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CPlayer::~CPlayer()
{

}

//=====================================================
// ��������
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
// ����������
//=====================================================
HRESULT CPlayer::Init(void)
{
	// �p���N���X�̏�����
	CMotion::Init();

	SetMotion(MOTION_WALK_FRONT);

	// �J�����̍s���ݒ�
	Camera::ChangeState(new CFollowPlayer);

	// �Ǎ�
	Load();

	// ���f���̐ݒ�
	CMotion::Load(&m_param.aPathBody[0]);

	m_info.pRoap = CObject3D::Create(GetPosition());

	m_info.fLengthDrift = 1500.0f;

	m_info.bGrabOld = true;

	return S_OK;
}

//=====================================================
// �Ǎ�����
//=====================================================
void CPlayer::Load(void)
{
	std::ifstream file(PATH_PARAM);

	if (file.is_open())
	{
		std::string temp;

		while (std::getline(file, temp))
		{// �ǂݍ��ނ��̂��Ȃ��Ȃ�܂œǍ�
			std::istringstream iss(temp);
			std::string key;
			iss >> key;

			if (key == "BODY_PATH")
			{// �����ڂ̃p�X
				iss >> m_param.aPathBody;
			}

			if (key == "SPEED_MAX")
			{// �ő呬�x
				iss >> m_param.fSpeedMax;
			}

			if (key == "FACT_ACCELE")
			{// �����W��
				iss >> m_param.fFactAccele;
			}

			if (key == "FACT_ATTENU")
			{// �����W��
				iss >> m_param.fFactAttenu;
			}

			if (key == "FACT_BRAKE")
			{// �u���[�L�����W��
				iss >> m_param.fFactBrake;
			}

			if (key == "ANGLE_MAX_CURVE")
			{// �J�[�u�ő�p�x
				iss >> m_param.fAngleMaxCurve;
			}

			if (file.eof())
			{// �ǂݍ��ݏI��
				break;
			}
		}
		
		file.close();
	}
	else
	{
		assert(("�����L���O�t�@�C�����J���܂���ł���", false));
	}
}

//=====================================================
// �I������
//=====================================================
void CPlayer::Uninit(void)
{
	m_pPlayer = nullptr;

	// �p���N���X�̏I��
	CMotion::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CPlayer::Update(void)
{
	// ����
	Input();

	// �O��̈ʒu��ۑ�
	D3DXVECTOR3 pos = GetPosition();
	SetPositionOld(pos);

	// ��ԊǗ�
	ManageState();

	// ���[�V�����Ǘ�
	ManageMotion();

	// �p���N���X�̍X�V
	CMotion::Update();

// �f�o�b�O����
#if _DEBUG
	Debug();
#endif // _DEBUG
}

//=====================================================
// ���͏���
//=====================================================
void CPlayer::Input(void)
{
	// �ړ�����
	InputMove();

	// �J��������
	InputCamera();

	InputWire();

	// �X�s�[�h�̊Ǘ�
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
// �ړ��̓���
//=====================================================
void CPlayer::InputMove(void)
{
	CSlow *pSlow = CSlow::GetInstance();
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager == nullptr)
	{
		return;
	}

	// �A�N�Z���l�̎擾
	float fAccele = pInputManager->GetAccele();

	m_info.fSpeedDest = fAccele * m_param.fSpeedMax;

	CDebugProc::GetInstance()->Print("\n�A�N�Z���l[%f]", fAccele);

	if (m_info.pBlock == nullptr)
	{
		// �n���h���̑���
		CInputManager::SAxis axis = pInputManager->GetAxis();
		m_info.fAngleHandle = axis.axisMove.x;
	}

	// �u���[�L�l�̎擾
	float fBrake = pInputManager->GetBrake();

	m_info.fSpeed += (0.0f - m_info.fSpeed) * m_param.fFactBrake * fBrake;

	CDebugProc::GetInstance()->Print("\n�u���[�L�l[%f]", fBrake);
}

//=====================================================
// �J��������
//=====================================================
void CPlayer::InputCamera(void)
{
	// ���̓}�l�[�W���[�擾
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager == nullptr)
	{
		return;
	}

	// �J�����擾
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();
}

//=====================================================
// ���C���[�̑���
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

	// �u���b�N�̃`�F�b�N
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
		{// ���삵�Ă��锻��
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
				{// �e�����u��
					m_info.fTimerFlip = 0.8f;

					m_info.nCntFlip++;

					float fDiffInput = fAngle - fAngleDiff;

					if(fDiffInput * fDiffInput < D3DX_PI * 0.4f * D3DX_PI * 0.4f)
						m_info.fLengthDrift = 25.0f;
				}
				else
				{
					if (m_info.fTimerFlip > 0.0f)
					{// �e���^�C�}�[���Z
						m_info.fTimerFlip -= CManager::GetDeltaTime();
					}
					else
					{// �P�\���Ԃ��߂���ƒe���J�E���^�[���Z�b�g
						//if (fLength <= 0.5f)
						{// �����͂�ł��Ȃ���΃��Z�b�g
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

					// �J�������[��
					Camera::ControlRoll(0.3f, 0.04f);
				}
				else
				{
					rotDest.y = fAngleDiff - D3DX_PI * 0.5f;

					// �J�������[��
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

				// �h���t�g�̕␳
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

				//���_���̃|�C���^
				VERTEX_3D *pVtx;

				//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//���_���W�̐ݒ�
				float fHeight = 100.0f;

				D3DXVECTOR3 vec = { vecDiff.z, 0.0f, -vecDiff.x };

				D3DXVec3Normalize(&vec, &vec);

				pVtx[0].pos = D3DXVECTOR3(posBlock.x - vec.x * 20.0f, fHeight, posBlock.z);
				pVtx[1].pos = D3DXVECTOR3(posBlock.x + vec.x * 20.0f, fHeight, posBlock.z);
				pVtx[2].pos = D3DXVECTOR3(posPlayer.x - vec.x * 20.0f, fHeight, posPlayer.z);
				pVtx[3].pos = D3DXVECTOR3(posPlayer.x + vec.x * 20.0f, fHeight, posPlayer.z);

				//���_�o�b�t�@���A�����b�N
				pVtxBuff->Unlock();
			}

		}
	}
	else
	{
		// �J�����̃��[���l���܂������ɖ߂�
		Camera::ControlRoll(0.0f, 0.1f);

		//if (m_info.nCntFlip == 0)
		{
			while (pBlock != nullptr)
			{
				// ���̃A�h���X��ۑ�
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

				// ���̃A�h���X����
				pBlock = pBlockNext;
			}

			if (pBlockGrab != nullptr)
			{
				if (pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_DOWN, 0) ||
					pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_LEFT, 0) ||
					pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_UP, 0) ||
					pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION::DIRECTION_RIGHT, 0))
				{// �e�����u��
					m_info.pBlock = pBlockGrab;

					m_info.fTimerDriftChange = 0.7f;
				}
			}
		}
	}

	CDebugProc::GetInstance()->Print("\n�͂�ł�u���b�N�͂���H[%d]", m_info.pBlock != nullptr);
	CDebugProc::GetInstance()->Print("\n���b�N�I������[%f]", fAngle);
}

//=====================================================
// �h���t�g�̕␳
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
// �X�s�[�h�̊Ǘ�
//=====================================================
void CPlayer::ManageSpeed(void)
{
	CSlow* pSlow = CSlow::GetInstance();

	// �X�s�[�h�̑���
	if (m_info.fSpeedDest >= m_info.fSpeed)
	{// �������Ă���Ƃ�
		m_info.fSpeed += (m_info.fSpeedDest - m_info.fSpeed) * m_param.fFactAccele;

		CDebugProc::GetInstance()->Print("\n������");
	}
	else
	{// �������Ă���Ƃ�
		m_info.fSpeed += (m_info.fSpeedDest - m_info.fSpeed) * m_param.fFactAttenu;

		CDebugProc::GetInstance()->Print("\n������");
	}

	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRotation();

	// �X���[��Ԃ��l�������ړ��ʂ̒���
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
	{// �n���h���̉�]��ǉ�
		rot.y += m_info.fAngleHandle * m_param.fAngleMaxCurve;
		universal::LimitRot(&rot.y);
	}

	SetRotation(rot);

	// �ɍ��W����������Ă��镪��␳
	rot.x += D3DX_PI * 0.5f;

	D3DXVECTOR3 vecForward = universal::PolarCoordinates(rot);

	// ���݂̃X�s�[�h�ƑO���x�N�g���������Ĉړ��ʂɓK�p
	move = vecForward * m_info.fSpeed;

	SetMove(move);
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CPlayer::ManageState(void)
{
	switch (m_info.state)
	{
	case STATE_NORMAL:
	{// �ʏ���

	}
	default:
		break;
	}
}

//=====================================================
// ���[�V�����Ǘ�
//=====================================================
void CPlayer::ManageMotion(void)
{
	int nMotion = GetMotion();
	bool bFinish = IsFinish();

	if (m_fragMotion.bMove)
	{// �������[�V����
		if (nMotion != MOTION_WALK_FRONT)
		{
			SetMotion(MOTION_WALK_FRONT);
		}
	}
	else
	{// �ҋ@���[�V����
		if (nMotion != MOTION_NEUTRAL)
		{
			SetMotion(MOTION_NEUTRAL);
		}
	}
}

//=====================================================
// �C�x���g�̊Ǘ�
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
// �`�揈��
//=====================================================
void CPlayer::Draw(void)
{
	// �p���N���X�̕`��
	CMotion::Draw();
}

//=====================================================
// �q�b�g����
//=====================================================
void CPlayer::Hit(float fDamage)
{

}

//=====================================================
// �f�o�b�O�\��
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

	pDebugProc->Print("\n�v���C���[�̈ʒu[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	pDebugProc->Print("\n�v���C���[�̈ړ���[%f,%f,%f]", GetMove().x, GetMove().y, GetMove().z);
	pDebugProc->Print("\n�v���C���[�̌���[%f,%f,%f]", GetRotation().x, GetRotation().y, GetRotation().z);
	pDebugProc->Print("\n�ڕW���x[%f]", m_info.fSpeedDest);
	pDebugProc->Print("\n���݂̑��x[%f]", m_info.fSpeed);
	pDebugProc->Print("\n�e���J�E���^�[[%d]", m_info.nCntFlip);
	pDebugProc->Print("\n�p�x�J�E���^�[[%f]", m_info.fCntAngle);
}