//*****************************************************
//
// プレイヤー忍者[playerNinja.cpp]
// Author:髙山桃也
//
//*****************************************************
#ifndef _PLAYERNINJA_H_
#define _PLAYERNINJA_H_

//*****************************************************
// インクルード
//*****************************************************
#include "motion.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CBlockGrab;
class CObject3D;
class CPlayerNinja;

//*****************************************************
// クラスの定義
//*****************************************************
class CPlayerNinja : public CMotion
{
public:
	CPlayerNinja(int nPriority = 4);	// コンストラクタ
	~CPlayerNinja();	// デストラクタ

	static CPlayerNinja *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Event(EVENT_INFO *pEventInfo);
	void ManagekatanaCollision(D3DXVECTOR3 pos);
};

#endif