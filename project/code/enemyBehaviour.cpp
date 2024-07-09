//*****************************************************
//
// エネミービヘイビア[enemyBehaviour.cpp]
// Author:大原怜将
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "enemyBehaviour.h"
#include "enemy.h"
#include "effect3D.h"
#include "debugproc.h"
#include "player.h"
#include "myLib.h"
#include "meshRoad.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float SPEED_DEFAULT_CAHSE = 50.0f;	// 追跡の標準速度
}

//********************************************************************************
// プレイヤーの追跡
//********************************************************************************
//=====================================================
// コンストラクタ
//=====================================================
CEnemyBehaviourChasePlayer::CEnemyBehaviourChasePlayer()
{

}

//=====================================================
// デストラクタ
//=====================================================
CEnemyBehaviourChasePlayer::~CEnemyBehaviourChasePlayer()
{

}

//=====================================================
// 初期化
//=====================================================
void CEnemyBehaviourChasePlayer::Init(CEnemy *pEnemy)
{
	// スプラインの情報を取得
	m_pSpline = CMeshRoad::GetInstance()->GetCenterSpline();

	// ロードポイントの情報を取得
	std::vector<CMeshRoad::SInfoRoadPoint> pRoadPoint = *CMeshRoad::GetInstance()->GetArrayRP();

	// ベクターを必要なサイズに調整
	int nSize = pRoadPoint.size();
	m_vPos.resize(nSize);

	for (int i = 0; i < nSize; i++)
	{
		m_vPos[i] = pRoadPoint[i].pos;
	}

	// 中心スプラインの初期化
	if (m_pSpline != nullptr)
		m_pSpline->Init(m_vPos);

	// 初期スピードの計算
	m_fSpeedDefault = SPEED_DEFAULT_CAHSE;
	CalcSpeed(pEnemy);

	pEnemy->SetPosition(D3DXVECTOR3(pRoadPoint[0].pos.x, pRoadPoint[0].pos.y, pRoadPoint[0].pos.z));
}

//=====================================================
// 終了
//=====================================================
void CEnemyBehaviourChasePlayer::Uninit(CEnemy *pEnemy)
{

}

//=====================================================
// 更新
//=====================================================
void CEnemyBehaviourChasePlayer::Update(CEnemy *pEnemy)
{
	// 位置の補間
	InterpolatePosition(pEnemy);
}

//=====================================================
// 位置の補間
//=====================================================
void CEnemyBehaviourChasePlayer::InterpolatePosition(CEnemy *pEnemy)
{
	D3DXVECTOR3 pos = pEnemy->GetPosition();

	if (m_fRate >= 1.0f)
	{
		m_nIdx++;

		// サイズを超えたら戻す
		if (m_nIdx >= (int)m_vPos.size())
			m_nIdx = 1;

		// スピードの計算
		CalcSpeed(pEnemy);

		m_fRate -= 1.0f;
	}

	m_fRate += m_fSpeed;

	CPlayer *pPlayer = CPlayer::GetInstance();

	m_fSpeedDefault = pPlayer->GetSpeed() * 0.85f;

	// スピードの計算
	CalcSpeed(pEnemy);

	// 位置補間
	if (m_pSpline != nullptr)
	{
		if (m_pSpline->IsEmpty())
		{// スプラインが空だった時の再取得
			CMeshRoad *pMesh = CMeshRoad::GetInstance();

			if (pMesh == nullptr)
				return;

			m_pSpline = pMesh->GetCenterSpline();

			if (m_pSpline->IsEmpty())
				return;	// 再取得しても空だったら処理を通さない
		}

		pos = m_pSpline->Interpolate(m_fRate, m_nIdx);
	}

	// 位置と向き更新
	pEnemy->SetPosition(pos);

	// 向きの制御
	ControllRot(pEnemy);

	// デバッグ表示
	Debug(pEnemy);
}

//=====================================================
// スピードの計算
//=====================================================
void CEnemyBehaviourChasePlayer::CalcSpeed(CEnemy *pEnemy)
{
	if (m_pSpline == nullptr)
		return;

	if (m_pSpline->IsEmpty())
		return;

	float fLength = m_pSpline->GetLength(m_nIdx, 50);

	if (fLength == 0)
		return;	// 0割り防止

	m_fSpeed = m_fSpeedDefault / fLength;
}

//=====================================================
// 向きの制御
//=====================================================
void CEnemyBehaviourChasePlayer::ControllRot(CEnemy *pEnemy)
{
	D3DXVECTOR3 pos = pEnemy->GetPosition();
	D3DXVECTOR3 rot = pEnemy->GetRotation();

	// 次のデータ点の方を向く
	universal::FactingRotTarget(&rot, pos, m_vPos[m_nIdx], 0.05f);

	pEnemy->SetRotation(D3DXVECTOR3(0.0f, rot.y, 0.0f));
}

//=====================================================
// デバッグ表示
//=====================================================
void CEnemyBehaviourChasePlayer::Debug(CEnemy *pEnemy)
{
	// デバッグプロック取得
	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
		return;

	CEffect3D::Create(pEnemy->GetPosition(), 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	pDebugProc->Print("\n敵のバイクの位置[%f,%f,%f]", pEnemy->GetPosition().x, pEnemy->GetPosition().y, pEnemy->GetPosition().z);
	pDebugProc->Print("\n敵の速度[%f]", m_fSpeedDefault);
}
