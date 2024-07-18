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
#include "meshRoad.h"
#include "myLib.h"

//*****************************************************
// èè`
//*****************************************************
namespace
{
const float MOVESPEED = 4.0f;	// Ú®¬x
const float WIDTH_GOAL = 100.0f;	// S[Ì
const float NEXT_INTERPOLATE_ROAD = 0.1f;	// ÌÊuÆÝÈ·â³Ìl
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
	m_nIdxSpline = 0;	// XvCÌÔ
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
CEnemySpawner* CEnemySpawner::Create(int nIdxSpline,float fRot, float fLength)
{
	CEnemySpawner *pSpawner = nullptr;

	pSpawner = new CEnemySpawner;

	if (pSpawner != nullptr)
	{
		pSpawner->m_nIdxSpline = nIdxSpline;
		pSpawner->m_fRot = fRot;
		pSpawner->m_fLength = fLength;

		pSpawner->SetPositionSpline();

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
#if 1
	// e[vÌ¶¬
	m_pObj3D = CPolygon3D::Create(m_pos);

	// |SÌÝè
	SetPolygon();
#endif

	return S_OK;
}

//=====================================================
// XvCÉÎµ½ÊuÌÝè
//=====================================================
void CEnemySpawner::SetPositionSpline(void)
{
	// bV[hÌæ¾
	CMeshRoad *pMesh = CMeshRoad::GetInstance();

	if (pMesh == nullptr)
		return;

	// [h|CgÌÊuÌæ¾
	CCutMullSpline spline = *pMesh->GetCenterSpline();

	D3DXVECTOR3 pos;

	pos = spline.Interpolate(0.0f, m_nIdxSpline);

	SetPosition(pos);

	// ñÌxNgÆÌ·ªÅü«ðßé
	D3DXVECTOR3 posNext = spline.Interpolate(NEXT_INTERPOLATE_ROAD, m_nIdxSpline);

	D3DXVECTOR3 vecDiff = posNext - pos;

	float fRot = atan2f(vecDiff.x, vecDiff.z);

	SetRotation(fRot + D3DX_PI * 0.5f);
}

//=====================================================
// |SÌÝè
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
		m_pObj3D->Uninit();
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
			CreateEnemy();

			// ©gÌjü
			Uninit();
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
// GÌ¶¬
//=====================================================
void CEnemySpawner::CreateEnemy(void)
{
	CEnemy *pEnemy = CEnemy::Create();

	if (pEnemy == nullptr)
		return;

	pEnemy->SetIdxSpline(m_nIdxSpline - 1);
}

//=====================================================
// `æ
//=====================================================
void CEnemySpawner::Draw()
{

}