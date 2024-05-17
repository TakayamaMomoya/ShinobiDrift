//*****************************************************
//
//タイムの処理[timer.cpp]
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
	const int VALUE = 120;			// 値
	const int PLACE = 3;			// 桁数
	const float WIDTH = SCREEN_WIDTH * 0.5f;		// 幅
	const float HEIGHT = SCREEN_HEIGHT * 0.5f;		// 高さ
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CTimer::CTimer(int nPriority)
{
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
	// インスタンス生成
	CTimer* pTimer = new CTimer;

	// 初期化
	pTimer->Init();

	return pTimer;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CTimer::Init(void)
{
	m_nSeconds = VALUE;

	// 生成
	m_pNumber = CNumber::Create(PLACE, VALUE);

	// 位置設定
	m_pNumber->SetPosition(D3DXVECTOR3(WIDTH, 75.0f, 0.0f));

	// サイズ調整
	m_pNumber->SetSizeAll(35.0f, 35.0f);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CTimer::Uninit(void)
{
	m_pNumber = nullptr;

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

	// カウンター加算
	m_nCntSeconds++;

	if (m_nCntSeconds > 60)
	{
		m_nCntSeconds = 0;

		if (m_nSeconds >= 1)
		{
			m_nSeconds--;
		}
	}

	// 秒の計算
	int nSecond = m_nSeconds % VALUE;

	if (m_pNumber != nullptr)
	{// 秒表示の制御
		m_pNumber->SetValue(nSecond, PLACE);
	}

	if (m_nSeconds <= 0)
	{
		m_nSeconds = 0;
	}
}

//=====================================================
// 設定
//=====================================================
void CTimer::Set()
{
	int nSeconds = m_nSeconds % 60;

	if (m_pNumber != nullptr)
	{
		m_pNumber->SetValue(nSeconds, PLACE);
	}
}
