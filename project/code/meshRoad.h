//*****************************************************
//
// メッシュ道の処理[meshRoad.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _MESHROAD_H_
#define _MESHROAD_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "object3D.h"
#include <vector>

//*****************************************************
// 前方定義
//*****************************************************
class CCutMullSpline;
class CTunnel;

//*****************************************************
// クラスの定義
//*****************************************************
class CMeshRoad : public CObject3D
{
public:
	struct SInfoRoadPoint
	{// 辺に必要な情報
		D3DXVECTOR3 pos;
		float fWidth;
		SInfoRoadPoint() : pos({ 0.0f,0.0f,0.0f }) {}
	};

	CMeshRoad(int nPriority = 3);	// コンストラクタ
	~CMeshRoad();	// デストラクタ

	static CMeshRoad *Create(void);
	static CMeshRoad *GetInstance(void) { return m_pMeshRoad; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddRoadPoint(D3DXVECTOR3 pos,bool bReCreateVtx = false);
	void CreateVtxBuffEdge(void);	// エッジ数に応じて頂点を生成する

	bool CollisionRoad(D3DXVECTOR3* pPos, D3DXVECTOR3 posOld);
	bool CollisionRoadSide(D3DXVECTOR3* pPos, D3DXVECTOR3 posOld);

	void Save(void);	// エディターのみ。ゲームでは消してね
	void Load(void);	// エディターのみ。ゲームでは消してね

	std::vector<CMeshRoad::SInfoRoadPoint>::iterator SelectRoadPoint(void);
	std::vector<SInfoRoadPoint> *GetList(void) { return &m_aRoadPoint; }
	std::vector<CTunnel*> *GetArrayTunnnel(void) { return &m_aTunnel; }
	void DeleteRoadPoint(std::vector<CMeshRoad::SInfoRoadPoint>::iterator it);
	void ResetIterator(void);

private:
	void SetNormal(VERTEX_3D *pVtx);	// 法線の設定
	void CreateSpline(void);	// スプラインの生成
	void CreateSideSpline(void);	// 側面のスプライン生成
	void CreateVtxBetweenRoadPoint(SInfoRoadPoint infoRoadPoint, VERTEX_3D *pVtx, SInfoRoadPoint *infoRoadPointOld = nullptr, int nIdx = 0);	// ロードポイント間の頂点の設定
	void SetEdgeAngle(VERTEX_3D *pVtx, D3DXVECTOR3 posEdge, D3DXVECTOR3 posEdgeOld);	// 辺の角度の設定
	D3DXVECTOR3 GetPosEdge(D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2);

	UINT m_nNumVtx;
	std::vector<SInfoRoadPoint> m_aRoadPoint;
	std::vector<SInfoRoadPoint>::iterator m_it;
	CCutMullSpline *m_pSpline;	// スプライン
	CCutMullSpline *m_pSplineL;	// 左側のスプライン
	CCutMullSpline *m_pSplineR;	// 右側のスプライン
	std::vector<CTunnel*> m_aTunnel;	// トンネルのポインタの配列

	static CMeshRoad *m_pMeshRoad;
};

namespace MeshRoad
{
const int NUM_EDGE_IN_ROADPOINT = 20;	// ロードポイント一つにつき、ある辺の数
const int NUM_VTX_IN_EDGE = 2;	// 一辺にある頂点数

CMeshRoad *GetInstance(void);
}

#endif