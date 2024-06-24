//*****************************************************
//
// トンネルの処理[tunnel.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "guardRail.h"
#include "texture.h"
#include "effect3D.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const char* TEX_PATH = "data\\TEXTURE\\MATERIAL\\concrete.jpg";	// テクスチャパス
const int NUM_VTX_ON_POINT = 2;	// メッシュロードの頂点上にある頂点数
}

//=====================================================
// コンストラクタ
//=====================================================
CGuardRail::CGuardRail(int nPriority) : CObject3D(nPriority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CGuardRail::~CGuardRail()
{

}

//=====================================================
// 生成処理
//=====================================================
CGuardRail *CGuardRail::Create(std::vector<CMeshRoad::SInfoRoadPoint>::iterator itStart, std::vector<CMeshRoad::SInfoRoadPoint>::iterator itEnd)
{
	CGuardRail *pGuardRail = nullptr;

	pGuardRail = new CGuardRail;

	if (pGuardRail != nullptr)
	{
		pGuardRail->m_itStart = itStart;
		pGuardRail->m_itEnd = itEnd;

		pGuardRail->Init();
	}

	return pGuardRail;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CGuardRail::Init(void)
{
	// 頂点生成
	CreateVtx();

	// 頂点を道に沿わせる
	VtxFollowRoad();

	return S_OK;
}

//=====================================================
// 頂点の生成
//=====================================================
void CGuardRail::CreateVtx(void)
{
	int nDistIt = std::distance(m_itStart, m_itEnd);
	int nNumVtx = nDistIt * NUM_VTX_ON_POINT;

	// 頂点生成
	CreateVtxBuff(nNumVtx);

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
void CGuardRail::VtxFollowRoad(void)
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
		nDistBetween *= MeshRoad::NUM_EDGE_IN_ROADPOINT;

		for (int i = 0; i < nDistBetween; i++)
		{
			CEffect3D::Create(pVtx[0].pos, 20.0f, 3, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

			vectorPosEdge.push_back(pVtx[0].pos);

			pVtx += 2;
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



	// 頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//=====================================================
// 終了処理
//=====================================================
void CGuardRail::Uninit(void)
{
	CObject3D::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CGuardRail::Update(void)
{
	CObject3D::Update();
}

//=====================================================
// 描画処理
//=====================================================
void CGuardRail::Draw(void)
{
	CObject3D::Draw();
}