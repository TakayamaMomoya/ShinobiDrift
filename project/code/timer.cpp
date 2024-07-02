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
const int TIME_PLACE = 3;		// 桁数
const int TIME_LIMIT = 5;		// タイムの上限値
const float TIME_WIDTH = SCREEN_WIDTH * 0.5f;		// 幅
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CTimer* CTimer::m_pTimer = nullptr;

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CTimer::CTimer(int nPriority) : CObject(nPriority)
{
	m_fSeconds = 0.0f;		// 現在の時間
	m_pNumber = nullptr;	// ナンバーのポインタ
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
	m_fSeconds = 0.0f;

	// 生成
	if(m_pNumber == nullptr)
	m_pNumber = CNumber::Create(TIME_PLACE, TIME_LIMIT);

	if (m_pNumber != nullptr)
	{
		// 位置設定
		m_pNumber->SetPosition(D3DXVECTOR3(TIME_WIDTH, 75.0f, 0.0f));

		// サイズ調整
		m_pNumber->SetSizeAll(35.0f, 35.0f);
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CTimer::Uninit(void)
{
	if (m_pNumber != nullptr)
	{
		m_pNumber->Uninit();
		m_pNumber = nullptr;
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

	// タイマー加算
	m_fSeconds += fDeltaTime;

	// 秒の計算
	int nSecond = (int)m_fSeconds % 60;

	// 秒表示の制御
	if (m_pNumber != nullptr)
		m_pNumber->SetValue(nSecond, TIME_PLACE);

	// タイマーの上限値超えないように
	if (nSecond >= TIME_LIMIT)
		m_fSeconds = TIME_LIMIT;

	//CDebugProc::GetInstance()->Print("\nデルタタイム[%f]", fDeltaTime);
}
