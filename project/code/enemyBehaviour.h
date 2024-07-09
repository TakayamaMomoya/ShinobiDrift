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
class CCutMullSpline;

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyBehaviour
{// ビヘイビアの基底クラス
public:
	CEnemyBehaviour() {};	// コンストラクタ
	virtual ~CEnemyBehaviour() {};	 // デストラクタ

	// メンバ関数
	virtual void Init(CEnemy *pEnemy) = 0;	// 初期化処理
	virtual void Uninit(CEnemy *pEnemy) = 0;	// 終了処理
	virtual void Update(CEnemy *pEnemy) = 0;	// 更新処理

private:
};

class CEnemyBehaviourChasePlayer : public CEnemyBehaviour
{// プレイヤーの追跡
public:
	CEnemyBehaviourChasePlayer();	// コンストラクタ
	virtual ~CEnemyBehaviourChasePlayer();	 // デストラクタ

	// メンバ関数
	void Init(CEnemy *pEnemy) override;	// 初期化処理
	void Uninit(CEnemy *pEnemy) override;	// 終了処理
	void Update(CEnemy *pEnemy) override;	// 更新処理

private:
	// メンバ関数
	void CalcSpeed(CEnemy *pEnemy);	// スピードの計算
	void InterpolatePosition(CEnemy *pEnemy);	// 位置の補間
	void ControllRot(CEnemy *pEnemy);	// 向きの制御
	void Debug(CEnemy *pEnemy);	// デバッグ表示

	// メンバ変数
	CCutMullSpline *m_pSpline;	// スプライン
	std::vector<D3DXVECTOR3> m_vPos;	// データ点のベクター
	int m_nIdx = 1;	// スプラインの番号
	float m_fSpeed;	// 速度
	float m_fSpeedDefault;	// 基準にする速度
	float m_fRate;
	float m_fRateOld;	// 前回のスプラインの割合
};

#endif