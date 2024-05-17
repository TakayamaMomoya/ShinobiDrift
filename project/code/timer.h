//*****************************************************
//
//タイムの処理[timer.h]
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
// マクロ定義
//*****************************************************
#define MAX_PLACE	(10)	// 最大桁数

//*****************************************************
// クラスの定義
//*****************************************************
class CTimer : public CObject
{
public:
	// メンバ関数
	CTimer(int nPriority = 7);
	~CTimer();	//	デストラクタ

	//敵生成
	static CTimer* Create();

	HRESULT Init();
	void Uninit();
	void Update();
	void Set();
	void Sub(int nTime) { m_nSeconds -= nTime; }

private:
	//メンバ変数
	int m_nSeconds;		// 現在の時間
	int m_nCntSeconds;	// カウント加算
	CNumber* m_pNumber;	// ナンバーのポインタ
};
#endif