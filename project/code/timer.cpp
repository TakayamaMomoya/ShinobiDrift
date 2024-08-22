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
#include "goal.h"
#include "player.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const int MINUTES_LIMIT = 9;		// 分の上限値
const int SECOND_LIMIT = 59;		// 秒の上限値
const int MILLI_LIMIT = 99;			// ミリ秒の上限
const int MINUTES_DIGIT = 1;		// 分表示の桁数
const int TIME_DIGIT = 2;			// それぞれの桁数
const float MAGNIFICATION = 100.0f;	// 掛ける倍率
const float MINUTES_WIDTH = 0.44f;	// 分のX座標
const float SECOND_WIDTH = 0.5f;		// 秒のX座標
const float MILLI_WIDTH = 0.6f;		// ミリ秒のX座標
D3DXVECTOR2 SIZE_NORMAL_NUM = { 0.02f, 0.04f };	// 通常数字のサイズ
D3DXVECTOR2 SIZE_MINI_NUM = { 0.014f, 0.028f };	// ミニ数字のサイズ
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CTimer::CTimer()
{
	m_fSecond = 0.0f;			// 現在の時間(秒)
	m_bStop = false;
	m_pMinutes = nullptr;		// 分表示のポインタ
	m_pSecond = nullptr;		// 秒表示用のポインタ
	m_pMilli = nullptr;			// ミリセカンド表示用のポインタ
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
	CTimer *pTimer = nullptr;

	pTimer = new CTimer;

	if (pTimer != nullptr)
	{// 初期化
		pTimer->Init();
	}

	return pTimer;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CTimer::Init(void)
{
	// 分・秒・ミリ秒の初期化
	m_fSecond = 0.0f;

	m_bStop = false;	// タイマー停止のフラグ

	if (m_pMinutes == nullptr)
	{// 分表示
		// 生成・位置、サイズ設定
		m_pMinutes = CNumber::Create(MINUTES_DIGIT, MINUTES_LIMIT);
		m_pMinutes->SetPosition(D3DXVECTOR3(MINUTES_WIDTH, SIZE_MINI_NUM.y * 2.0f + 0.01f, 0.0f));
		m_pMinutes->SetSizeAll(SIZE_NORMAL_NUM.x, SIZE_NORMAL_NUM.y);
	}

	if (m_pSecond == nullptr)
	{// 秒表示
		// 生成・位置、サイズ設定
		m_pSecond = CNumber::Create(TIME_DIGIT, SECOND_LIMIT);
		m_pSecond->SetPosition(D3DXVECTOR3(SECOND_WIDTH, SIZE_MINI_NUM.y * 2.0f + 0.01f , 0.0f));
		m_pSecond->SetSizeAll(SIZE_NORMAL_NUM.x, SIZE_NORMAL_NUM.y);
	}

	if (m_pMilli == nullptr)
	{// ミリ秒表示
		// 生成・位置、サイズ設定
		m_pMilli = CNumber::Create(TIME_DIGIT, MILLI_LIMIT);
		m_pMilli->SetPosition(D3DXVECTOR3(MILLI_WIDTH, SIZE_MINI_NUM.y * 2.0f + 0.01f, 0.0f));
		m_pMilli->SetSizeAll(SIZE_MINI_NUM.x, SIZE_MINI_NUM.y);
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CTimer::Uninit(void)
{
	if (m_pMinutes != nullptr)
	{// 分の終了
		m_pMinutes->Uninit();
		m_pMinutes = nullptr;
	}

	if (m_pSecond != nullptr)
	{// 秒の終了
		m_pSecond->Uninit();
		m_pSecond = nullptr;
	}

	if (m_pMilli != nullptr)
	{// ミリ秒の終了
		m_pMilli->Uninit();
		m_pMilli = nullptr;
	}

	// 自身の破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CTimer::Update(void)
{
	// 分の更新
	if (!m_bStop)
	{
		Minutes();
	}
}

//=====================================================
// 分の更新
//=====================================================
void CTimer::Minutes()
{
	// 秒の更新
	Second();

	// 分の計算
	int nMinutes = (int)m_fSecond / SECOND_LIMIT;

	// 分の上限値超えないように
	if (nMinutes >= MINUTES_LIMIT)
		nMinutes = MINUTES_LIMIT;

	// 分表示
	if (m_pMinutes != nullptr)
		m_pMinutes->SetValue(nMinutes, MINUTES_DIGIT);
}

//=====================================================
// 秒の更新
//=====================================================
void CTimer::Second()
{
	// ミリ秒の更新
	MilliSecond();

	// 秒の計算
	int nSecond = (int)m_fSecond % SECOND_LIMIT;

	// 秒表示
	if (m_pSecond != nullptr)
		m_pSecond->SetValue(nSecond, TIME_DIGIT);
}

//=====================================================
// ミリ秒更新
//=====================================================
void CTimer::MilliSecond()
{
	// 秒を100倍
	int nMilli = (int)(m_fSecond * MAGNIFICATION);

	// ミリ秒の計算
	nMilli = nMilli % (int)MAGNIFICATION;

	// ミリ秒表示
	if (m_pMilli != nullptr)
		m_pMilli->SetValue(nMilli, TIME_DIGIT);
}
