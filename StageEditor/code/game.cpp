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
	m_pEdit = nullptr;
	m_fHoge = 0.0f;
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

	// °Ì¶¬
	//CObject3D *pObjectOut = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//if (pObjectOut != nullptr)
	//{
	//	int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\BG\\field00.jpg");
	//	pObjectOut->SetPosition(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	//	pObjectOut->SetIdxTexture(nIdx);
	//	pObjectOut->SetTex(D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(0.0f, 0.0f));
	//	pObjectOut->SetSize(50000.0f, 50000.0f);
	//}

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

	// XvCâÔÌeXg
	CSpline *pSpline = nullptr;
	pSpline = new CSpline;

	if (pSpline != nullptr)
	{
		// f[^_ÌpÓ
		std::vector<double> x = { 0.0,200.0,500.0,700.0 ,900.0};
		std::vector<double> y = { 0.0,100.0,0.0,100.0,200.0 };

		// WÌvZ
		pSpline->Init(x, y);

		int nSize = x.size();

		// f[^_ÌÊuÉGtFNgðo·
		std::vector<double>::iterator itX = x.begin();
		std::vector<double>::iterator itY = y.begin();
		for (int i = 0; i < nSize; i++)
		{
			D3DXVECTOR3 pos = { (float)*itX, (float)*itY, 0.0f };

			CEffect3D::Create(pos, 20.0f, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			itX++;
			itY++;
		}

		if (CInputKeyboard::GetInstance()->GetPress(DIK_M))
			m_fHoge += 1.0f;
		if (CInputKeyboard::GetInstance()->GetPress(DIK_N))
			m_fHoge -= 1.0f;

		CDebugProc::GetInstance()->Print("\nzQ[%f]", m_fHoge);

		float fHeight = pSpline->Interpolate(m_fHoge);
		CEffect3D::Create(D3DXVECTOR3(m_fHoge,fHeight,0.0f), 20.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

	delete pSpline;
	pSpline = nullptr;
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