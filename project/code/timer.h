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
#include "main.h"
#include "number.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CTimer : public CObject
{
public:
	CTimer(int nPriority = 7);	// コンストラクタ
	~CTimer();	// デストラクタ

	// メンバ関数
	static CTimer* Create();	// 生成

	HRESULT Init();
	void Uninit();
	void Update();

	void Minutes();
	void Second();
	void MilliSecond();

	static CTimer* GetInstance() { return s_pTimer; }	// 自身の情報取得

private:
	//メンバ変数
	float m_fSecond;			// 現在の時間(秒)
	float m_fMilli;				// 現在の時間(ミリ秒)

	CNumber* m_pMinutes;		// 分表示のポインタ
	CNumber* m_pSecond;			// 秒表示のポインタ
	CNumber* m_pMilli;			// ミリ秒表示のポインタ

	static CTimer* s_pTimer;	// 自身のポインタ
};

#endif
