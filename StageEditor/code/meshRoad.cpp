//*****************************************************
//
// メッシュ道の処理[meshRoad.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "meshRoad.h"
#include "renderer.h"
#include "texture.h"
#include "effect3D.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const UINT NUMVTX_NOTDRAW = 4;	// この頂点数未満の場合、描画しない
const float WIDTH_DEFAULT = 200.0f;	// デフォルトの幅
const float LENGTH_DEFAULT = 200.0f;	// デフォルトの長さ
const int NUM_VTX_IN_EDGE = 2;	// 一辺にある頂点数
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CMeshRoad *CMeshRoad::m_pMeshRoad = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CMeshRoad::CMeshRoad(int nPriority) : CObject3D(nPriority)
{
	m_nNumVtx = 0;
}

//=====================================================
// デストラクタ
//=====================================================
CMeshRoad::~CMeshRoad()
{

}

//=====================================================
// 生成処理
//=====================================================
CMeshRoad *CMeshRoad::Create(void)
{
	CMeshRoad *pMeshRoad = nullptr;

	if (pMeshRoad == nullptr)
	{
		// インスタンス生成
		pMeshRoad = new CMeshRoad;

		if (pMeshRoad != nullptr)
		{
			// 初期化処理
			pMeshRoad->Init();

			m_pMeshRoad = pMeshRoad;
		}
	}

	return pMeshRoad;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CMeshRoad::Init(void)
{
	// リストの初期化
	m_listEdge.clear();

	m_nNumVtx = 4;

	AddEdge(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, true);
	AddEdge(D3DXVECTOR3(100.0f, 0.0f, 500.0f), 0.0f, true);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CMeshRoad::Uninit(void)
{
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CMeshRoad::Update(void)
{

}

//=====================================================
// 描画処理
//=====================================================
void CMeshRoad::Draw(void)
{
	if (m_nNumVtx < NUMVTX_NOTDRAW)	// 描画制限
		return;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	D3DXMATRIX *pMtx = GetMatrix();

	// ワールドマトリックス初期化
	D3DXMatrixIdentity(pMtx);

	D3DXMATRIX mtxRot, mtxTrans;
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRot();

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxTrans);

	// ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, pMtx);

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャ設定
	int nIdxTexture = GetIdxTexture();
	LPDIRECT3DTEXTURE9 pTexture = CTexture::GetInstance()->GetAddress(nIdxTexture);
	pDevice->SetTexture(0, pTexture);

	// カリングを無効化
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_nNumVtx - 2);
}

//=====================================================
// 辺の追加
//=====================================================
void CMeshRoad::AddEdge(D3DXVECTOR3 pos, float fRot, bool bReCreateVtx)
{
	// リストに情報を追加
	SInfoEdge info;
	info.pos = pos;
	info.fRot = fRot;

	m_listEdge.push_back(info);

	if(bReCreateVtx)	// 辺に応じた頂点の再生成
		CreateVtxBuffEdge();
}

//=====================================================
// 辺に応じた頂点の生成
//=====================================================
void CMeshRoad::CreateVtxBuffEdge(void)
{
	// 頂点の生成
	m_nNumVtx = m_listEdge.size() * NUM_VTX_IN_EDGE;
	CreateVtxBuff(m_nNumVtx);

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点位置を辺に合わせる
	int nCntEdge = 0;
	for (const auto& edge : m_listEdge)
	{
		int nIdx = nCntEdge * NUM_VTX_IN_EDGE;	// 頂点の番号計算

		// 頂点位置の計算
		D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, edge.fRot, 0.0f));
		CEffect3D::Create(edge.pos + vecPole * WIDTH_DEFAULT, 50.0f, 50000, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		CEffect3D::Create(edge.pos - vecPole * WIDTH_DEFAULT, 50.0f, 50000, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		pVtx[nIdx].pos = edge.pos + vecPole * WIDTH_DEFAULT;
		pVtx[nIdx + 1].pos = edge.pos - vecPole * WIDTH_DEFAULT;

		nCntEdge++;
	}

	// 頂点バッファをアンロック
	pVtxBuff->Unlock();
}