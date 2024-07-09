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
#include "enemyBehaviour.h"

//*****************************************************
// 前方定義
//*****************************************************
class CBehaviourEnemy;

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
	};

	// メンバ関数
	void ReleaseAllBehaviour(void);	// 全てのビヘイビアの解放

	// メンバ変数
	SInfo m_Info;	// 情報
	std::list<CEnemyBehaviour*> m_listBehaviour;	// ビヘイビアのリスト
};

#endif