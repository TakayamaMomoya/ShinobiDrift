//*****************************************************
//
// ランクタイムの処理[rankTime.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _RANKTIME_H_
#define _RANKTIME_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CTimer;
class CUI;

//*****************************************************
// クラスの定義
//*****************************************************
class CRankTime : public CObject
{
public:
	CRankTime();	// コンストラクタ
	~CRankTime();	// デストラクタ

	// メンバ関数
	HRESULT Init();
	void Uninit();
	void Update();

	// 静的メンバ関数
	static CRankTime* Create();	// 生成
	static CRankTime* GetInstance() { return s_pRankTime; }	// インスタンス取得

private:
	// メンバ変数
	vector<CTimer*> m_aTimer;	// ランカーのタイム配列

	// 静的メンバ変数
	static CRankTime* s_pRankTime;	// 自身のポインタ
};

namespace RankTime
{
// ランキングタイム読込
vector<float> LoadRankTime(void);

// ランキングタイム保存
void SaveRankTime(vector<float> aTime);
}

#endif