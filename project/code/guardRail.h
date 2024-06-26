//*****************************************************
//
// ガードレールの処理[guardRail.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _GUARDRAIL_H_	// 二重インクルード防止
#define _GUARDRAIL_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object3D.h"
#include "meshRoad.h"

//*****************************************************
// クラス定義
//*****************************************************
class CGuardRail : public CObject3D
{
public:
	CGuardRail(int nPriority = 5);	// コンストラクタ
	~CGuardRail();	// デストラクタ

	// メンバ変数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 変数取得・設定関数
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator GetItStart(void) { return m_itStart; }	// 開始イテレーター
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator GetItEnd(void) { return m_itEnd; }	// 終了イテレーター
	bool IsLeft(void) { return m_bLeft; }	// 左にするかどうか
	void EnableLeft(bool bLeft) { m_bLeft = bLeft; }

	bool CollideGuardRail(D3DXVECTOR3* pos, D3DXVECTOR3 vecAxial);

	// 静的メンバ関数
	static CGuardRail *Create(std::vector<CMeshRoad::SInfoRoadPoint>::iterator itStart, std::vector<CMeshRoad::SInfoRoadPoint>::iterator itEnd,bool bLeft = false,float fHeight = 600.0f);

private:
	// メンバ関数
	void CreateVtx(void);	// 頂点の生成
	void VtxFollowRoad(void);	// 頂点を道に沿わせる
	void SetNormal(VERTEX_3D *pVtx);	// 法線の設定

	// メンバ変数
	int m_nNumVtx;	// 頂点数
	float m_fHeight;	// 高さ
	bool m_bLeft;	// 左側にするかどうか
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator m_itStart;	// 開始イテレイター
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator m_itEnd;	// 終了イテレイター
};
#endif