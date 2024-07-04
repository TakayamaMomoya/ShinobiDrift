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

	static CTimer* GetInstance() { return m_pTimer; }	// 自身の情報取得

private:
	//メンバ変数
	float m_fSeconds;		// 現在の時間
	CNumber* m_pNumber;	// ナンバーのポインタ

	static CTimer* m_pTimer;	// 自身のポインタ
};
#endif
