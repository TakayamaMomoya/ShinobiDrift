//*****************************************************
//
// ブロックの処理[block.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "block.h"
#include "blockManager.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "effect3D.h"
#include "fan3D.h"
#include "debugproc.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const float SPEED_MOVE(1.0f);	// 移動速度
	const char* MAP_FILE = "data\\MAP\\map01.bin";	// マップのファイルパス
	const float RADIUS_DRIFT_DEFAULT = 1000.0f;	// ドリフト半径のデフォルト値
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
int CBlock::m_nNumAll = 0;	// 総数

//=====================================================
// コンストラクタ
//=====================================================
CBlock::CBlock(int nPriority)
{
	m_fLife = 0.0f;
	m_pPrev = nullptr;
	m_pNext = nullptr;
	m_nIdx = -1;

	// 先頭、最後尾アドレス取得
	CBlockManager *pManager = CBlockManager::GetInstance();
	CBlock *pHead = nullptr;
	CBlock *pTail = nullptr;

	if (pManager != nullptr)
	{
		pHead = pManager->GetHead();
		pTail = pManager->GetTail();
	}

	if (pHead == nullptr)
	{// 先頭と最後尾アドレスの代入
		pManager->SetHead(this);
		pManager->SetTail(this);

		return;
	}

	// 前のアドレスに最後尾のアドレスを代入する
	m_pPrev = pTail;

	// 最後尾のアドレスを自分にする
	pManager->SetTail(this);

	if (m_pPrev != nullptr)
	{
		// 前のオブジェクトの次のアドレスを自分にする
		m_pPrev->m_pNext = this;
	}

	m_nNumAll++;
}

//=====================================================
// デストラクタ
//=====================================================
CBlock::~CBlock()
{
	// 先頭、最後尾アドレス取得
	CBlockManager *pManager = CBlockManager::GetInstance();
	CBlock *pHead = nullptr;
	CBlock *pTail = nullptr;

	if (pManager != nullptr)
	{
		pHead = pManager->GetHead();
		pTail = pManager->GetTail();
	}

	m_nNumAll--;

	if (pTail != this && pHead != this)
	{// 真ん中のアドレスの破棄
		if (m_pPrev != nullptr)
		{
			// 前のアドレスから次のアドレスをつなぐ
			m_pPrev->m_pNext = m_pNext;
		}

		if (m_pNext != nullptr)
		{
			// 次のアドレスから前のアドレスをつなぐ
			m_pNext->m_pPrev = m_pPrev;
		}
	}

	if (pHead == this)
	{// 先頭アドレスの破棄
		//if (m_pNext != nullptr)
		{// 先頭アドレスを次のアドレスに引き継ぐ
			pManager->SetHead(m_pNext);

			if (m_pNext != nullptr)
			{
				m_pNext->m_pPrev = nullptr;
			}
		}
	}

	if (pTail == this)
	{// 最後尾アドレスの破棄
		if (m_pPrev != nullptr)
		{// 最後尾アドレスを前のアドレスに引き継ぐ
			pManager->SetTail(m_pPrev);

			m_pPrev->m_pNext = nullptr;
		}
	}

	m_nNumAll--;
}

//=====================================================
// 生成処理
//=====================================================
CBlock *CBlock::Create(int nIdxModel, BEHAVIOUR behaviour)
{
	CBlock *pBlock = nullptr;

	// インスタンス生成
	switch (behaviour)
	{
	case BEHAVIOUR_NORMAL:
		pBlock = new CBlock;
		break;
	case BEHAVIOUR_GRAB:
		pBlock = new CBlockGrab;
		break;
	default:
		assert(("ブロックのビヘイビアーに不正な値が入力されました", false));
		break;
	}

	if (pBlock != nullptr)
	{
		// 初期化処理
		pBlock->Init();

		// 種類ごとのモデル読込
		pBlock->BindModel(nIdxModel);
	}

	return pBlock;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CBlock::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// 継承クラスの初期化
	CObjectX::Init();

	// タイプの設定
	SetType(TYPE_BLOCK);

	m_fLife = 300.0f;

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CBlock::Uninit(void)
{
	// 継承クラスの終了
	CObjectX::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CBlock::Update(void)
{
	// 継承クラスの更新
	CObjectX::Update();
}

//=====================================================
// 位置設定
//=====================================================
void CBlock::SetPosition(D3DXVECTOR3 pos)
{
	CObjectX::SetPosition(pos);
}

//=====================================================
// 描画処理
//=====================================================
void CBlock::Draw(void)
{
	// 継承クラスの描画
	CObjectX::Draw();
}

//=====================================================
// ヒット処理
//=====================================================
void CBlock::Hit(float fDamage)
{

}

//=====================================================
// 頂点を入れ替える処理
//=====================================================
void CBlock::SetRotation(D3DXVECTOR3 rot)
{
	CObjectX::SetRotation(rot);
}

//============================================================================
// 掴めるブロッククラス
//============================================================================
//=====================================================
// コンストラクタ
//=====================================================
CBlockGrab::CBlockGrab() : m_bCurrent(false), m_fRadiusOffset(0.0f),m_pFan(nullptr)
{
	for (int i = 0; i < NUM_OFFSET; i++)
	{
		m_afAngleOffset[i] = 0.0f;
	}
}
 
//=====================================================
// デストラクタ
//=====================================================
CBlockGrab::~CBlockGrab()
{

}

//=====================================================
// 初期化
//=====================================================
HRESULT CBlockGrab::Init(void)
{
	// 掴みブロックリストに追加
	CBlockManager *pBlockManager =  BlockManager::GetInstance();

	if (pBlockManager != nullptr)
		pBlockManager->AddGrabList(this);

	// 基底クラスの初期化
	CBlock::Init();

	// オフセットの初期化
	m_afAngleOffset[0] = D3DX_PI;
	m_afAngleOffset[1] = D3DX_PI * 0.5f;
	m_fRadiusOffset = 1000.0f;

#ifdef _DEBUG
	// 判定可視化用の扇生成
	if (m_pFan == nullptr)
	{
		m_pFan = CFan3D::Create();
		
		if (m_pFan != nullptr)
		{
			m_pFan->SetRotation(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
			m_pFan->SetRadius(400.0f);
		}
	}
#endif

	return S_OK;
}

//=====================================================
// 終了
//=====================================================
void CBlockGrab::Uninit(void)
{
	// 掴みブロックリストから除外
	CBlockManager *pBlockManager = BlockManager::GetInstance();

	if (pBlockManager != nullptr)
		pBlockManager->RemoveGrabList(this);
	
	// 基底クラスの終了
	CBlock::Uninit();
}

//=====================================================
// 更新
//=====================================================
void CBlockGrab::Update(void)
{
	if (m_bCurrent)
	{
		CEffect3D::Create(GetPosition(), 200.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	CBlock::Update();

	if (m_pFan != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();
		
		pos.y += 10.0f;

		m_pFan->SetPosition(pos);

		m_pFan->SetRotation(D3DXVECTOR3(D3DX_PI * 0.5f, GetRotation().y, 0.0f));
	}
}

//=====================================================
// 描画
//=====================================================
void CBlockGrab::Draw(void)
{
	CBlock::Draw();
}

//=====================================================
// 掴めるかの判定
//=====================================================
bool CBlockGrab::CanGrab(D3DXVECTOR3 pos)
{
	bool bCanGrab1 = true;
	bool bCanGrab2 = true;

	// 判定の設置
	D3DXMATRIX mtxVec1;
	D3DXMATRIX mtxVec2;
	D3DXMATRIX mtx = *GetMatrix();

	// オフセットの設定
	D3DXVECTOR3 offset1 = { sinf(m_afAngleOffset[0]) * m_fRadiusOffset,0.0f,cosf(m_afAngleOffset[0]) * m_fRadiusOffset };
	D3DXVECTOR3 offset2 = { sinf(m_afAngleOffset[1]) * m_fRadiusOffset,0.0f,cosf(m_afAngleOffset[1]) * m_fRadiusOffset };

	universal::SetOffSet(&mtxVec1, mtx, offset1);
	universal::SetOffSet(&mtxVec2, mtx, offset2);

	D3DXVECTOR3 posMtx1 = { mtxVec1._41,mtxVec1._42 ,mtxVec1._43 };
	D3DXVECTOR3 posMtx2 = { mtxVec2._41,mtxVec2._42 ,mtxVec2._43 };

	bCanGrab1 = universal::IsCross(pos, posMtx1, GetPosition(), nullptr);
	bCanGrab2 = universal::IsCross(pos, GetPosition(), posMtx2, nullptr);

	CDebugProc::GetInstance()->Print("\n掴める1[%d]", bCanGrab1);
	CDebugProc::GetInstance()->Print("\n掴める2[%d]", bCanGrab2);

	bool bOK = bCanGrab1 && bCanGrab2;

#ifdef _DEBUG
	CEffect3D::Create(posMtx1, 100.0f, 3, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CEffect3D::Create(posMtx2, 100.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	
	if (bCanGrab1)
	{
		posMtx1.y += 100.0f;
		CEffect3D::Create(posMtx1, 100.0f, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	
	if (bCanGrab2)
	{
		posMtx2.y += 100.0f;
		CEffect3D::Create(posMtx2, 100.0f, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (bOK)
	{
		CEffect3D::Create(GetPosition(), 150.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
#endif

	return bOK;
}