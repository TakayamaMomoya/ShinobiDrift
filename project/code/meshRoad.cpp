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
const char PATH_SAVE[] = "data\\MAP\\road00.bin";	// 保存ファイルのパス
const char* PATH_TEXTURE = "data\\TEXTURE\\MATERIAL\\road.jpg";	// テクスチャパス
const float DIST_DEFAULT = 200.0f;	// デフォルトの辺間の距離
const float WIDTH_ROAD = 600.0f;	// 道の幅
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CMeshRoad *CMeshRoad::m_pMeshRoad = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CMeshRoad::CMeshRoad(int nPriority) : CObject3D(nPriority), m_nNumVtx(0), m_pSpline(nullptr), m_pSplineL(nullptr), m_pSplineR(nullptr)
{

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
	m_aRoadPoint.clear();

	// テクスチャ読み込み
	int nIdx = Texture::GetIdx(PATH_TEXTURE);
	SetIdxTexture(nIdx);

	// 読み込み処理
	Load();

	m_it = m_aRoadPoint.begin();

	EnableWire(true);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CMeshRoad::Uninit(void)
{
	if (m_pSpline != nullptr)
	{
		delete m_pSpline;
		m_pSpline = nullptr;
	}

	if (m_pSplineL != nullptr)
	{
		delete m_pSplineL;
		m_pSplineL = nullptr;
	}

	if (m_pSplineR != nullptr)
	{
		delete m_pSplineR;
		m_pSplineR = nullptr;
	}

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CMeshRoad::Update(void)
{
#ifdef _DEBUG
	for (SInfoRoadPoint info : m_aRoadPoint)
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
	D3DXVECTOR3 rot = GetRotation();

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
}

//=====================================================
// ロードポイントの削除
//=====================================================
void CMeshRoad::DeleteEdge(std::vector<CMeshRoad::SInfoRoadPoint>::iterator it)
{
	m_aRoadPoint.erase(it);

	CreateVtxBuffEdge();

	m_it = m_aRoadPoint.begin();
}

//=====================================================
// イテレーターのリセット
//=====================================================
void CMeshRoad::ResetIterator(void)
{
	m_it = m_aRoadPoint.end() - 1;
}

//=====================================================
// ロードポイントの追加
//=====================================================
void CMeshRoad::AddRoadPoint(D3DXVECTOR3 pos, bool bReCreateVtx)
{
	// リストに情報を追加
	SInfoRoadPoint info;
	info.pos = pos;

	m_aRoadPoint.push_back(info);

	if (bReCreateVtx)	// ロードポイントに応じた頂点の再生成
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
	m_nNumVtx = m_aRoadPoint.size() * MeshRoad::NUM_VTX_IN_EDGE * MeshRoad::NUM_EDGE_IN_ROADPOINT;
	CreateVtxBuff(m_nNumVtx);

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	std::vector<SInfoRoadPoint>::iterator itRoadPoint;
	int nIdx = 0;

	for (itRoadPoint = m_aRoadPoint.begin(); itRoadPoint != m_aRoadPoint.end(); itRoadPoint++)
	{
		if (itRoadPoint != m_aRoadPoint.begin())
		{
			SInfoRoadPoint *pInfoRoadPointOld = &*std::prev(itRoadPoint);

			// ロードポイント間の頂点設定
			CreateVtxBetweenRoadPoint(*itRoadPoint, pVtx, pInfoRoadPointOld, nIdx);
		}

		pVtx += MeshRoad::NUM_EDGE_IN_ROADPOINT * MeshRoad::NUM_VTX_IN_EDGE;

		nIdx++;
	}

	// 頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//=====================================================
// ロードポイント間の頂点設定
//=====================================================
void CMeshRoad::CreateVtxBetweenRoadPoint(SInfoRoadPoint infoRoadPoint, VERTEX_3D *pVtx, SInfoRoadPoint *pInfoRoadPointOld, int nIdx)
{
	if (pVtx == nullptr)
		assert(("CreateVtxBetweenRoadPointで頂点情報がnullです", false));

	if (m_pSpline == nullptr)
		assert(("CreateVtxBetweenRoadPointでスプラインがnullです", false));

	D3DXVECTOR3 posEdgeOld = {};	// 前回の辺の位置

	if (pInfoRoadPointOld != nullptr)
	{
		posEdgeOld = pInfoRoadPointOld->pos;
	}

	// ロードポイント間で必要な辺
	for (int i = 0; i < MeshRoad::NUM_EDGE_IN_ROADPOINT; i++)
	{
		D3DXVECTOR3 pos = infoRoadPoint.pos;

		if (pInfoRoadPointOld == nullptr)
		{// 前回のロードポイントがない場合、分割は実質無し
			pos = m_pSpline->Interpolate(pos.x, 0);

			// 前回の辺と比べない頂点位置設定
			pVtx[0].pos = pos;
			pVtx[1].pos = pos;

			pVtx[0].pos.z -= WIDTH_ROAD;
			pVtx[1].pos.z += WIDTH_ROAD;

			posEdgeOld = GetPosEdge(pVtx[0].pos, pVtx[1].pos);	// 辺の位置を保存
		}
		else
		{
			float fDiff = infoRoadPoint.pos.x - pInfoRoadPointOld->pos.x;
			float fRate = ((float)i + 1.0f) / MeshRoad::NUM_EDGE_IN_ROADPOINT;

			// 座標の決定
			pos = m_pSpline->Interpolate(fRate, nIdx);

			pVtx[0].pos = m_pSplineL->Interpolate(fRate, nIdx);
			pVtx[1].pos = m_pSplineR->Interpolate(fRate, nIdx);

			posEdgeOld = GetPosEdge(pVtx[0].pos, pVtx[1].pos);	// 辺の位置を保存
		}

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

		pVtx += MeshRoad::NUM_VTX_IN_EDGE;	// 辺にある頂点数分ポインタを進める
	}
}

//=====================================================
// 辺の角度を設定
//=====================================================
void CMeshRoad::SetEdgeAngle(VERTEX_3D *pVtx, D3DXVECTOR3 posEdge, D3DXVECTOR3 posEdgeOld)
{
	//if (pVtx == nullptr)
	//	return;

	//// 差分ベクトルから角度を取得
	//D3DXVECTOR3 vecDiff = posEdge - posEdgeOld;
	//float fAngle = atan2f(vecDiff.x, vecDiff.z);
	//
	//fAngle += D3DX_PI * 0.5f;	// 角度を90度傾ける
	//universal::LimitRot(&fAngle);

	//// 角度から極座標で頂点位置を決定
	//D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, fAngle, 0.0f));

	//pVtx[0].pos = posEdge + vecPole * WIDTH_ROAD;
	//pVtx[1].pos = posEdge - vecPole * WIDTH_ROAD;
}

//=====================================================
// 辺の位置を取得
//=====================================================
D3DXVECTOR3 CMeshRoad::GetPosEdge(D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2)
{
	D3DXVECTOR3 vecDiff = vtx2 - vtx1;

	D3DXVECTOR3 posEdge = vtx1 + vecDiff * 0.5f;

	return posEdge;
}

//=====================================================
// 法線の設定
//=====================================================
void CMeshRoad::SetNormal(VERTEX_3D *pVtx)
{
	if (pVtx == nullptr)
		return;

	// 法線を適用
	pVtx[0].nor = { 0.0f,1.0f,0.0f };
	pVtx[1].nor = { 0.0f,1.0f,0.0f };
}

//=====================================================
// スプラインの生成
//=====================================================
void CMeshRoad::CreateSpline(void)
{
	if (m_pSpline != nullptr)
	{// スプラインが既にあったら破棄
		delete m_pSpline;
		m_pSpline = nullptr;
	}

	m_pSpline = new CCutMullSpline;

	if (m_pSpline != nullptr)
	{
		// データ点のベクター用意
		std::vector<D3DXVECTOR3> vPos;

		// ベクターを必要なサイズに調整
		int nSize = m_aRoadPoint.size();
		vPos.resize(nSize);

		for (int i = 0; i < nSize; i++)
		{
			vPos[i] = m_aRoadPoint[i].pos;
		}

		// 中心スプラインの初期化
		m_pSpline->Init(vPos);

		// 左右のスプラインの生成
		CreateSideSpline();
	}
}

//=====================================================
// 左右のスプライン生成
//=====================================================
void CMeshRoad::CreateSideSpline(void)
{
	if (m_pSpline == nullptr)
		return;

	int nSize = m_aRoadPoint.size();

	std::vector<D3DXVECTOR3> aPosL;
	std::vector<D3DXVECTOR3> aPosR;

	for (int i = 0; i < nSize; i++)
	{
		D3DXVECTOR3 posL;
		D3DXVECTOR3 posR;

		if (i == 0)
		{// 最初のスプラインの設定
			// 次回のデータ点との差分ベクトルから側面のデータ点を算出
			D3DXVECTOR3 vecDiff = m_aRoadPoint[i + 1].pos - m_aRoadPoint[i].pos;

			float fAngle = atan2f(vecDiff.x, vecDiff.z);

			fAngle += D3DX_PI * 0.5f;	// 角度を90度傾ける
			universal::LimitRot(&fAngle);

			// 角度から極座標で頂点位置を決定
			D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, fAngle, 0.0f));

			posL = m_aRoadPoint[i].pos + vecPole * m_aRoadPoint[i].fWidth;
			posR = m_aRoadPoint[i].pos - vecPole * m_aRoadPoint[i].fWidth;
		}
		else if (i == nSize - 1)
		{// 最後のスプラインの設定
			// 前回のデータ点との差分ベクトルから側面のデータ点を算出
			D3DXVECTOR3 vecDiff = m_aRoadPoint[i].pos - m_aRoadPoint[i - 1].pos;

			float fAngle = atan2f(vecDiff.x, vecDiff.z);

			fAngle += D3DX_PI * 0.5f;	// 角度を90度傾ける
			universal::LimitRot(&fAngle);

			// 角度から極座標で頂点位置を決定
			D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, fAngle, 0.0f));

			posL = m_aRoadPoint[i].pos + vecPole * m_aRoadPoint[i].fWidth;
			posR = m_aRoadPoint[i].pos - vecPole * m_aRoadPoint[i].fWidth;
		}
		else
		{// 中間のスプラインの設定
			// 判断用のカーブ角度計算
			D3DXVECTOR3 vecDiffNext = m_aRoadPoint[i + 1].pos - m_aRoadPoint[i].pos;
			D3DXVECTOR3 vecDiffPrev = m_aRoadPoint[i - 1].pos - m_aRoadPoint[i].pos;

			float fDot = universal::Vec3Dot(vecDiffNext, vecDiffPrev);

			if (fDot < m_aRoadPoint[i].fWidth)
			{// 緩やかなカーブの場合
				// 前回のデータ点との差分ベクトルから側面のデータ点を算出
				D3DXVECTOR3 vecDiff = m_aRoadPoint[i].pos - m_aRoadPoint[i - 1].pos;

				float fAngle = atan2f(vecDiff.x, vecDiff.z);

				fAngle += D3DX_PI * 0.5f;	// 角度を90度傾ける
				universal::LimitRot(&fAngle);

				// 角度から極座標で頂点位置を決定
				D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, fAngle, 0.0f));

				posL = m_aRoadPoint[i].pos + vecPole * m_aRoadPoint[i].fWidth;
				posR = m_aRoadPoint[i].pos - vecPole * m_aRoadPoint[i].fWidth;
			}
			else
			{// 角度がしきい値を超えた急カーブだったら
				// 前回のデータ点と次回のデータ点と自身の位置からできる三角形の中心座標
				D3DXVECTOR3 posMid = (m_aRoadPoint[i].pos + m_aRoadPoint[i + 1].pos + m_aRoadPoint[i - 1].pos) / 3;

				// 道幅に正規化
				D3DXVECTOR3 vecDiff = posMid - m_aRoadPoint[i].pos;

				D3DXVec3Normalize(&vecDiff, &vecDiff);

				vecDiff *= m_aRoadPoint[i].fWidth;

				bool bCross = universal::IsCross(m_aRoadPoint[i + 1].pos, m_aRoadPoint[i - 1].pos, posMid, nullptr);

				if (bCross)
				{
					posL = m_aRoadPoint[i].pos + vecDiff;
					posR = m_aRoadPoint[i].pos - vecDiff;
					posR.y = m_aRoadPoint[i].pos.y;	// 高さは合わせる
				}
				else
				{
					posL = m_aRoadPoint[i].pos - vecDiff;
					posR = m_aRoadPoint[i].pos + vecDiff;
					posR.y = m_aRoadPoint[i].pos.y;	// 高さは合わせる
				}
			}
		}

		aPosL.push_back(posL);
		aPosR.push_back(posR);
	}

	m_pSplineL = new CCutMullSpline;
	m_pSplineR = new CCutMullSpline;

	if (m_pSplineL != nullptr && m_pSplineR != nullptr)
	{
		m_pSplineL->Init(aPosL);
		m_pSplineR->Init(aPosR);
	}
}

//=====================================================
// 当たり判定処理
//=====================================================
bool CMeshRoad::CollisionRoad(D3DXVECTOR3* pPos, D3DXVECTOR3 posOld)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	VERTEX_3D* pVtx;
	float fHeight = pPos->y;
	float fHeightDef = pPos->y;
	bool bColRoad = false;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int effectNum = 0;

	for (auto itRoadPoint : m_aRoadPoint)
	{
		for (int i = 0; i < MeshRoad::NUM_EDGE_IN_ROADPOINT; i++)
		{
			// ポリゴンの上に乗っているか判定する
			if (universal::IsOnPolygon(pVtx[0].pos, pVtx[1].pos, pVtx[2].pos, pVtx[3].pos, pVtx[0].nor, pVtx[3].nor, *pPos, posOld, fHeight))
			{// 当たっていたら

				if (fHeightDef > fHeight || !bColRoad)
				{
					fHeightDef = fHeight;
				}

				bColRoad = true;
			}
			
#ifdef _DEBUG
			// デバッグ用のエフェクト
			if (m_effectNum == effectNum)
			{
				CEffect3D::Create(pVtx[0].pos, 50.0f, 5, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));
				CEffect3D::Create(pVtx[1].pos, 50.0f, 5, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f));
				CEffect3D::Create(pVtx[2].pos, 50.0f, 5, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f));
				CEffect3D::Create(pVtx[3].pos, 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

				CEffect3D::Create(pVtx[0].pos + (pVtx[0].nor * 50.0f), 50.0f, 5, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));
				CEffect3D::Create(pVtx[1].pos + (pVtx[1].nor * 50.0f), 50.0f, 5, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f));
				CEffect3D::Create(pVtx[2].pos + (pVtx[2].nor * 50.0f), 50.0f, 5, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f));
				CEffect3D::Create(pVtx[3].pos + (pVtx[3].nor * 50.0f), 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
			effectNum++;
#endif

			pVtx += MeshRoad::NUM_VTX_IN_EDGE;
		}
	}

	pPos->y = fHeightDef;

	// 頂点バッファをアンロック
	pVtxBuff->Unlock();

	return bColRoad;
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
	size_t size = m_aRoadPoint.size();
	outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

	// リストの情報保存
	outputFile.write(reinterpret_cast<char*>(m_aRoadPoint.data()), sizeof(SInfoRoadPoint) * size);

	outputFile.close();
}

//=====================================================
// 読み込み処理
//=====================================================
void CMeshRoad::Load(void)
{
	m_aRoadPoint.clear();

	// ファイルを開く
	std::ifstream inputFile(PATH_SAVE, std::ios::binary);

	if (!inputFile.is_open())
		assert(("メッシュロードのファイルを開けませんでした", false));

	// データ数読み込み
	size_t size;
	inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
	m_aRoadPoint.resize(size);

	for (auto it : m_aRoadPoint)
	{// 道幅のリセット
		it.fWidth = WIDTH_ROAD;
	}

	// 辺データ読み込み
	inputFile.read(reinterpret_cast<char*>(m_aRoadPoint.data()), sizeof(SInfoRoadPoint) * size);

	inputFile.close();

	CreateVtxBuffEdge();
}

namespace MeshRoad
{
CMeshRoad *GetInstance(void)
{
	CMeshRoad *pMeshRoad = CMeshRoad::GetInstance();

	if (pMeshRoad == nullptr)
		assert(("meshroadがないよ〜〜", false));

	return pMeshRoad;
}
}