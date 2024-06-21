//*****************************************************
//
// ゴール処理[goal.h]
// Author:森川駿弥
//
//*****************************************************

#ifndef _GOAL_H_
#define _GOAL_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "player.h"
#include "object3D.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CGoal : public CObject
{
public:
	CGoal(int nPriority = 7);	// コンストラクタ
	~CGoal();	//	デストラクタ

	// メンバ関数
	static CGoal* Create();	// 生成

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	float GetRotation() { return m_fRot; }	// 向き取得処理

private:
	//メンバ変数
	int m_nTransitionTime;		// 遷移時間

	D3DXVECTOR3 m_pos;		// 位置
	float m_fPosX;		// X座標
	float m_fPosZ;		// Z座標
	float m_fRot;		// 向き

	CPlayer* m_pPlayer;		// プレイヤーのポインタ
	CObject3D* m_pObj3D;	// オブジェクト3Dのポインタ
};

#endif
