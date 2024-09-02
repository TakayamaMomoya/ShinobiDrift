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
#include "UI.h"
#include "texture.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const int MINUTES_LIMIT = 9;	// 分の上限値
const int SECOND_LIMIT = 59;	// 秒の上限値
const int MILLI_LIMIT = 99;	// ミリ秒の上限
const int MINUTES_DIGIT = 2;	// 分表示の桁数
const int TIME_DIGIT = 2;	// それぞれの桁数
const float MAGNIFICATION = 100.0f;	// 掛ける倍率
const float MINUTES_WIDTH = 0.44f;	// 分のX座標
const float SECOND_WIDTH = 0.5f;	// 秒のX座標
const float MILLI_WIDTH = 0.6f;	// ミリ秒のX座標
const float DIST_NUMBER = 0.03f;	// 数字間の距離
D3DXVECTOR2 SIZE_NORMAL_NUM = { 0.02f, 0.04f };	// 通常数字のサイズ
D3DXVECTOR2 SIZE_MINI_NUM = { 0.014f, 0.028f };	// ミニ数字のサイズ
D3DXVECTOR3 POS_INITIAL = { 0.5f,0.08f,0.0f };	// 初期位置
const string PATH_TEX_COLON = "data\\TEXTURE\\UI\\colon.png";	// コロンのテクスチャパス
}

//=====================================================
// コンストラクタ
//=====================================================
CTimer::CTimer()
{
	m_fSecond = 0.0f;
	m_fScaleNumber = 0.0f;
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
	m_fSecond = 0.0f;	// 秒の初期化
	m_fScaleNumber = 1.0f;	// 初期スケール設定
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

	// 数字の生成
	for (int i = 0; i < E_Number::NUMBER_MAX; i++)
	{
		m_aNumber[i] = CNumber::Create(aDigit[i], 0);	// 数字の生成
	}

	// コロンの生成
	m_aColon.resize(E_Number::NUMBER_MAX - 1);

	for (int i = 0; i < E_Number::NUMBER_MAX - 1; i++)
	{
		m_aColon[i] = CUI::Create();

		if (m_aColon[i] == nullptr)
			continue;

		int nIdxTexture = Texture::GetIdx(&PATH_TEX_COLON[0]);
		m_aColon[i]->SetIdxTexture(nIdxTexture);
	}

	// 数字のトランスフォームの設定
	TransformNumber();

	// ゲームUIの削除


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

	for (auto it : m_aColon)
	{
		it->Uninit();
	}

	m_aColon.clear();

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
// 数字のトランスフォーム設定
//=====================================================
void CTimer::TransformNumber()
{
	if (m_aNumber.empty())
		return;

	int aDigit[E_Number::NUMBER_MAX] =
	{// 桁数
		MINUTES_DIGIT,
		TIME_DIGIT,
		TIME_DIGIT
	};

	D3DXVECTOR2 aSize[E_Number::NUMBER_MAX] =
	{// 数字のサイズ
		SIZE_NORMAL_NUM * m_fScaleNumber,
		SIZE_NORMAL_NUM * m_fScaleNumber,
		SIZE_NORMAL_NUM * m_fScaleNumber
	};

	D3DXVECTOR3 posBase = GetPosition();

	// 数字分、生成して設定
	for (int i = 0; i < E_Number::NUMBER_MAX; i++)
	{
		if (m_aNumber[i] == nullptr)
			continue;

		// 参照するサイズの番号
		int nIdx = i;

		if (nIdx > 0)
			nIdx--;	// 0番目でなければ前回のサイズを参照する

		// パラメーター設定
		float fWidth = aSize[nIdx].x * aDigit[nIdx] * 2 + DIST_NUMBER * m_fScaleNumber;	// サイズに応じて数字間のスペースをあける
		D3DXVECTOR3 pos = { posBase.x + fWidth * (i - 1), posBase.y, 0.0f };
		m_aNumber[i]->SetPosition(pos);
		m_aNumber[i]->SetSizeAll(aSize[i].x, aSize[i].y);

		if (i == 0)	// 0以上のときしか入らない処理
			continue;
		
		// コロンの位置を設定
		int nIdxColon = i - 1;

		if (m_aColon[nIdxColon] != nullptr)
		{
			float fPosXLast = m_aNumber[i - 1]->GetPosition().x + aDigit[i - 1] * aSize[i - 1].x;
			D3DXVECTOR3 posColon = { (pos.x + fPosXLast) / 2, pos.y, 0.0f };
			m_aColon[nIdxColon]->SetPosition(posColon);	// 位置
			m_aColon[nIdxColon]->SetSize(aSize[i].x, aSize[i].y);	// サイズ
			m_aColon[nIdxColon]->SetVtx();
		}
	}
}

//=====================================================
// 位置の設定
//=====================================================
void CTimer::SetPosition(D3DXVECTOR3 pos)
{
	CGameObject::SetPosition(pos);

	// 数字のトランスフォームの設定
	TransformNumber();
}

//=====================================================
// 数字のスケールの設定
//=====================================================
void CTimer::SetScaleNumber(float fScale)
{
	m_fScaleNumber = fScale;

	// 数字のトランスフォームの設定
	TransformNumber();
}

//=====================================================
// 色の設定
//=====================================================
void CTimer::SetColor(E_Number number, D3DXCOLOR col)
{
	if (number < 0 || number > E_Number::NUMBER_MAX)
		return;

	if (number == E_Number::NUMBER_MAX)
	{// 全数字の色設定
		for (auto it : m_aNumber)	// 数字
			it->SetColor(col);

		for (auto it : m_aColon)	// コロン
			it->SetCol(col);
	}
	else
	{// 各数字の色設定
		m_aNumber[number]->SetColor(col);
	}
}

//=====================================================
// 色の取得
//=====================================================
D3DXCOLOR CTimer::GetColor(E_Number number)
{
	if (number < 0 || number >= E_Number::NUMBER_MAX)
		return D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	return m_aNumber[number]->GetColor();
}

//=====================================================
// 描画処理
//=====================================================
void CTimer::Draw()
{

}