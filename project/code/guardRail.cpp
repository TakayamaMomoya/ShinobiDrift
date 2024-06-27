//*****************************************************
//
// ガードレールの処理[guardRail.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "guardRail.h"
#include "texture.h"
#include "effect3D.h"
#include "renderer.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const char* TEX_PATH = "data\\TEXTURE\\MATERIAL\\wall00.jpeg";	// テクスチャパス
const int NUM_VTX_ON_POINT = 2;	// メッシュロードの頂点上にある頂点数
const float HEIGHT_GR = 600.0f;	// ガードレールの高さ
const int NUMVTX_NOTDRAW = 4;	// この頂点数未満の場合、描画しない
}

//=====================================================
// コンストラクタ
//=====================================================
CGuardRail::CGuardRail(int nPriority) : CObject3D(nPriority), m_nNumVtx(0), m_fHeight(0.0f), m_bLeft(false)
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
CGuardRail *CGuardRail::Create(std::vector<CMeshRoad::SInfoRoadPoint>::iterator itStart, std::vector<CMeshRoad::SInfoRoadPoint>::iterator itEnd, bool bLeft, float fHeight)
{
	CGuardRail *pGuardRail = nullptr;

	pGuardRail = new CGuardRail;

	if (pGuardRail != nullptr)
	{
		pGuardRail->m_fHeight = fHeight;
		pGuardRail->m_bLeft = bLeft;
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

#ifdef _DEBUG
	EnableWire(true);
#endif // _DEBUG

	return S_OK;
}

//=====================================================
// 頂点の生成
//=====================================================
void CGuardRail::CreateVtx(void)
{
	int nDistIt = std::distance(m_itStart, m_itEnd);
	m_nNumVtx = nDistIt * NUM_VTX_ON_POINT * MeshRoad::NUM_EDGE_IN_ROADPOINT;

	// 頂点生成
	CreateVtxBuff(m_nNumVtx);

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
			CEffect3D::Create(pVtx[m_bLeft].pos, 20.0f, 3, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

			vectorPosEdge.push_back(pVtx[m_bLeft].pos);

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

	for (size_t i = 0; i < vectorPosEdge.size(); i++)
	{
		// 位置の決定
		pVtx[0].pos = vectorPosEdge[i];
		pVtx[1].pos = pVtx[0].pos;

		pVtx[1].pos.y += m_fHeight;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 法線の設定
		if (i > 0)
		{
			SetNormal(pVtx);
		}

		if (i == 1)
		{
			pVtx[-2].nor = pVtx[0].nor;
			pVtx[-1].nor = pVtx[1].nor;

			CEffect3D::Create(pVtx[-2].pos + pVtx[-2].nor * 200.0f, 50.0f, 200000, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			CEffect3D::Create(pVtx[-1].pos + pVtx[-1].nor * 200.0f, 50.0f, 200000, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

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

		CEffect3D::Create(pVtx[0].pos + pVtx[0].nor * 200.0f, 50.0f, 20000, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		CEffect3D::Create(pVtx[1].pos + pVtx[1].nor * 200.0f, 50.0f, 20000, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		pVtx += NUM_VTX_ON_POINT;
	}

	// 頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//=====================================================
// 法線の設定
//=====================================================
void CGuardRail::SetNormal(VERTEX_3D *pVtx)
{
	if (pVtx == nullptr)
		return;

	// 頂点位置
	D3DXVECTOR3 vtxLu = pVtx[-MeshRoad::NUM_VTX_IN_EDGE].pos;
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
// 当たり判定処理
//=====================================================
bool CGuardRail::CollideGuardRail(D3DXVECTOR3* pos, D3DXVECTOR3 vecAxial)
{
	bool bCollision = false;

	// 頂点バッファ取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点数の計算
	int size = CMeshRoad::GetInstance()->GetList()->size() * MeshRoad::NUM_EDGE_IN_ROADPOINT;
	for (int i = 0; i < size; i++)
	{
		// ガードレールの高さ以内で判定する
		if (m_fHeight < pos->y - pVtx[0].pos.y)
			continue;

		if (D3DXVec3Dot(&(*pos - pVtx[0].pos), &(pVtx[2].pos - pVtx[0].pos)) < 0.0f &&
			D3DXVec3Dot(&(*pos - pVtx[2].pos), &(pVtx[0].pos - pVtx[2].pos)) >= 0.0f)
			continue;

		if (universal::CollideOBBToPlane(pos, vecAxial, pVtx[0].pos, pVtx[0].nor))
		{
			bCollision = true;
			break;
		}

		pVtx += NUM_VTX_ON_POINT;
	}

	// 頂点バッファをアンロック
	pVtxBuff->Unlock();

	return bCollision;
}