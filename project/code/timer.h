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
#include "gameObject.h"
#include "number.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CTimer : public CGameObject
{
public:
	CTimer();	// コンストラクタ
	~CTimer();	// デストラクタ

	// メンバ関数
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

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
	// 列挙型定義
	enum E_Number
	{// 数字の種類
		NUMBER_MINUTE = 0,	// 分
		NUMBER_SECOND,	// 秒
		NUMBER_MILLI,	// ミリ秒
		NUMBER_MAX
	};

	// メンバ関数
	void UpdateNumber();	// 数字の更新

	// メンバ変数
	float m_fSecond;			// 現在の時間(秒)
	bool m_bStop;				// タイマー停止のフラグ
	vector<CNumber*> m_aNumber;	// 数字の配列
};

#endif
