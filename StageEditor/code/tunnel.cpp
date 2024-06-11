//*****************************************************
//
// トンネルの処理[tunnel.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "tunnel.h"
#include "texture.h"
#include "effect3D.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const int MESH_U = 16;	// 横の分割数
const float MESH_HEIGHT = 50.0f;	// メッシュの高さ
const char* TEX_PATH = "data\\TEXTURE\\MATERIAL\\concrete.jpg";	// テクスチャパス
const int NUM_VTX_IN_EDGE = 5;	// 辺の中にある頂点数
}

//=====================================================
// コンストラクタ
//=====================================================
CTunnel::CTunnel(int nPriority) : CMeshCylinder(nPriority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CTunnel::~CTunnel()
{

}

//=====================================================
// 生成処理
//=====================================================
CTunnel *CTunnel::Create(std::vector<CMeshRoad::SInfoRoadPoint>::iterator itStart, std::vector<CMeshRoad::SInfoRoadPoint>::iterator itEnd)
{
	CTunnel *pTunnel = nullptr;

	if (pTunnel == nullptr)
	{
		pTunnel = new CTunnel;

		if (pTunnel != nullptr)
		{
			pTunnel->m_itStart = itStart;
			pTunnel->m_itEnd = itEnd;

			pTunnel->Init();
		}
	}

	return pTunnel;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CTunnel::Init(void)
{
	// 頂点の生成
	CreateVtx();

	// 頂点を道に沿わせる
	VtxFollowRoad();

	return S_OK;
}

//=====================================================
// 頂点の生成
//=====================================================
void CTunnel::CreateVtx(void)
{
	int nDistStart = std::distance(m_itStart, m_itEnd);

	// 分割数設定
	int nMeshV = nDistStart * MeshRoad::NUM_EDGE_IN_ROADPOINT;

	SetNumMeshU(MESH_U);
	SetNumMeshV(nMeshV);

	// 継承クラスの初期化
	CMeshCylinder::Init();

	// 頂点位置設定
	SetVtx();

	// テクスチャの読込
	CTexture *pTexture = CTexture::GetInstance();

	if (pTexture != nullptr)
	{
		int nIdx = pTexture->Regist(TEX_PATH);
		SetIdxTexture(nIdx);
	}
}

//=====================================================
// 頂点を道に沿わせる
//=====================================================
void CTunnel::VtxFollowRoad(void)
{
	// 開始と終了までの頂点位置を保存============================
	CMeshRoad *pMesh = CMeshRoad::GetInstance();

	std::vector<D3DXVECTOR3> vectorPosEdge;

	if (pMesh != nullptr)
	{
		// 開始地点を算出
		std::vector<CMeshRoad::SInfoRoadPoint> *pList = pMesh->GetList();

		int nDistStart = std::distance(pList->begin(), m_itStart) + 1;

		LPDIRECT3DVERTEXBUFFER9 pVtxBuffRoad = pMesh->GetVtxBuff();

		// 頂点情報のポインタ
		VERTEX_3D *pVtx;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		pVtxBuffRoad->Lock(0, 0, (void**)&pVtx, 0);

		// 開始地点までポインタを進める
		pVtx += nDistStart * MeshRoad::NUM_EDGE_IN_ROADPOINT * MeshRoad::NUM_VTX_IN_EDGE;

		// 頂点数の計算
		int nDistBetween = std::distance(m_itStart, m_itEnd);
		nDistBetween *= MeshRoad::NUM_EDGE_IN_ROADPOINT * MeshRoad::NUM_VTX_IN_EDGE;

		for (int i = 0; i < nDistBetween; i++)
		{
			CEffect3D::Create(pVtx[0].pos, 200.0f, 5000, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

			vectorPosEdge.push_back(pVtx[0].pos);

			pVtx++;
		}

		// 頂点バッファをアンロック
		pVtxBuffRoad->Unlock();
	}
	else
	{
		return;
	}

	// 頂点を道に沿わせる========================================
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点情報のポインタ
	VERTEX_3D *pVtx;
	
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nMeshV = GetMeshCylinder()->nMeshV;

	for (int i = 0; i < nMeshV + 1; i++)
	{
		for (int j = 0; j < MESH_U + 1; j++)
		{
			CEffect3D::Create(pVtx[0].pos, 10.0f, 5000, D3DXCOLOR(1.0f, 1.0f - 0.1 * j, 0.0f, 1.0f));

			pVtx++;
		}
	}

	// 頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//=====================================================
// 終了処理
//=====================================================
void CTunnel::Uninit(void)
{
	CMeshCylinder::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CTunnel::Update(void)
{
	CMeshCylinder::Update();
}

//=====================================================
// 描画処理
//=====================================================
void CTunnel::Draw(void)
{
	CMeshCylinder::Draw();
}