//*****************************************************
//
// メーター[meter.h]
// Author:森川駿弥
//
//*****************************************************

#ifndef _METER_H_
#define _METER_H_

//*****************************************************
// 前方宣言
//*****************************************************
class CNumber;
class CUI;

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CMeter : public CObject
{
public:
	CMeter(int nPriority = 7);	// コンストラクタ
	~CMeter();	//	デストラクタ

	// メンバ関数
	HRESULT Init();
	void Uninit();
	void Update();

	// 変数取得・設定関数
	int GetMeter() { return m_NowMeter; }	// メーター値

	// 静的メンバ関数
	static CMeter* Create();	// 生成
	static CMeter* GetInstance() { return m_pMeter; }	// インスタンス取得

private:
	// メンバ関数
	void Acceleration();
	void Needle();

	//メンバ変数
	int m_NowMeter;		// 現在のメーター値
	int m_nCntMeter;	// カウント加算
	float m_fRot;		// 向き
	CNumber* m_pNumber;	// ナンバーのポインタ
	CUI* m_pNeedle;			// 針UIのポインタ
	CUI* m_pBackMeter;			// メーター背景のポインタ
	static CMeter* m_pMeter;	// 自身のポインタ
};

#endif
