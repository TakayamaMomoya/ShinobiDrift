//*****************************************************
//
// 首都高を走る車の処理[car.cpp]
// Author:大原怜将
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "enemy.h"
#include "myLib.h"
#include "debugproc.h"
#include "player.h"
#include "effect3D.h"

//*****************************************************
// 静的メンバ変数
//*****************************************************
CEnemy* CEnemy::m_pEnemy = nullptr;

//=====================================================
// コンストラクタ
//=====================================================
CEnemy::CEnemy(int nPriority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CEnemy::~CEnemy()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEnemy::Init(void)
{
	// 継承クラスの初期化
	CMotion::Init();

	// モデルの設定
	CMotion::Load("data\\MOTION\\motionPlayer.txt");

	// データ点のベクター用意
	std::vector<D3DXVECTOR3> vPos;
	D3DXVECTOR3 Pos[3] = {};

	CPlayer* pPlayer = CPlayer::GetInstance();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();
	
	Pos[0] = { 0.0f, PlayerPos.y, 0.0f };
	Pos[1] = { 1000.0f, PlayerPos.y, 1000.0f };
	Pos[2] = { 2000.0f, PlayerPos.y, 1500.0f };

	//m_aRoadPoint.clear();

	//m_aRoadPoint.begin();

	// ベクターを必要なサイズに調整
	int nSize = 3;
	vPos.resize(nSize);

	for (int i = 0; i < nSize; i++)
	{
		vPos[i] = Pos[i];
	}

	m_pSpline = new CCutMullSpline;

	// 中心スプラインの初期化
	m_pSpline->Init(vPos);

	SetPosition(pPlayer->GetPosition());

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEnemy::Uninit(void)
{
	// 継承クラスの終了
	CMotion::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEnemy::Update(void)
{
	// 継承クラスの更新
	CMotion::Update();

	D3DXVECTOR3 pos = {};
	pos = m_pSpline->Interpolate(m_t, m_nIdx);

	m_t += 0.01f;

	if (m_t >= 1.0f)
	{
		m_t = 0.0f;

		m_nIdx++;
	}

	if (m_nIdx >= 3)
		m_nIdx = 1;

	CEffect3D::Create(pos, 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\n車の位置[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
}

//=====================================================
// 描画処理
//=====================================================
void CEnemy::Draw(void)
{
	// 継承クラスの描画
	CMotion::Draw();
}

//=====================================================
// 生成処理
//=====================================================
CEnemy* CEnemy::Create()
{
	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{
		pEnemy = new CEnemy;

		if (pEnemy != nullptr)
		{
			m_pEnemy = pEnemy;

			// 初期化
			pEnemy->Init();
		}
	}

	return pEnemy;
}
