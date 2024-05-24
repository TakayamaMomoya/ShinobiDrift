//*****************************************************
//
// メッシュ道の処理[meshRoad.h]
// Author:��山桃也
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
// クラスの定義
//*****************************************************
class CMeshRoad : public CObject3D
{
public:
	struct SInfoEdge
	{// 辺に必要な情報
		D3DXVECTOR3 pos;
		float fRot;
		SInfoEdge() : pos({ 0.0f,0.0f,0.0f }), fRot(0.0f) {}
	};

	CMeshRoad(int nPriority = 3);	// コンストラクタ
	~CMeshRoad();	// デストラクタ

	static CMeshRoad *Create(void);
	static CMeshRoad *GetInstance(void) { return m_pMeshRoad; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddEdge(D3DXVECTOR3 pos, float fRot,bool bReCreateVtx = false);
	void CreateVtxBuffEdge(void);	// エッジ数に応じて頂点を生成する

	void Save(void);	// エディターのみ。ゲームでは消してね
	void Load(void);	// エディターのみ。ゲームでは消してね

	std::vector<CMeshRoad::SInfoEdge>::iterator SelectEdge(void);
	std::vector<SInfoEdge> *GetList(void) { return &m_listEdge; }
	void DeleteEdge(std::vector<CMeshRoad::SInfoEdge>::iterator it);
	void ResetIterator(void);

private:
	void SetNormal(VERTEX_3D *pVtx,int nIdx);	// 法線の設定

	UINT m_nNumVtx;
	std::vector<SInfoEdge> m_listEdge;
	std::vector<SInfoEdge>::iterator m_it;
	static CMeshRoad *m_pMeshRoad;
};

namespace MeshRoad
{
CMeshRoad *GetInstance(void);
}

#endif