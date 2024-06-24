//*****************************************************
//
// ゴール処理[goal.cpp]
// Author:森川駿弥
//
//*****************************************************

#include "goal.h"
#include "universal.h"
#include "debugproc.h"
#include "effect3D.h"
#include "fade.h"
#include "object3D.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const int Transition = 120;		// 画面遷移するまでの時間
	const float MOVESPEED = 4.0f;	// 移動速度
	const float WIDTH_GOAL = 100.0f;	// ゴールの幅
}

//=====================================================
// コンストラクタ
//=====================================================
CGoal::CGoal(int nPriority)
{
	m_nTransitionTime = 0;		// 遷移カウンター
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	m_posStart = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ゴールの始点
	m_posEnd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ゴールの終点
	m_fRot = 0.0f;		// 向き
	m_pPlayer = nullptr;	// プレイヤーのポインタ
	m_pObj3D = nullptr;		// オブジェクト3Dのポインタ
}

//=====================================================
// デストラクタ
//=====================================================
CGoal::~CGoal()
{
}

//=====================================================
// 生成
//=====================================================
CGoal* CGoal::Create(D3DXVECTOR3 pos,float fRot, float fLength)
{
	CGoal* pGoal = new CGoal;

	if (pGoal != nullptr)
	{
		pGoal->m_pos = pos;
		pGoal->m_fRot = fRot;
		pGoal->m_fLength = fLength;

		// 初期化
		pGoal->Init();
	}

	return pGoal;
}

//=====================================================
// 初期化
//=====================================================
HRESULT CGoal::Init()
{
	// 始点・終点の計算
	m_posStart.x = sinf(m_fRot) * m_fLength;
	m_posStart.z = cosf(m_fRot) * m_fLength;

	m_posEnd = -m_posStart;

	m_posStart += m_pos;
	m_posEnd += m_pos;

	// ゴールテープの生成
	m_pObj3D = CObject3D::Create(m_pos);

	if (m_pObj3D != nullptr)
	{
		// 色設定
		m_pObj3D->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f));

		// サイズ設定
		m_pObj3D->SetSize(WIDTH_GOAL, m_fLength);

		m_pObj3D->SetRotation(D3DXVECTOR3(0.0f, m_fRot, 0.0f));
	}

	return S_OK;
}

//=====================================================
// 終了
//=====================================================
void CGoal::Uninit()
{
	if (m_pObj3D != nullptr)
	{
		m_pObj3D = nullptr;
	}

	// 自身の削除
	Release();
}

//=====================================================
// 更新
//=====================================================
void CGoal::Update()
{
	// プレイヤー情報取得
	CPlayer* pPlayer = CPlayer::GetInstance();

	// フェード情報取得
	CFade* pFade = CFade::GetInstance();

	// 位置取得
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// 移動量取得
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();

	// 交点の割合
	float fCross = 0.0f;

	// 外積の判定
	if (universal::IsCross(posPlayer,		// プレイヤーの位置
		m_posStart,		// ゴールの始点
		m_posEnd,			// ゴールの終点
		&fCross,		// 交点の割合
		movePlayer))	// プレイヤーの移動量
	{
		if (fCross > 0.0f && fCross < 1.0f)
		{// 始点と終点の間を通った時
			// カウント加算
			m_nTransitionTime++;

			if (m_nTransitionTime >= Transition)
			{
				// 画面遷移
				pFade->SetFade(CScene::MODE_RESULT);

				// カウントリセット
				m_nTransitionTime = 0;
			}

			CDebugProc::GetInstance()->Print("\nゴールした");
		}
	}

#ifdef _DEBUG
	CEffect3D::Create(m_posStart, 200.0f, 3, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	CEffect3D::Create(m_posEnd, 200.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
#endif

	CDebugProc::GetInstance()->Print("\nfCrossの値[%f]", fCross);
	CDebugProc::GetInstance()->Print("\nstartPosの位置[%f, %f, %f]", m_posStart.x, m_posStart.y, m_posStart.z);
	CDebugProc::GetInstance()->Print("\nendPosの位置[%f, %f, %f]", m_posEnd.x, m_posEnd.y, m_posEnd.z);
}

//=====================================================
// 描画
//=====================================================
void CGoal::Draw()
{

}