//*****************************************************
//
// エネミーの処理[enemy.h]
// Author:大原怜将
//
//*****************************************************
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************
// インクルード
//*****************************************************
#include "motion.h"

//*****************************************************
// 前方定義
//*****************************************************
class CCutMullSpline;

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemy : public CMotion
{
public:
	CEnemy(int nPriority = 4);	// コンストラクタ
	~CEnemy();	                // デストラクタ

	HRESULT Init(void);         // 初期化処理
	void Uninit(void);          // 終了処理
	void Update(void);          // 更新処理
	void Draw(void);            // 描画処理
	static CEnemy* Create();    // 生成処理

private:
	enum STATE
	{// 状態
		STATE_NONE = 0,	         // 何でもない状態
		STATE_NORMAL,	         // 通常状態
		STATE_MAX
	};
	
	struct SInfo
	{// 情報
		STATE state;             // 状態
		float fRate;            // スプラインの割合
	};

	// メンバ関数
	void CalcSpeed(void);	// スピードの計算
	void InterpolatePosition(void);	// 位置の補間
	void Debug(void);	// デバッグ表示

	// メンバ変数
	SInfo m_Info;                     // 情報
	static CEnemy *m_pEnemy;          // 自分自身のポインタ
	CCutMullSpline *m_pSpline;	      // スプライン
	std::vector<D3DXVECTOR3> m_vPos;  // データ点のベクター
	int m_nIdx = 1;	// スプラインの番号
	float m_fSpeed = 0.0f;	// 速度
	float m_fSpeedDefault;	// 基準にする速度
	float m_fRateOld = 0.0f;	// 前回のスプラインの割合
};

#endif