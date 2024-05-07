//*****************************************************
//
// 花の処理[flower.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _FLOWER_H_
#define _FLOWER_H_

#include "ObjectX.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CCollisionSphere;

//*****************************************************
// クラスの定義
//*****************************************************
class CFlower : public CObjectX
{
public:
	CFlower(int nPriority = 3);	// コンストラクタ
	~CFlower();	// デストラクタ

	static CFlower *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(float fDamage);
	void SetPosition(D3DXVECTOR3 pos);

private:
	void DeleteCollision(void);

	static int m_nNumAll;	// 総数
	CCollisionSphere *m_pCollisionSphere;	// 球の当たり判定
};

#endif
