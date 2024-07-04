//*****************************************************
//
// エネミーの処理[enemy.h]
// Author:大原怜将
//
//*****************************************************

#ifndef _CAR_H_
#define _CAR_H_

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

	// 状態
	enum STATE
	{
		STATE_NONE = 0,	         // 何でもない状態
		STATE_NORMAL,	         // 通常状態
		STATE_MAX
	};

	// 情報
	struct SInfo
	{
		STATE state;             // 状態
		float fSpeed;            // 速さ
	};

	SInfo m_Info;                     // 情報
	static CEnemy *m_pEnemy;          // 自分自身のポインタ
	CMotion* m_pEnemyNinja;           // バイクに乗っている忍者
	CCutMullSpline *m_pSpline;	      // スプライン
	std::vector<D3DXVECTOR3> m_vPos;  // データ点のベクター

	int m_nIdx = 1;
	int m_nSize = 0;
	float m_t = 0.0f;
};

#endif