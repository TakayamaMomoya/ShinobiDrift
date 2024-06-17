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
	const D3DXVECTOR3 STARTPOS = D3DXVECTOR3(15000.0f, 00.0f, -15000.0f);		// 始点の位置
	const D3DXVECTOR3 ENDPOS = D3DXVECTOR3(17000.0f, 00.0f, -12000.0f);		// 終点の位置
}

//=====================================================
// コンストラクタ
//=====================================================
CGoal::CGoal(int nPriority)
{
	m_pPlayer = nullptr;
	m_pObj3D = nullptr;
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
CGoal* CGoal::Create()
{
	CGoal* pGoal = new CGoal;

	// 初期化
	pGoal->Init();

	return pGoal;
}

//=====================================================
// 初期化
//=====================================================
HRESULT CGoal::Init()
{
	// 生成
	m_pObj3D = CObject3D::Create(STARTPOS);

	// 色設定
	m_pObj3D->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f));

	// サイズ設定
	m_pObj3D->SetSize(2000.0f, 100.0f);

	// ベクトル
	D3DXVECTOR3 vec = ENDPOS - STARTPOS;

	// 位置設定
	m_pObj3D->SetPosition(D3DXVECTOR3(STARTPOS + vec * 0.5f));

	// 向き設定
	m_pObj3D->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.75f, 0.0f));

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
	// 確認用変数
	int n = 0;

	// 交点の割合
	float fCross = 0.0f;

	// プレイヤー情報取得
	CPlayer* pPlayer = CPlayer::GetInstance();

	// フェード情報取得
	CFade* pFade = CFade::GetInstance();

	// 位置取得
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// 移動量取得
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();

	// 外積の判定
	if (universal::IsCross(posPlayer,		// プレイヤーの位置
		STARTPOS,		// ゴールの始点
		ENDPOS,			// ゴールの終点
		&fCross,		// 交点の割合
		movePlayer))	// プレイヤーの移動量
	{
		if (fCross > 0.0f && fCross < 1.0f)
		{// 始点と終点の間を通った時
			n = 1;

			// カウント加算
			m_nTransitionTime++;

			if (m_nTransitionTime >= Transition)
			{
				// 画面遷移
				//pFade->SetFade(CScene::MODE_RESULT);

				// カウントリセット
				m_nTransitionTime = 0;
			}

			CDebugProc::GetInstance()->Print("\nゴールした");
		}
	}

#ifdef _DEBUG
	CEffect3D::Create(STARTPOS, 200.0f, 3, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	CEffect3D::Create(ENDPOS, 200.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
#endif

	CDebugProc::GetInstance()->Print("\nnの値[%d]", n);
	CDebugProc::GetInstance()->Print("\nfCrossの値[%f]", fCross);
	CDebugProc::GetInstance()->Print("\nstartPosの位置[%f, %f, %f]", STARTPOS.x, STARTPOS.y, STARTPOS.z);
	CDebugProc::GetInstance()->Print("\nendPosの位置[%f, %f, %f]", ENDPOS.x, ENDPOS.y, ENDPOS.z);
}

//=====================================================
// 描画
//=====================================================
void CGoal::Draw()
{
	m_pObj3D->Draw();
}
