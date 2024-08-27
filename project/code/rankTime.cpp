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
#include "UI.h"
#include "texture.h"

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
const float SIZE_MEDAL = 0.025f;	// メダルのサイズ
const D3DXVECTOR2 SIZE_FRAME = { 0.13f,0.025f };	// フレームのサイズ
const D3DXCOLOR COL_FRAME = { 0.4f, 0.4f, 0.4f, 0.7f };	// フレームの色
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
	m_aFrame.resize(NUM_TIMER_RUNKER);
	m_aMedal.resize(NUM_TIMER_RUNKER);

	vector<float> aTime = RankTime::LoadRankTime();

	vector<string> aPathMedal(NUM_TIMER_RUNKER);
	aPathMedal =
	{
		"data\\TEXTURE\\UI\\rank00.png",
		"data\\TEXTURE\\UI\\rank01.png",
		"data\\TEXTURE\\UI\\rank02.png"
	};

	for (int i = 0; i < NUM_TIMER_RUNKER; i++)
	{
		D3DXVECTOR3 pos = POS_NUMBER_DEFAULT;
		pos.y += DIST_TIMER * i;

		// フレームの生成
		m_aFrame[i] = CUI::Create();

		if (m_aFrame[i] == nullptr)
			continue;

		D3DXVECTOR3 posFrame = pos;
		m_aFrame[i]->SetPosition(posFrame);
		m_aFrame[i]->SetSize(SIZE_FRAME.x, SIZE_FRAME.y);
		m_aFrame[i]->SetVtx();
		m_aFrame[i]->SetCol(COL_FRAME);

		// タイマーの生成
		m_aTimer[i] = CTimer::Create();

		if (m_aTimer[i] == nullptr)
			continue;
		m_aTimer[i]->SetPosition(pos);	// 位置
		m_aTimer[i]->SetScaleNumber(SCALE_NUMBER);// スケール
		m_aTimer[i]->SetSecond(aTime[i]);

		// タイマー横のメダルアイコンの生成
		D3DXVECTOR3 posMedal = pos;
		posMedal.x -= SIZE_MEDAL * 4;

		m_aMedal[i] = CUI::Create();

		if (m_aMedal[i] == nullptr)
			continue;

		m_aMedal[i]->SetPosition(posMedal);
		m_aMedal[i]->SetSize(SIZE_MEDAL, SIZE_MEDAL);
		m_aMedal[i]->SetVtx();

		int nIdxTexture = Texture::GetIdx(&aPathMedal[i][0]);
		m_aMedal[i]->SetIdxTexture(nIdxTexture);
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CRankTime::Uninit(void)
{
	s_pRankTime = nullptr;

	auto lamda = [](CObject* pObj)
	{
		if (pObj == nullptr)
			return;

		pObj->Uninit();
	};

	std::for_each(m_aFrame.begin(), m_aFrame.end(), lamda);
	std::for_each(m_aMedal.begin(), m_aMedal.end(), lamda);
	std::for_each(m_aTimer.begin(), m_aTimer.end(), lamda);

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