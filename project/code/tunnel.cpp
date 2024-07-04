//*****************************************************
//
// トンネルの処理[tunnel.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "tunnel.h"
#include "texture.h"
#include "effect3D.h"
#include "player.h"
#include "debugproc.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const int MESH_U = 32;	// 横の分割数
const float MESH_HEIGHT = 50.0f;	// メッシュの高さ
const char* TEX_PATH = "data\\TEXTURE\\MATERIAL\\concrete.jpg";	// テクスチャパス
const int NUM_VTX_IN_EDGE = 5;	// 辺の中にある頂点数
}

//=====================================================
// コンストラクタ
//=====================================================
CTunnel::CTunnel(int nPriority) : CMeshCylinder(nPriority),m_bInPlayer(false)
{
	m_bInPlayer = false;
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

	pTunnel = new CTunnel;

	if (pTunnel != nullptr)
	{
		pTunnel->m_itStart = itStart;
		pTunnel->m_itEnd = itEnd;

		pTunnel->Init();
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
		std::vector<CMeshRoad::SInfoRoadPoint> *pList = pMesh->GetArrayRP();

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
		int nIdx = i * 2;

		D3DXVECTOR3 pos1;
		D3DXVECTOR3 pos2;

		if (i == nMeshV)
		{
			pos1 = vectorPosEdge[nMeshV * 2 - 2];
			pos2 = vectorPosEdge[nMeshV * 2 - 1];
		}
		else
		{
			pos1 = vectorPosEdge[nIdx];
			pos2 = vectorPosEdge[nIdx + 1];
		}

		D3DXVECTOR3 vecDiff = pos2 - pos1;

		float fWidthRoad = sqrtf(vecDiff.x * vecDiff.x + vecDiff.z * vecDiff.z) * 0.5f;

		for (int j = 0; j <= MESH_U / 2; j++)
		{
			float fRate = (float)j / (MESH_U / 2);
			
			pVtx[j].pos = pos1 + vecDiff * 0.5f * cosf(D3DX_PI * fRate) + vecDiff * 0.5f;

			float fHeight = sinf(D3DX_PI * fRate) * fWidthRoad;
			pVtx[j].pos.y += fHeight;

			pVtx[MESH_U - j].pos = pVtx[j].pos;
			pVtx[MESH_U - j].pos.y -= fHeight * 2;
		}

		pVtx += MESH_U + 1;
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
	// プレイヤーの検知
	DetectionPlayer();

	CMeshCylinder::Update();
}

//=====================================================
// プレイヤーの検知
//=====================================================
void CTunnel::DetectionPlayer(void)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;

	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点情報のポインタ
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (!m_bInPlayer)
	{// プレイヤーが入ってきた判定
		CollidePlayerEnter(pVtx);
	}
	else
	{// プレイヤーが出ていった判定
		CollidePlayerExit(pVtx);
	}

	CDebugProc::GetInstance()->Print("\nトンネル入ってるよ[%d]", m_bInPlayer);

	// 頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//=====================================================
// プレイヤー入ってくる判定
//=====================================================
void CTunnel::CollidePlayerEnter(VERTEX_3D *pVtx)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pVtx == nullptr || pPlayer == nullptr)
		return;

	// 入口
	D3DXVECTOR3 pos1 = pVtx[0].pos;
	D3DXVECTOR3 pos2 = pVtx[MESH_U / 2].pos;

	CEffect3D::Create(pos1, 50.0f, 5, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	CEffect3D::Create(pos2, 50.0f, 5, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	// 出口
	int nNumVtx = GetNumVtx();

	D3DXVECTOR3 pos3 = pVtx[nNumVtx - MESH_U / 2 - 1].pos;
	D3DXVECTOR3 pos4 = pVtx[nNumVtx - 1].pos;

	CEffect3D::Create(pos3, 50.0f, 5, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	CEffect3D::Create(pos4, 50.0f, 5, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	// 外積でのトリガー判定
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();
	D3DXVECTOR3 posNext = posPlayer + movePlayer;
	float fRate;

	bool bHit1 = universal::IsCross(posPlayer, pos2, pos1, &fRate);
	bool bHit1Next = universal::IsCross(posNext, pos2, pos1, &fRate);

	if (fRate > 1.0f || fRate < 0.0f)
		return;

	if (!m_bInPlayer && (!bHit1 && bHit1Next))
	{// 入口から入った判定
		m_bInPlayer = true;
	}

	bool bHit2 = universal::IsCross(posPlayer, pos4, pos3, &fRate);
	bool bHit2Next = universal::IsCross(posNext, pos4, pos3, &fRate);

	if (!m_bInPlayer && (!bHit2 && bHit2Next))
	{// 出口から入った判定
		m_bInPlayer = true;
	}
}

//=====================================================
// プレイヤー出ていく判定
//=====================================================
void CTunnel::CollidePlayerExit(VERTEX_3D *pVtx)
{
	if (pVtx == nullptr)
		return;

	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pVtx == nullptr || pPlayer == nullptr)
		return;

	// 入口
	D3DXVECTOR3 pos1 = pVtx[0].pos;
	D3DXVECTOR3 pos2 = pVtx[MESH_U / 2].pos;

	CEffect3D::Create(pos1, 50.0f, 5, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	CEffect3D::Create(pos2, 50.0f, 5, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	// 出口
	int nNumVtx = GetNumVtx();

	D3DXVECTOR3 pos3 = pVtx[nNumVtx - MESH_U / 2 - 1].pos;
	D3DXVECTOR3 pos4 = pVtx[nNumVtx - 1].pos;

	CEffect3D::Create(pos3, 50.0f, 5, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	CEffect3D::Create(pos4, 50.0f, 5, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	// 外積でのトリガー判定
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();
	D3DXVECTOR3 posNext = posPlayer + movePlayer;
	float fRate;

	bool bHit1 = universal::IsCross(posPlayer, pos2, pos1, &fRate);
	bool bHit1Next = universal::IsCross(posNext, pos2, pos1, &fRate);

	if (fRate > 1.0f || fRate < 0.0f)
		return;

	if (m_bInPlayer && (bHit1 && !bHit1Next))
	{// 入口から入った判定
		m_bInPlayer = false;
	}

	bool bHit2 = universal::IsCross(posPlayer, pos4, pos3, &fRate);
	bool bHit2Next = universal::IsCross(posNext, pos4, pos3, &fRate);

	if (m_bInPlayer && (bHit2 && !bHit2Next))
	{// 出口から入った判定
		m_bInPlayer = false;
	}
}

//=====================================================
// 描画処理
//=====================================================
void CTunnel::Draw(void)
{
	CMeshCylinder::Draw();
}