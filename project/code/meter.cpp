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
	const int SECOND = 70;		// メーターの表示値
	const int PLACE = 2;		// 桁数
}

//=====================================================
// 静的メンバ変数
//=====================================================
CMeter* CMeter::m_pMeter = nullptr;

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CMeter::CMeter(int nPriority)
{
	m_NowMeter = 0;			// 現在のメーター値
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
	if (m_pMeter == nullptr)
	{// インスタンス生成
		m_pMeter = new CMeter;

		if (m_pMeter != nullptr)
		{// 初期化
			m_pMeter->Init();
		}
	}

	return m_pMeter;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CMeter::Init(void)
{
	// プレイヤーの情報取得
	m_pPlayer = CPlayer::GetInstance();

	// 速度
	m_NowMeter = 0;

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

	m_pMeter = nullptr;

	// 自身の破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CMeter::Update(void)
{
	// メーター値の加算
	Acceleration();
}

//=====================================================
// 加速時処理
//=====================================================
void CMeter::Acceleration()
{
	// デルタタイム取得
	float fDeltaTime = CManager::GetDeltaTime();

	// 速度取得
	float fSpeed = m_pPlayer->GetSpeed();
	float fMaxSpeed = m_pPlayer->GetParam().fSpeedMax;

	m_NowMeter = fSpeed;

	if (m_NowMeter >= fMaxSpeed)
	{// プレイヤーパラメーターの速度を超えないように
		m_NowMeter = fMaxSpeed;
	}

	// メーター値の計算
	int Meter = m_NowMeter % SECOND;

	if (m_pNumber != nullptr)
	{// 秒表示の制御
		m_pNumber->SetValue(Meter, PLACE);
	}

	if (m_NowMeter <= 0)
	{// マイナスの値にいかないように
		m_NowMeter = 0;
	}
}
