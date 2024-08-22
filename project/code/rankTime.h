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
	//メンバ変数
	static CRankTime* s_pRankTime;	// 自身のポインタ
};

#endif
