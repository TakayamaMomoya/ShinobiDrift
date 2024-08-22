//*****************************************************
//
// タイムの処理[timer.h]
// Author:森川駿弥
//
//*****************************************************
#ifndef _TIMER_H_
#define _TIMER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "number.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CTimer : public CObject
{
public:
	CTimer();	// コンストラクタ
	~CTimer();	// デストラクタ

	// メンバ関数
	HRESULT Init();
	void Uninit();
	void Update();

	void Minutes();
	void Second();
	void MilliSecond();

	// 変数取得・設定関数
	float GetSecond() { return m_fSecond; }	// 秒
	void SetSecond(float fSecond) { m_fSecond = fSecond; }
	void AddSecond(float fSecond) { m_fSecond += fSecond; }
	bool GetFlag() { return m_bStop; }	// 動作フラグ
	void SetFlag(bool bStop) { m_bStop = bStop; }

	// 静的メンバ関数
	static CTimer *Create();	// 生成

private:
	// メンバ変数
	float m_fSecond;			// 現在の時間(秒)
	bool m_bStop;				// タイマー停止のフラグ
	CNumber* m_pMinutes;		// 分表示のポインタ
	CNumber* m_pSecond;			// 秒表示のポインタ
	CNumber* m_pMilli;			// ミリ秒表示のポインタ
};

#endif
