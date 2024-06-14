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

private:
	//メンバ変数
	int m_nTransitionTime = 0;		// 遷移時間

	CPlayer* m_pPlayer;		// プレイヤーのポインタ
	CObject3D* m_pObj3D;	// オブジェクト3Dのポインタ
};

#endif
