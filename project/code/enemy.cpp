//*****************************************************
//
// エネミーの処理[enemy.cpp]
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
#include "meshRoad.h"
#include "universal.h"

//*****************************************************
// 静的メンバ変数
//*****************************************************
CEnemy* CEnemy::m_pEnemy = nullptr;

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const float SPEED = 0.004f;
}

//=====================================================
// コンストラクタ
//=====================================================
CEnemy::CEnemy(int nPriority)
{
	m_pEnemyNinja = nullptr;
	m_nIdx = 1;
	m_nSize = 0;
	m_Info.fSpeed = 0.0f;
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
	CMotion::Load("data\\MOTION\\motionEnemy.txt");

	// スプラインの情報を取得
	m_pSpline = CMeshRoad::GetInstance()->GetCenterSpline();

	// ロードポイントの情報を取得
	std::vector<CMeshRoad::SInfoRoadPoint> pRoadPoint = *CMeshRoad::GetInstance()->GetArrayRP();

	// ベクターを必要なサイズに調整
	m_nSize = pRoadPoint.size();
	m_vPos.resize(m_nSize);

	for (int i = 0; i < m_nSize; i++)
	{
		m_vPos[i] = pRoadPoint[i].pos;
	}

	// 中心スプラインの初期化
	if(m_pSpline != nullptr)
	   m_pSpline->Init(m_vPos);

	SetPosition(D3DXVECTOR3(pRoadPoint[0].pos.x, pRoadPoint[0].pos.y, pRoadPoint[0].pos.z));

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEnemy::Uninit(void)
{
	m_pEnemy = nullptr;

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

	D3DXVECTOR3 pos = { 0.0f, 0.0f, 0.0f };

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// 位置補間
	if(m_pSpline != nullptr)
	   pos = m_pSpline->Interpolate(m_Info.fSpeed, m_nIdx);

	m_Info.fSpeed += SPEED;

	if (m_Info.fSpeed >= 1.0f)
	{
		m_Info.fSpeed = 0.0f;

		m_nIdx++;
	}

	// サイズを超えたら戻す
	if (m_nIdx >= m_nSize)
		m_nIdx = 1;
		
	// 次のポイントに向かせる
	universal::FactingRotTarget(&rot, pos, m_vPos[m_nIdx], 0.05f);

	// 位置と向き更新
	SetPosition(pos);
	SetRotation(D3DXVECTOR3(0.0f, rot.y, 0.0f));

	CEffect3D::Create(pos, 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// デバッグプロック取得
	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
		return;
	
	pDebugProc->Print("\n敵のバイクの位置[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	//pDebugProc->Print("\n敵の位置[%f,%f,%f]", m_pEnemyNinja->GetPosition().x, m_pEnemyNinja->GetPosition().y, m_pEnemyNinja->GetPosition().z);
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
