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
#include "myLib.h"
#include <fstream>

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const UINT NUMVTX_NOTDRAW = 4;	// この頂点数未満の場合、描画しない
const float WIDTH_DEFAULT = 200.0f;	// デフォルトの幅
const float LENGTH_DEFAULT = 200.0f;	// デフォルトの長さ
const int NUM_VTX_IN_EDGE = 2;	// 一辺にある頂点数
const int NUM_EDGE_IN_ROADPOINT = 10;	// ロードポイント一つにつき、ある辺の数
const char PATH_SAVE[] = "data\\MAP\\road00.bin";	// 保存ファイルのパス
const char* PATH_TEXTURE = "data\\TEXTURE\\MATERIAL\\road.jpg";	// テクスチャパス
const float DIST_DEFAULT = 200.0f;	// デフォルトの辺間の距離
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
	m_pSplineXZ = nullptr;
	m_pSplineXY = nullptr;
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
	m_listRoadPoint.clear();

	// テクスチャ読み込み
	int nIdx = Texture::GetIdx(PATH_TEXTURE);
	SetIdxTexture(nIdx);

	// 読み込み処理
	Load();

	m_it = m_listRoadPoint.begin();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CMeshRoad::Uninit(void)
{
	if (m_pSplineXZ != nullptr)
	{
		delete m_pSplineXZ;
		m_pSplineXZ = nullptr;
	}

	if (m_pSplineXY != nullptr)
	{
		delete m_pSplineXY;
		m_pSplineXY = nullptr;
	}

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CMeshRoad::Update(void)
{
#ifdef _DEBUG
	for (SInfoRoadPoint info : m_listRoadPoint)
		CEffect3D::Create(info.pos, 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
#endif // _DEBUG
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
	LPDIRECT3DTEXTURE9 pTexture = Texture::GetTexture(nIdxTexture);
	pDevice->SetTexture(0, pTexture);

	// カリングを無効化
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_nNumVtx - 2);

	// カリングを有効化
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	ImGui::Text("%d", m_nNumVtx);
}

//=====================================================
// ロードポイントの選択
//=====================================================
std::vector<CMeshRoad::SInfoRoadPoint>::iterator CMeshRoad::SelectEdge(void)
{
	if (ImGui::Button("NextEdge", ImVec2(70, 30)))
	{
		if(m_it != m_listRoadPoint.end() && std::next(m_it) != m_listRoadPoint.end())
			std::advance(m_it, 1);
	}
	if (ImGui::Button("PrevEdge", ImVec2(70, 30)))
	{
		if (m_it != m_listRoadPoint.begin())
			std::advance(m_it, -1);
	}

	return m_it;
}

//=====================================================
// ロードポイントの削除
//=====================================================
void CMeshRoad::DeleteEdge(std::vector<CMeshRoad::SInfoRoadPoint>::iterator it)
{
	m_listRoadPoint.erase(it);

	CreateVtxBuffEdge();

	m_it = m_listRoadPoint.begin();
}

//=====================================================
// イテレーターのリセット
//=====================================================
void CMeshRoad::ResetIterator(void)
{
	m_it = m_listRoadPoint.begin();
}

//=====================================================
// ロードポイントの追加
//=====================================================
void CMeshRoad::AddRoadPoint(D3DXVECTOR3 pos, bool bReCreateVtx)
{
	// リストに情報を追加
	SInfoRoadPoint info;
	info.pos = pos;

	m_listRoadPoint.push_back(info);

	if(bReCreateVtx)	// ロードポイントに応じた頂点の再生成
		CreateVtxBuffEdge();
}

//=====================================================
// ロードポイントに応じた頂点の生成
//=====================================================
void CMeshRoad::CreateVtxBuffEdge(void)
{
	// スプラインの再生成
	CreateSpline();

	// 頂点の生成
	m_nNumVtx = m_listRoadPoint.size() * NUM_VTX_IN_EDGE * NUM_EDGE_IN_ROADPOINT;
	CreateVtxBuff(m_nNumVtx);

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	std::vector<SInfoRoadPoint>::iterator itRoadPoint = m_listRoadPoint.begin();

	for (itRoadPoint = m_listRoadPoint.begin(); itRoadPoint != m_listRoadPoint.end(); itRoadPoint++)
	{
		if (itRoadPoint != m_listRoadPoint.begin())
		{
			SInfoRoadPoint *pInfoRoadPointOld = &*std::prev(itRoadPoint);

			// ロードポイント間の頂点設定
			CreateVtxBetweenRoadPoint(*itRoadPoint, pVtx, pInfoRoadPointOld);
		}

		pVtx += NUM_EDGE_IN_ROADPOINT * NUM_VTX_IN_EDGE;
	}

	// 頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//=====================================================
// ロードポイント間の頂点設定
//=====================================================
void CMeshRoad::CreateVtxBetweenRoadPoint(SInfoRoadPoint infoRoadPoint, VERTEX_3D *pVtx, SInfoRoadPoint *pInfoRoadPointOld)
{
	if (pVtx == nullptr)
		assert(("CreateVtxBetweenRoadPointで頂点情報がnullです", false));

	if (m_pSplineXZ == nullptr || m_pSplineXY == nullptr)
		assert(("CreateVtxBetweenRoadPointでスプラインがnullです", false));

	// ロードポイント間で必要な辺
	for (int i = 0; i < NUM_EDGE_IN_ROADPOINT; i++)
	{
		D3DXVECTOR3 pos = infoRoadPoint.pos;

		if (pInfoRoadPointOld == nullptr)
		{// 前回のロードポイントがない場合、分割は実質無し
			float z = (float)m_pSplineXZ->Interpolate(pos.x);
			pos.z = z;
		}
		else
		{
			float fDiff = infoRoadPoint.pos.x - pInfoRoadPointOld->pos.x;
			float fRate = (float)i / NUM_EDGE_IN_ROADPOINT;

			// X座標の決定
			pos.x = pInfoRoadPointOld->pos.x + fRate * fDiff;
			
			// Y座標の決定
			float y = (float)m_pSplineXY->Interpolate(pos.x);
			pos.y = y;

			// Z座標の計算
			float z = (float)m_pSplineXZ->Interpolate(pos.x);
			pos.z = z;

			CEffect3D::Create(pos, 50.0f, 60, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));	// 中心座標のエフェクト
		}

		pVtx[0].pos = pos;
		pVtx[1].pos = pos;

		pVtx[0].pos.z -= 100.0f;	// デバッグ用、消して
		pVtx[1].pos.z += 100.0f;	// デバッグ用、消して

		// 法線の設定
		SetNormal(pVtx);

		// テクスチャ座標の設定
		if (i % 2 == 0)
		{
			pVtx[0].tex = { 0.0f,0.0f };
			pVtx[1].tex = { 1.0f,0.0f };
		}
		else
		{
			pVtx[0].tex = { 0.0f,1.0f };
			pVtx[1].tex = { 1.0f,1.0f };
		}

		pVtx += NUM_VTX_IN_EDGE;	// 辺にある頂点数分ポインタを進める
	}
}

//=====================================================
// 法線の設定
//=====================================================
void CMeshRoad::SetNormal(VERTEX_3D *pVtx)
{
	if (pVtx == nullptr)
		return;

	// 頂点位置
	D3DXVECTOR3 vtxLu = pVtx[-NUM_VTX_IN_EDGE].pos;
	D3DXVECTOR3 vtxRu = pVtx[0].pos;
	D3DXVECTOR3 vtxRd = pVtx[1].pos;

	// 頂点どうしの差分ベクトルから辺を算出
	D3DXVECTOR3 edge1 = vtxLu - vtxRu;
	D3DXVECTOR3 edge2 = vtxRd - vtxRu;

	// 二辺の外積から法線を算出
	D3DXVECTOR3 nor;
	D3DXVec3Cross(&nor, &edge1, &edge2);

	D3DXVec3Normalize(&nor, &nor);	// 法線を正規化

	// 法線を適用
	pVtx[0].nor = nor;
	pVtx[1].nor = nor;
}

//=====================================================
// スプラインの生成
//=====================================================
void CMeshRoad::CreateSpline(void)
{
	if (m_pSplineXZ != nullptr)
	{// スプラインが既にあったら破棄
		delete m_pSplineXZ;
		m_pSplineXZ = nullptr;
	}

	if (m_pSplineXY != nullptr)
	{// スプラインが既にあったら破棄
		delete m_pSplineXY;
		m_pSplineXY = nullptr;
	}

	m_pSplineXZ = new CSpline;
	m_pSplineXY = new CSpline;

	if (m_pSplineXZ != nullptr && m_pSplineXY != nullptr)
	{
		// データ点のベクター用意
		std::vector<double> x;
		std::vector<double> y;
		std::vector<double> z;

		// ベクターを必要なサイズに調整
		int nSize = m_listRoadPoint.size();
		x.resize(nSize);
		y.resize(nSize);
		z.resize(nSize);
		
		for (int i = 0; i < nSize; i++)
		{
			x[i] = m_listRoadPoint[i].pos.x;
			y[i] = m_listRoadPoint[i].pos.y;
			z[i] = m_listRoadPoint[i].pos.z;	// xz平面で計算するため、ｙにはｚ座標を代入
		}
		
		// スプラインの初期化
		m_pSplineXZ->Init(x, z);
		m_pSplineXY->Init(x, y);
	}
}

//=====================================================
// 保存処理
//=====================================================
void CMeshRoad::Save(void)
{
	// ファイルを開く
	std::ofstream outputFile(PATH_SAVE, std::ios::binary);

	if (!outputFile.is_open())
		assert(("メッシュロードのファイルを開けませんでした", false));
	
	// 情報数保存
	size_t size = m_listRoadPoint.size();
	outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

	// リストの情報保存
	outputFile.write(reinterpret_cast<const char*>(m_listRoadPoint.data()), sizeof(SInfoRoadPoint) * size);

	outputFile.close();
}

//=====================================================
// 読み込み処理
//=====================================================
void CMeshRoad::Load(void)
{
	m_listRoadPoint.clear();

	// ファイルを開く
	std::ifstream inputFile(PATH_SAVE, std::ios::binary);

	if (!inputFile.is_open())
		assert(("メッシュロードのファイルを開けませんでした", false));

	// データ数読み込み
	size_t size;
	inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
	m_listRoadPoint.resize(size);

	// 辺データ読み込み
	inputFile.read(reinterpret_cast<char*>(m_listRoadPoint.data()), sizeof(SInfoRoadPoint) * size);

	inputFile.close();

	CreateVtxBuffEdge();
}

namespace MeshRoad
{
CMeshRoad *GetInstance(void)
{
	CMeshRoad *pMeshRoad = CMeshRoad::GetInstance();

	if (pMeshRoad == nullptr)
		assert("meshroadがないよ〜〜", false);

	return pMeshRoad;
}
}