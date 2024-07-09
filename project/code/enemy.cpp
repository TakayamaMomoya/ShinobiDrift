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
#include "effect3D.h"
#include "meshRoad.h"
#include "shuriken.h"
#include "player.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const float SPEED_DEFAULT = 50.0f;
}

//=====================================================
// コンストラクタ
//=====================================================
CEnemy::CEnemy(int nPriority)
{
	m_nIdx = 1;
	m_Info.fRate = 0.0f;
	m_fSpeedDefault = 0.0f;
}

//=====================================================
// デストラクタ
//=====================================================
CEnemy::~CEnemy()
{

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
			// 初期化
			pEnemy->Init();
		}
	}

	return pEnemy;
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
	int nSize = pRoadPoint.size();
	m_vPos.resize(nSize);

	for (int i = 0; i < nSize; i++)
	{
		m_vPos[i] = pRoadPoint[i].pos;
	}

	// 中心スプラインの初期化
	if(m_pSpline != nullptr)
	   m_pSpline->Init(m_vPos);

	// 初期スピードの計算
	m_fSpeedDefault = SPEED_DEFAULT;
	CalcSpeed();

	SetPosition(D3DXVECTOR3(pRoadPoint[0].pos.x, pRoadPoint[0].pos.y, pRoadPoint[0].pos.z));

	return S_OK;
}

//=====================================================
// スピードの計算
//=====================================================
void CEnemy::CalcSpeed(void)
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
// 終了処理
//=====================================================
void CEnemy::Uninit(void)
{
	// 全ビヘイビア解放
	ReleaseAllBehaviour();

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

	// ビヘイビアの更新
	for (auto it : m_listBehaviour)
	{
		it->Update(this);
	}

	// 位置の補間
	InterpolatePosition();
}

//=====================================================
// 位置の補間
//=====================================================
void CEnemy::InterpolatePosition(void)
{
	D3DXVECTOR3 pos = GetPosition();

	if (m_Info.fRate >= 1.0f)
	{
		m_nIdx++;

		// サイズを超えたら戻す
		if (m_nIdx >= (int)m_vPos.size())
			m_nIdx = 1;

		// スピードの計算
		CalcSpeed();

		m_Info.fRate -= 1.0f;
	}

	m_Info.fRate += m_fSpeed;

	CPlayer *pPlayer = CPlayer::GetInstance();

	m_fSpeedDefault = pPlayer->GetSpeed() * 0.85f;

	// スピードの計算
	CalcSpeed();

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

		pos = m_pSpline->Interpolate(m_Info.fRate, m_nIdx);
	}

	// 位置と向き更新
	SetPosition(pos);

	// 向きの制御
	ControllRot();

	// デバッグ表示
	Debug();
}

//=====================================================
// 向きの制御
//=====================================================
void CEnemy::ControllRot(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// 次のデータ点の方を向く
	universal::FactingRotTarget(&rot, pos, m_vPos[m_nIdx], 0.05f);

	SetRotation(D3DXVECTOR3(0.0f, rot.y, 0.0f));
}

//=====================================================
// デバッグ表示
//=====================================================
void CEnemy::Debug(void)
{
	// デバッグプロック取得
	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
		return;

	CEffect3D::Create(GetPosition(), 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	pDebugProc->Print("\n敵のバイクの位置[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	pDebugProc->Print("\n敵の速度[%f]", m_fSpeedDefault);
}

//=====================================================
// 全ビヘイビア解放
//=====================================================
void CEnemy::ReleaseAllBehaviour(void)
{
	for (auto it : m_listBehaviour)
	{
		it->Uninit(this);
		m_listBehaviour.remove(it);
	}
}

//=====================================================
// 描画処理
//=====================================================
void CEnemy::Draw(void)
{
	// 継承クラスの描画
	CMotion::Draw();
}