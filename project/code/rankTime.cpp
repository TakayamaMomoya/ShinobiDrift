//*****************************************************
//
// ランクタイムの処理[rankTime.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "rankTime.h"
#include "timer.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const int NUM_TIMER_RUNKER = 3;	// ランカーのタイムの数
const D3DXVECTOR3 POS_NUMBER_DEFAULT = { 0.9f, 0.2f,0.0f };	// 数字のデフォルト位置
const float SCALE_NUMBER = 0.5f;	// タイマーの数字のスケール
const float DIST_TIMER = 0.1f;	// タイマー間の距離
const string PATH_SAVE = "data\\BYNARY\\ranking.bin";	// ランキングのファイルパス
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CRankTime *CRankTime::s_pRankTime = nullptr;

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CRankTime::CRankTime()
{

}

//=====================================================
// デストラクタ
//=====================================================
CRankTime::~CRankTime()
{

}

//=====================================================
// 生成処理
//=====================================================
CRankTime* CRankTime::Create(void)
{
	if (s_pRankTime == nullptr)
	{// インスタンス生成
		s_pRankTime = new CRankTime;

		if (s_pRankTime != nullptr)
		{// 初期化
			s_pRankTime->Init();
		}
	}
	
	return s_pRankTime;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CRankTime::Init(void)
{
	m_aTimer.resize(NUM_TIMER_RUNKER);

	vector<float> aTime = RankTime::LoadRankTime();

	// タイマーの生成
	for (int i = 0; i < NUM_TIMER_RUNKER; i++)
	{
		m_aTimer[i] = CTimer::Create();

		if (m_aTimer[i] == nullptr)
			continue;
		D3DXVECTOR3 pos = POS_NUMBER_DEFAULT;
		pos.y += DIST_TIMER * i;
		m_aTimer[i]->SetPosition(pos);	// 位置
		m_aTimer[i]->SetScaleNumber(SCALE_NUMBER);// スケール
		m_aTimer[i]->SetSecond(aTime[i]);
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CRankTime::Uninit(void)
{
	s_pRankTime = nullptr;

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CRankTime::Update(void)
{

}

namespace RankTime
{
//=====================================================
// ランキングタイム読込
//=====================================================
vector<float> LoadRankTime(void)
{
	vector<float> aTime;

	// ファイルを開く
	std::ifstream inputFile(PATH_SAVE, std::ios::binary);

	if (!inputFile.is_open())
		assert(("ランキングファイルを開けませんでした", false));

	while(true)
	{// ファイルの終わりまで読み込む
		float fTime;

		inputFile.read(reinterpret_cast<char*>(&fTime), sizeof(float));

		if (inputFile.eof())
			break;

		aTime.push_back(fTime);
	}

	inputFile.close();

	return aTime;
}

//=====================================================
// ランキングタイム保存
//=====================================================
void SaveRankTime(vector<float> aTime)
{
	// ファイルを開く
	std::ofstream outputFile(PATH_SAVE, std::ios::binary);

	if (!outputFile.is_open())
		assert(("ランキングファイルを開けませんでした", false));

	// 情報数保存
	size_t size = aTime.size();

	// 配列の保存
	outputFile.write(reinterpret_cast<char*>(aTime.data()), sizeof(float) * size);

	outputFile.close();
}
}