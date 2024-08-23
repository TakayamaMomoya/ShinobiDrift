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
const float DIST_NUMBER = 0.015f;	// 数字間の距離
D3DXVECTOR2 SIZE_NORMAL_NUM = { 0.02f, 0.04f };	// 通常数字のサイズ
D3DXVECTOR2 SIZE_MINI_NUM = { 0.014f, 0.028f };	// ミニ数字のサイズ
D3DXVECTOR3 POS_INITIAL = { 0.5f,0.04f,0.0f };	// 初期位置
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

	// 初期位置の設定
	SetPosition(POS_INITIAL);

	// 数字の配列のリサイズ
	m_aNumber.resize(E_Number::NUMBER_MAX);

	int aDigit[E_Number::NUMBER_MAX] =
	{// 桁数
		MINUTES_DIGIT,
		TIME_DIGIT,
		TIME_DIGIT
	};

	D3DXVECTOR2 aSize[E_Number::NUMBER_MAX] =
	{// 数字のサイズ
		SIZE_NORMAL_NUM,
		SIZE_NORMAL_NUM,
		SIZE_MINI_NUM
	};

	// 数字分、生成して設定
	for (int i = 0; i < E_Number::NUMBER_MAX; i++)
	{
		m_aNumber[i] = CNumber::Create(aDigit[i], 0);	// 数字の生成

		if (m_aNumber[i] == nullptr)
			continue;

		// 参照するサイズの番号
		int nIdx = i;

		if (nIdx > 0)
			nIdx--;	// 0番目でなければ前回のサイズを参照する

		// パラメーター設定
		float fWidth = aSize[nIdx].x * aDigit[nIdx] * 2 + DIST_NUMBER;	// サイズに応じて数字間のスペースをあける
		D3DXVECTOR3 pos = { POS_INITIAL.x + fWidth * (i - 1), POS_INITIAL.y, 0.0f };
		m_aNumber[i]->SetPosition(pos);
		m_aNumber[i]->SetSizeAll(aSize[i].x, aSize[i].y);
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CTimer::Uninit(void)
{
	for (auto it : m_aNumber)
	{
		it->Uninit();
	}

	m_aNumber.clear();

	// 自身の破棄
	CGameObject::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CTimer::Update(void)
{
	if (!m_bStop)
	{// 数字の更新
		UpdateNumber();
	}
}

//=====================================================
// 数字の更新
//=====================================================
void CTimer::UpdateNumber()
{
	if (m_aNumber.empty())
		return;

	// 値の用意
	int aValue[E_Number::NUMBER_MAX] =
	{
		(int)m_fSecond / SECOND_LIMIT,
		(int)m_fSecond % SECOND_LIMIT,
		(int)(m_fSecond * MAGNIFICATION) % (int)MAGNIFICATION
	};

	for (int i = 0; i < E_Number::NUMBER_MAX; i++)
	{
		m_aNumber[i]->SetValue(aValue[i]);
	}
}

//=====================================================
// 描画処理
//=====================================================
void CTimer::Draw()
{

}