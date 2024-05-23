//*****************************************************
//
// タイムの処理[timer.cpp]
// Author:森川駿弥
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "meter.h"
#include "manager.h"
#include "debugproc.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const int VALUE = 240;			// 値
	const int PLACE = 3;			// 桁数
	const float WIDTH = SCREEN_WIDTH * 0.5f;		// 幅
	const float HEIGHT = SCREEN_HEIGHT * 0.5f;		// 高さ
}

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CMeter::CMeter(int nPriority)
{
	m_nMeter = 0;			// 現在のメーター値
	m_nCntMeter = 0;		// メーター加算
	m_pNumber = nullptr;	// ナンバーのポインタ
	m_pPlayer = nullptr;	// プレイヤーのポインタ
}

//=====================================================
// デストラクタ
//=====================================================
CMeter::~CMeter()
{
}

//=====================================================
// 生成処理
//=====================================================
CMeter* CMeter::Create(void)
{
	// インスタンス生成
	CMeter* pMeter = new CMeter;

	// 初期化
	pMeter->Init();

	return pMeter;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CMeter::Init(void)
{
	// プレイヤーの情報取得
	m_pPlayer = CPlayer::GetInstance();

	// 速度
	m_nMeter = 0;

	// 生成
	m_pNumber = CNumber::Create(PLACE, 0);

	// 位置設定
	m_pNumber->SetPosition(D3DXVECTOR3(1000, 600.0f, 0.0f));

	// サイズ調整
	m_pNumber->SetSizeAll(35.0f, 35.0f);

	// 色設定
	m_pNumber->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CMeter::Uninit(void)
{
	m_pNumber = nullptr;

	// 自身の破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CMeter::Update(void)
{
	// デルタタイム取得
	float fDeltaTime = CManager::GetDeltaTime();

	Acceleration();
}

//=====================================================
// 加速時処理
//=====================================================
void CMeter::Acceleration()
{
	// 速度取得
	float fSpeed = m_pPlayer->GetParam().fSpeedMax;

	// カウンター加算
	m_nCntMeter++;

	if (m_nCntMeter > 60)
	{
		m_nCntMeter = 0;

		if (m_nMeter >= 1)
		{// メーター加算
			m_nMeter++;
		}
	}

	// 秒の計算
	int nSecond = m_nMeter % VALUE;

	if (m_pNumber != nullptr)
	{// 秒表示の制御
		m_pNumber->SetValue(nSecond, PLACE);
	}

	if (m_nMeter <= 0)
	{
		m_nMeter = 0;
	}
}

//=====================================================
// 減速時処理
//=====================================================
void CMeter::Deceleration()
{
	// 速度取得
	float fSpeed = m_pPlayer->GetParam().fSpeedMax;

	// カウンター加算
	m_nCntMeter++;

	if (m_nCntMeter > 60)
	{
		m_nCntMeter = 0;

		if (m_nMeter >= 1)
		{// メーター減算
			m_nMeter--;
		}
	}

	// 秒の計算
	int nSecond = m_nMeter % VALUE;

	if (m_pNumber != nullptr)
	{// 秒表示の制御
		m_pNumber->SetValue(nSecond, PLACE);
	}

	if (m_nMeter <= 0)
	{
		m_nMeter = 0;
	}
}
