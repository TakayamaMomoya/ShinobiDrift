//*****************************************************
//
// エネミービヘイビア[enemyBehaviour.h]
// Author:大原怜将
//
//*****************************************************
#ifndef _ENEMYBEHAVIOUR_H_
#define _ENEMYBEHAVIOUR_H_

//*****************************************************
// インクルード
//*****************************************************

//*****************************************************
// 前方定義
//*****************************************************
class CEnemy;

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyBehaviour
{// ビヘイビアの基底クラス
public:
	CEnemyBehaviour() {};	// コンストラクタ
	virtual ~CEnemyBehaviour() {};	 // デストラクタ

	// メンバ変数
	virtual void Init(CEnemy *pEnemy) = 0;	// 初期化処理
	virtual void Uninit(CEnemy *pEnemy) = 0;	// 終了処理
	virtual void Update(CEnemy *pEnemy) = 0;	// 更新処理

private:
};

class CEnemyBehaviourChasePlayer : public CEnemyBehaviour
{// プレイヤーの追跡
	CEnemyBehaviourChasePlayer();	// コンストラクタ
	virtual ~CEnemyBehaviourChasePlayer();	 // デストラクタ

	// メンバ変数
	void Init(CEnemy *pEnemy) override;	// 初期化処理
	void Uninit(CEnemy *pEnemy) override;	// 終了処理
	void Update(CEnemy *pEnemy) override;	// 更新処理
};

#endif