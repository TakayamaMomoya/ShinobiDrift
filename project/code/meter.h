//*****************************************************
//
// メーター[meter.h]
// Author:森川駿弥
//
//*****************************************************

#ifndef _METER_H_
#define _METER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "number.h"
#include "player.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define MAX_PLACE	(10)	// 最大桁数

//*****************************************************
// クラスの定義
//*****************************************************
class CMeter : public CObject
{
public:
	CMeter(int nPriority = 7);	// コンストラクタ
	~CMeter();	//	デストラクタ

	// メンバ関数
	static CMeter* Create();	// 生成

	HRESULT Init();
	void Uninit();
	void Update();
	void Acceleration();

	// メーターの取得
	int GetMeter() { return m_NowMeter; }

	static CMeter* GetInstance() { return m_pMeter; }

private:
	//メンバ変数
	int m_NowMeter;		// 現在のメーター値
	int m_nCntMeter;	// カウント加算
	CNumber* m_pNumber;	// ナンバーのポインタ
	CPlayer* m_pPlayer;	// プレイヤーのポインタ
	static CMeter* m_pMeter;	// 自身のポインタ
};

#endif
