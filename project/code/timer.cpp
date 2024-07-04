//*****************************************************
//
// タイムの処理[timer.cpp]
// Author:森川駿弥
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "timer.h"
#include "manager.h"
#include "debugproc.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const int SECOND_PLACE = 3;			// 秒の桁数
const int SECOND_LIMIT = 300;		// 秒の上限値
const float SECOND_WIDTH = SCREEN_WIDTH * 0.5f;		// 秒のX座標
const int MILLI_PLACE = 2;			// ミリ秒の桁数
const int MILLI_LIMIT = 60;			// ミリ秒の上限
const float MILLI_WIDTH = SCREEN_WIDTH * 0.65f;
const int TIME_CALCULATION = 60;	// 秒計算用
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CTimer* CTimer::s_pTimer = nullptr;

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CTimer::CTimer(int nPriority) : CObject(nPriority)
{
	m_fSecond = 0.0f;			// 現在の時間(秒)
	m_fMsecond = 0.0f;			// 現在の時間(ミリ秒)
	m_pSecond = nullptr;		// 秒表示用のポインタ
	m_pMilliSecond = nullptr;	// ミリセカンド表示用のポインタ
}

//=====================================================
// デストラクタ
//=====================================================
CTimer::~CTimer()
{
}

//=====================================================
// 生成処理
//=====================================================
CTimer* CTimer::Create(void)
{
	if (s_pTimer == nullptr)
	{// インスタンス生成
		s_pTimer = new CTimer;
	}

	if (s_pTimer != nullptr)
	{// 初期化
		s_pTimer->Init();

		if (s_pTimer->m_pSecond == nullptr)
		{// 秒表示
			// 生成
			s_pTimer->m_pSecond = CNumber::Create(SECOND_PLACE, SECOND_LIMIT);

			// 位置
			s_pTimer->m_pSecond->SetPosition(D3DXVECTOR3(SECOND_WIDTH, 75.0f, 0.0f));

			// サイズ
			s_pTimer->m_pSecond->SetSizeAll(35.0f, 35.0f);
		}

		if (s_pTimer->m_pMilliSecond == nullptr)
		{// ミリ秒表示
			// 生成
			s_pTimer->m_pMilliSecond = CNumber::Create(MILLI_PLACE, MILLI_LIMIT);

			// 位置
			s_pTimer->m_pMilliSecond->SetPosition(D3DXVECTOR3(MILLI_WIDTH, 85.0f, 0.0f));

			// サイズ
			s_pTimer->m_pMilliSecond->SetSizeAll(25.0f,15.0f);
		}
	}

	return s_pTimer;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CTimer::Init(void)
{
	// 現在時間の初期化
	m_fSecond = 0.0f;

	m_fMsecond = 0.0f;

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CTimer::Uninit(void)
{
	s_pTimer = nullptr;

	if (m_pSecond != nullptr)
	{
		m_pSecond->Uninit();
		m_pSecond = nullptr;
	}

	if (m_pMilliSecond != nullptr)
	{
		m_pMilliSecond->Uninit();
		m_pMilliSecond = nullptr;
	}

	// 自身の破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CTimer::Update(void)
{
	// デルタタイム取得
	float fDeltaTime = CManager::GetDeltaTime();

	// デルタタイム(リアル時間)加算
	m_fSecond += fDeltaTime;
	m_fMsecond++;

	// 秒の計算
	int nSecond = (int)m_fSecond % TIME_CALCULATION;

	// ミリ秒の計算
	int nMsecond = (int)m_fMsecond % TIME_CALCULATION;

	// 秒表示の制御
	if (m_pSecond != nullptr)
		m_pSecond->SetValue(nSecond, SECOND_PLACE);

	// 制限時間の上限値超えないように
	if (nSecond >= SECOND_LIMIT)
		m_fSecond = SECOND_LIMIT;

	// 秒表示の制御
	if (m_pMilliSecond!= nullptr)
		m_pMilliSecond->SetValue(nMsecond, MILLI_PLACE);

	// 制限時間の上限値超えないように
	if (nMsecond >= MILLI_LIMIT)
		m_fMsecond = MILLI_LIMIT;
}
