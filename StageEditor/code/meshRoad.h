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

private:
	struct SInfoEdge
	{// 辺に必要な情報
		D3DXVECTOR3 pos;
		float fRot;
		SInfoEdge() : pos({ 0.0f,0.0f,0.0f }), fRot(0.0f) {}
	};

	UINT m_nNumVtx;
	std::vector<SInfoEdge> m_listEdge;
	static CMeshRoad *m_pMeshRoad;
};

#endif