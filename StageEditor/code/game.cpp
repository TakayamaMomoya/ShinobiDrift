//*****************************************************
//
// Q[[game.cpp]
// Author:ûüRç
//
//*****************************************************

//*****************************************************
// CN[h
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
// }Nè`
//*****************************************************
#define TRANS_TIME	(60)	// I¹ÜÅÌ]CÌt[

//*****************************************************
// ÃIoÏé¾
//*****************************************************
CGame::STATE CGame::m_state = STATE_NONE;	// óÔ
CGame *CGame::m_pGame = nullptr;	// ©gÌ|C^

//=====================================================
// RXgN^
//=====================================================
CGame::CGame()
{
	m_nCntState = 0;
	m_bStop = false;
	m_bBlock = false;
	m_pEdit = nullptr;
}

//=====================================================
// ú»
//=====================================================
HRESULT CGame::Init(void)
{
	m_pGame = this;

	m_state = STATE_NORMAL;
	m_bStop = true;

	// UI}l[W[ÌÇÁ
	CUIManager::Create();

	// XJC{bNXÌ¶¬
	CSkybox::Create();

	// RDAj[VÇÌ¶¬
	CAnimEffect3D::Create();

	// TEhCX^XÌæ¾
	CSound* pSound = CSound::GetInstance();

	// ubNÇÌ¶¬
	CBlockManager::Create();
	
	// tHOð©¯é
	CRenderer *pRenderer = CRenderer::GetInstance();

	// X[ÇÌ¶¬
	CSlow::Create();

	// bV[hÌ¶¬
	CMeshRoad::Create();

	m_pEdit = new CEditMesh;
	m_pEdit->Init();

	// vC[ÌTCYmFpÌf¶¬
	CMotion::Create("data\\MOTION\\motionBike.txt");

	return S_OK;
}

//=====================================================
// I¹
//=====================================================
void CGame::Uninit(void)
{
	m_pEdit->Uninit();

	// IuWFNgSü
	CObject::ReleaseAll();

	m_pGame = nullptr;
}

//=====================================================
// XV
//=====================================================
void CGame::Update(void)
{
	CFade *pFade = CFade::GetInstance();
	CInputManager *pInputManager = CInputManager::GetInstance();
	CSound* pSound = CSound::GetInstance();

	m_pEdit->Update();

	// V[ÌXV
	CScene::Update();

	if (m_bStop == false)
	{
		// J[\ðSÉÅè
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
		// â~µÈ¢IuWFNgÌXV
		CObject::UpdateNotStop();

		CPause *pPause = CPause::GetInstance();

		if (pPause != nullptr)
		{
			pPause->Update();
		}
	}

	// JXV
	UpdateCamera();

	// óÔÇ
	ManageState();

	ImGui::Text("[EditMode]");

	if (ImGui::Button("Mesh", ImVec2(70, 30)))	// bVGfBbg
		ChangeEdit(new CEditMesh);

	if (ImGui::Button("Block", ImVec2(70, 30)))	// ubNGfBbg
		ChangeEdit(new CEditBlock);

#ifdef _DEBUG
	Debug();
#endif
}

//=====================================================
// JÌXV
//=====================================================
void CGame::UpdateCamera(void)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	// ì
	pCamera->Control();
}

//=====================================================
// óÔÇ
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
// GfB^[ÌÏX
//=====================================================
void CGame::ChangeEdit(CEdit *pEdit)
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
// CxgJÌÝè
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
// fobO
//=====================================================
void CGame::Debug(void)
{
	// üÍæ¾
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard == nullptr)
	{
		return;
	}
}

//=====================================================
// `æ
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

	pDebugProc->Print("\nQ[ÌóÔ[%s]\n", apString[m_state]);
}