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
#include "texture.h"
#include "input.h"
#include "inputkeyboard.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const int SECOND = 140;		// メーターの表示値
const int PLACE = 3;		// 桁数
const float WIDTH = SCREEN_WIDTH * 0.80f;		// 幅
const float HEIGHT = SCREEN_HEIGHT * 0.9f;		// 高さ
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
	m_nIdxTexture = 0;		// テクスチャ番号
	m_fRot = 0.0f;			// 向き
	m_pNumber = nullptr;	// ナンバーのポインタ
	m_pPlayer = nullptr;	// プレイヤーのポインタ
	m_pUI = nullptr;		// UIのポインタ
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
HRESULT CMeter::Init()
{
	// 速度
	m_NowMeter = 0;

	// カウント加算
	m_nCntMeter = 0;

	// テクスチャ番号
	m_nIdxTexture = 0;

	// プレイヤーの情報取得
	if (m_pPlayer == nullptr)
		m_pPlayer = CPlayer::GetInstance();

	// テクスチャ情報の取得
	CTexture* pTexture = CTexture::GetInstance();

	// テクスチャ番号
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\UI\\Needle.png");

	if (m_pUI == nullptr)
	{
		// 生成
		m_pUI = CUI::Create();

		// テクスチャ設定
		m_pUI->SetIdxTexture(m_nIdxTexture);

		// 位置設定
		m_pUI->SetPosition(D3DXVECTOR3(1100, 600.0f, 0.0f));

		// サイズ設定
		m_pUI->SetSize(75.0f, 100.0f);

		// 向き設定
		m_pUI->SetRotation(0.0f);

		// 頂点情報設定
		m_pUI->SetVtx();

		// 色設定
		m_pUI->SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
	}

	if (m_pNumber == nullptr)
	{
		// 生成
		m_pNumber = CNumber::Create(PLACE, 0);

		// 位置設定
		m_pNumber->SetPosition(D3DXVECTOR3(WIDTH, HEIGHT, 0.0f));

		// サイズ調整
		m_pNumber->SetSizeAll(30.0f, 30.0f);

		// 色設定
		m_pNumber->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CMeter::Uninit(void)
{
	if (m_pNumber != nullptr)
		m_pNumber = nullptr;

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	if (m_pUI != nullptr)
		m_pUI = nullptr;

	if (m_pMeter != nullptr)
		m_pMeter = nullptr;

	// 自身の破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CMeter::Update(void)
{
	// メーター値
	Acceleration();

	CDebugProc::GetInstance()->Print("\n現在の向き[%f]", m_fRot);
}

//=====================================================
// メーター値処理
//=====================================================
void CMeter::Acceleration()
{
	// デルタタイム取得
	float fDeltaTime = CManager::GetDeltaTime();

	if (m_pPlayer != nullptr)
	{
		// 速度取得
		float fPlayerSpeed = m_pPlayer->GetSpeed();

		// 最高速度
		float fMaxSpeed = m_pPlayer->GetParam().fSpeedMax;


		// 速度取得
		m_NowMeter = (int)fPlayerSpeed;

		if (m_NowMeter >= fMaxSpeed)
		{// プレイヤーパラメーターの速度を超えないように
			m_NowMeter = (int)fMaxSpeed;
		}
	}

	// メーター値の計算
	int Meter = m_NowMeter % SECOND;

	if (m_pNumber != nullptr)
	{// 値表示の制御
		m_pNumber->SetValue(Meter, PLACE);
	}

	if (m_NowMeter <= 0)
	{// マイナスの値にいかないように
		m_NowMeter = 0;
	}
}

//=====================================================
// メーター針処理
//=====================================================
void CMeter::Needle()
{
	if (m_pUI != nullptr)
	{
		// 向き取得
		m_fRot = m_pUI->GetRotation();

		// 
		m_fRot;

		// 向き設定
		m_pUI->SetRotation(m_fRot);
	}
}
