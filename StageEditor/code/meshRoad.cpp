//*****************************************************
//
// メッシュ道の処理[meshRoad.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "meshRoad.h"
#include "renderer.h"
#include "texture.h"
#include "effect3D.h"
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

	// テクスチャ読み込み
	int nIdx = Texture::GetIdx(PATH_TEXTURE);
	SetIdxTexture(nIdx);

	// 読み込み処理
	Load();

	m_it = m_listEdge.begin();

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
	LPDIRECT3DTEXTURE9 pTexture = Texture::GetTexture(nIdxTexture);
	pDevice->SetTexture(0, pTexture);

	// 描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_nNumVtx - 2);
}

//=====================================================
// 辺の選択
//=====================================================
std::vector<CMeshRoad::SInfoEdge>::iterator CMeshRoad::SelectEdge(void)
{
	if (ImGui::Button("NextEdge", ImVec2(70, 30)))
	{
		if(m_it != m_listEdge.end() && std::next(m_it) != m_listEdge.end())
			std::advance(m_it, 1);
	}
	if (ImGui::Button("PrevEdge", ImVec2(70, 30)))
	{
		if (m_it != m_listEdge.begin())
			std::advance(m_it, -1);
	}

	return m_it;
}

//=====================================================
// 辺の削除
//=====================================================
void CMeshRoad::DeleteEdge(std::vector<CMeshRoad::SInfoEdge>::iterator it)
{
	m_listEdge.erase(it);

	CreateVtxBuffEdge();

	m_it = m_listEdge.begin();
}

//=====================================================
// イテレーターのリセット
//=====================================================
void CMeshRoad::ResetIterator(void)
{
	m_it = m_listEdge.begin();
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

	// 最初のテクスチャ座標設定
	pVtx[0].tex = { 0.0f,0.0f };
	pVtx[1].tex = { 1.0f,0.0f };

	float fRateUp = 0.0f;
	float fRateDown = 0.0f;

	// 頂点位置を辺に合わせる
	int nCntEdge = 0;
	for (const auto& edge : m_listEdge)
	{
		int nIdx = nCntEdge * NUM_VTX_IN_EDGE;	// 頂点の番号計算

		// 頂点位置の計算
		D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, edge.fRot, 0.0f));

		pVtx[nIdx].pos = edge.pos + vecPole * WIDTH_DEFAULT;
		pVtx[nIdx + 1].pos = edge.pos - vecPole * WIDTH_DEFAULT;

		// 法線の計算
		if (nCntEdge != 0)
		{// 最初の辺以外を設定する
			SetNormal(pVtx, nIdx);
		}

		// テクスチャ座標の設定
		if (nCntEdge > 0)
		{// 最初の辺以外はテクスチャ座標を足していく
			// デフォルトの距離をもとに前回の辺からどのくらい離れているか計算
			int nIdxOld = nIdx - NUM_VTX_IN_EDGE;	// ひとつ前の辺の頂点番号

			// 頂点位置
			D3DXVECTOR3 vtxLu = pVtx[nIdxOld].pos;
			D3DXVECTOR3 vtxLd = pVtx[nIdxOld + 1].pos;
			D3DXVECTOR3 vtxRu = pVtx[nIdx].pos;
			D3DXVECTOR3 vtxRd = pVtx[nIdx + 1].pos;

			// 上下の辺の長さを計算
			D3DXVECTOR3 vecDiffUp = vtxLu - vtxRu;
			D3DXVECTOR3 vecDiffDown = vtxLd - vtxRd;
			float fDistUp = D3DXVec3Length(&vecDiffUp);
			float fDistDown = D3DXVec3Length(&vecDiffDown);

			fRateUp += fDistUp / DIST_DEFAULT;
			fRateDown += fDistDown / DIST_DEFAULT;

			pVtx[nIdx].tex = { 0.0f,fRateUp };
			pVtx[nIdx + 1].tex = { 1.0f,fRateDown };
		}
		else
		{// 奇数の時
		}

		nCntEdge++;
	}

	// 最初の辺と二番目の辺の法線を合わせる
	pVtx[0].nor = pVtx[NUM_VTX_IN_EDGE].nor;
	pVtx[1].nor = pVtx[NUM_VTX_IN_EDGE + 1].nor;

	// 頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//=====================================================
// 法線の設定
//=====================================================
void CMeshRoad::SetNormal(VERTEX_3D *pVtx, int nIdx)
{
	if (pVtx == nullptr)
		return;

	int nIdxOld = nIdx - NUM_VTX_IN_EDGE;	// ひとつ前の辺の頂点番号

	// 頂点位置
	D3DXVECTOR3 vtxLu = pVtx[nIdxOld].pos;
	D3DXVECTOR3 vtxRu = pVtx[nIdx].pos;
	D3DXVECTOR3 vtxRd = pVtx[nIdx + 1].pos;

	// 頂点どうしの差分ベクトルから辺を算出
	D3DXVECTOR3 edge1 = vtxLu - vtxRu;
	D3DXVECTOR3 edge2 = vtxRd - vtxRu;

	// 二辺の外積から法線を算出
	D3DXVECTOR3 nor;
	D3DXVec3Cross(&nor, &edge1, &edge2);

	D3DXVec3Normalize(&nor, &nor);	// 法線を正規化

	// 法線を適用
	pVtx[nIdx].nor = nor;
	pVtx[nIdx + 1].nor = nor;
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
	size_t size = m_listEdge.size();
	outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

	// リストの情報保存
	outputFile.write(reinterpret_cast<const char*>(m_listEdge.data()), sizeof(SInfoEdge) * size);

	outputFile.close();
}

//=====================================================
// 読み込み処理
//=====================================================
void CMeshRoad::Load(void)
{
	m_listEdge.clear();

	// ファイルを開く
	std::ifstream inputFile(PATH_SAVE, std::ios::binary);

	if (!inputFile.is_open())
		assert(("メッシュロードのファイルを開けませんでした", false));

	// データ数読み込み
	size_t size;
	inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
	m_listEdge.resize(size);

	// 辺データ読み込み
	inputFile.read(reinterpret_cast<char*>(m_listEdge.data()), sizeof(SInfoEdge) * size);

	inputFile.close();

	CreateVtxBuffEdge();
}

namespace MeshRoad
{
CMeshRoad *GetInstance(void)
{
	CMeshRoad *pMeshRoad = CMeshRoad::GetInstance();

	if (pMeshRoad == nullptr)
		assert("meshroadがないよ～～", false);

	return pMeshRoad;
}
}