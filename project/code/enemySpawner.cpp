//*****************************************************
//
// GX|i[[enemySpawner.cpp]
// Author:ûüRç
//
//*****************************************************

//*****************************************************
// CN[h
//*****************************************************
#include "enemySpawner.h"
#include "player.h"
#include "effect3D.h"
#include "enemy.h"

//*****************************************************
// èè`
//*****************************************************
namespace
{
	const float MOVESPEED = 4.0f;	// Ú®¬x
	const float WIDTH_GOAL = 100.0f;	// S[Ì
}

//=====================================================
// RXgN^
//=====================================================
CEnemySpawner::CEnemySpawner(int nPriority)
{
	m_nTransitionTime = 0;		// JÚJE^[
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// Êu
	m_posStart = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// S[Ìn_
	m_posEnd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// S[ÌI_
	m_fRot = 0.0f;		// ü«
	m_pObj3D = nullptr;		// IuWFNg3DÌ|C^
}

//=====================================================
// fXgN^
//=====================================================
CEnemySpawner::~CEnemySpawner()
{
}

//=====================================================
// ¶¬
//=====================================================
CEnemySpawner* CEnemySpawner::Create(D3DXVECTOR3 pos,float fRot, float fLength)
{
	CEnemySpawner *pSpawner = nullptr;

	pSpawner = new CEnemySpawner;

	if (pSpawner != nullptr)
	{
		pSpawner->m_pos = pos;
		pSpawner->m_fRot = fRot;
		pSpawner->m_fLength = fLength;

		// ú»
		pSpawner->Init();
	}

	return pSpawner;
}

//=====================================================
// ú»
//=====================================================
HRESULT CEnemySpawner::Init()
{
	// e[vÌ¶¬
	m_pObj3D = CPolygon3D::Create(m_pos);

	// |SÌÝè
	SetPolygon();

	return S_OK;
}

//=====================================================
// S[ÌÝè
//=====================================================
void CEnemySpawner::SetPolygon(void)
{
	// n_EI_ÌvZ
	D3DXVECTOR3 vec = { sinf(m_fRot) * m_fLength ,0.0f,cosf(m_fRot) * m_fLength };

	m_posStart = m_pos + vec;
	m_posEnd = m_pos - vec;

	if (m_pObj3D != nullptr)
	{
		// FÝè
		m_pObj3D->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f));

		// TCYÝè
		m_pObj3D->SetSize(WIDTH_GOAL, m_fLength);

		m_pObj3D->SetRotation(D3DXVECTOR3(0.0f, m_fRot, 0.0f));
		m_pObj3D->SetPosition(m_pos);
	}
}

//=====================================================
// I¹
//=====================================================
void CEnemySpawner::Uninit()
{
	if (m_pObj3D != nullptr)
	{
		m_pObj3D = nullptr;
	}

	// ©gÌí
	Release();
}

//=====================================================
// XV
//=====================================================
void CEnemySpawner::Update()
{
	// vC[îñæ¾
	CPlayer* pPlayer = CPlayer::GetInstance();

	// Êuæ¾
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// Ú®Êæ¾
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();

	// ð_Ì
	float fCross = 0.0f;

	// OÏÌ»è
	if (universal::IsCross(posPlayer,		// vC[ÌÊu
		m_posStart,		// S[Ìn_
		m_posEnd,			// S[ÌI_
		&fCross,		// ð_Ì
		posPlayer + movePlayer))	// vC[ÌÚ®Ê
	{
		if (fCross >= 0.0f && fCross <= 1.0f)
		{// n_ÆI_ÌÔðÊÁ½
			// GÌ¶¬
			

			// ©gÌjü
			//Uninit();
		}
	}

#ifdef _DEBUG
	CEffect3D::Create(m_posStart, 200.0f, 3, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	CEffect3D::Create(m_posEnd, 200.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
#endif

#if 0
	CDebugProc::GetInstance()->Print("\nfCrossÌl[%f]", fCross);
	CDebugProc::GetInstance()->Print("\nstartPosÌÊu[%f, %f, %f]", m_posStart.x, m_posStart.y, m_posStart.z);
	CDebugProc::GetInstance()->Print("\nendPosÌÊu[%f, %f, %f]", m_posEnd.x, m_posEnd.y, m_posEnd.z);
#endif
}

//=====================================================
// `æ
//=====================================================
void CEnemySpawner::Draw()
{

}