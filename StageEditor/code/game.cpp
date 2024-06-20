//*****************************************************
//
// �Q�[������[game.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "manager.h"
#include "game.h"
#include "object.h"
#include "inputkeyboard.h"
#include "inputManager.h"
#include "fade.h"
#include "camera.h"
#include "sound.h"
#include "scene.h"
#include "debugproc.h"
#include <stdio.h>
#include "UIManager.h"
#include "object3D.h"
#include "texture.h"
#include "skybox.h"
#include "editBlock.h"
#include "block.h"
#include "renderer.h"
#include "animEffect3D.h"
#include "pause.h"
#include "slow.h"
#include "blockManager.h"
#include "meshRoad.h"
#include "editMesh.h"
#include "effect3D.h"
#include "myLib.h"
#include "motion.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define TRANS_TIME	(60)	// �I���܂ł̗]�C�̃t���[����

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CGame::STATE CGame::m_state = STATE_NONE;	// ���
CGame *CGame::m_pGame = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CGame::CGame()
{
	m_nCntState = 0;
	m_bStop = false;
	m_bBlock = false;
	m_pEdit = nullptr;
}

//=====================================================
// ����������
//=====================================================
HRESULT CGame::Init(void)
{
	m_pGame = this;

	m_state = STATE_NORMAL;
	m_bStop = true;

	// UI�}�l�[�W���[�̒ǉ�
	CUIManager::Create();

	// �X�J�C�{�b�N�X�̐���
	CSkybox::Create();

	// �RD�A�j���[�V�����Ǘ��̐���
	CAnimEffect3D::Create();

	// �T�E���h�C���X�^���X�̎擾
	CSound* pSound = CSound::GetInstance();

	// �u���b�N�Ǘ��̐���
	CBlockManager::Create();
	
	// �t�H�O��������
	CRenderer *pRenderer = CRenderer::GetInstance();

	// �X���[�Ǘ��̐���
	CSlow::Create();

	// ���b�V�����[�h�̐���
	CMeshRoad::Create();

	m_pEdit = new CEditMesh;
	m_pEdit->Init();

	// �v���C���[�̃T�C�Y�m�F�p�̃��f������
	CMotion::Create("data\\MOTION\\motionBike.txt");

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CGame::Uninit(void)
{
	m_pEdit->Uninit();

	// �I�u�W�F�N�g�S��
	CObject::ReleaseAll();

	m_pGame = nullptr;
}

//=====================================================
// �X�V����
//=====================================================
void CGame::Update(void)
{
	CFade *pFade = CFade::GetInstance();
	CInputManager *pInputManager = CInputManager::GetInstance();
	CSound* pSound = CSound::GetInstance();

	m_pEdit->Update();

	// �V�[���̍X�V
	CScene::Update();

	if (m_bStop == false)
	{
		// �J�[�\���𒆐S�ɌŒ�
		SetCursorPos((int)(SCREEN_WIDTH * 0.5f), (int)(SCREEN_HEIGHT * 0.5f));

		if (pInputManager != nullptr)
		{
			if (pInputManager->GetTrigger(CInputManager::BUTTON_PAUSE))
			{
				CPause::Create();
			}
		}
	}
	else
	{
		// ��~���Ȃ��I�u�W�F�N�g�̍X�V
		CObject::UpdateNotStop();

		CPause *pPause = CPause::GetInstance();

		if (pPause != nullptr)
		{
			pPause->Update();
		}
	}

	// �J�����X�V
	UpdateCamera();

	// ��ԊǗ�
	ManageState();

	if (ImGui::Button("CreateEdge", ImVec2(70, 30)))	// ���b�V������
		//ChangeState(new CStateEditMeshCreateMesh);

	if (CInputKeyboard::GetInstance()->GetTrigger(DIK_G))
	{
		if (m_pEdit != nullptr)
		{
			m_pEdit->Uninit();
			delete m_pEdit;
			m_pEdit = nullptr;
		}

		if (m_bBlock)
		{
			m_pEdit = new CEditMesh;

			m_bBlock = false;
		}
		else
		{
			m_pEdit = new CEditBlock;

			m_bBlock = true;
		}

		if (m_pEdit != nullptr)
			m_pEdit->Init();
	}

#ifdef _DEBUG
	Debug();
#endif
}

//=====================================================
// �J�����̍X�V
//=====================================================
void CGame::UpdateCamera(void)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	// ����
	pCamera->Control();
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CGame::ManageState(void)
{
	CFade *pFade = CFade::GetInstance();

	switch (m_state)
	{
	case CGame::STATE_NORMAL:
		break;

		break;
	case CGame::STATE_END:

		m_nCntState++;

		if (m_nCntState >= TRANS_TIME && pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_RANKING);
		}

		break;
	default:
		break;
	}
}

//=====================================================
// �G�f�B�^�[�̕ύX
//=====================================================
void CGame::ChangeEditer(CEdit *pEdit)
{
	if (m_pEdit != nullptr)
	{
		m_pEdit->Uninit();
		delete m_pEdit;
		m_pEdit = nullptr;
	}

	m_pEdit = pEdit;

	if (m_pEdit != nullptr)
	{
		m_pEdit->Init();
	}
}

//=====================================================
// �C�x���g�J�����̐ݒ�
//=====================================================
void CGame::SetEventCamera(float fTime, D3DXVECTOR3 posRDest, D3DXVECTOR3 posVDest)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->SetEventTimer(fTime);
		pCamera->SetPosRDest(posRDest);
		pCamera->SetPosVDest(posVDest);

		EnableStop(true);
	}
}

//=====================================================
// �f�o�b�O����
//=====================================================
void CGame::Debug(void)
{
	// ���͎擾
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard == nullptr)
	{
		return;
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CGame::Draw(void)
{
#ifndef _DEBUG
	return;
#endif

	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	char *apString[STATE::STATE_MAX] =
	{
		"NONE",
		"NORMAL",
		"END",
	};

	pDebugProc->Print("\n�Q�[���̏��[%s]\n", apString[m_state]);
}