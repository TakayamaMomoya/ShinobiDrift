//*****************************************************
//
// ブロックの処理[block.cpp]
// Author:髙山桃也
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
#include "debrisSpawner.h"
#include "effect3D.h"
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
	m_bGrab = true;
	m_bCurrent = false;

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
CBlock *CBlock::Create(int nIdxModel)
{
	CBlock *pBlock = nullptr;

	if (pBlock == nullptr)
	{// インスタンス生成
		pBlock = new CBlock;

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

	// 影の有効化
	EnableShadow(true);

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

	if (m_bCurrent)
	{
		CEffect3D::Create(GetPosition(),200.0f,5,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	}
}

//=====================================================
// 掴めるかの判定
//=====================================================
bool CBlock::CanGrab(D3DXVECTOR3 pos)
{
	bool bCanGrab1 = true;
	bool bCanGrab2 = true;

	// 判定の設置
	D3DXMATRIX mtxVec1;
	D3DXMATRIX mtxVec2;
	D3DXMATRIX mtx = *GetMatrix();
	universal::SetOffSet(&mtxVec1, mtx, D3DXVECTOR3(200.0f, 0.0f, 0.0f));
	universal::SetOffSet(&mtxVec2, mtx, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	D3DXVECTOR3 posMtx1 = { mtxVec1._41,mtxVec1._42 ,mtxVec1._43 };
	D3DXVECTOR3 posMtx2 = { mtxVec2._41,mtxVec2._42 ,mtxVec2._43 };

#ifdef _DEBUG
	CEffect3D::Create(posMtx1, 100.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
#endif

	bCanGrab1 = universal::IsCross(pos, GetPosition(), posMtx1, nullptr);
	bCanGrab2 = universal::IsCross(pos, GetPosition(), posMtx2, nullptr);

	CDebugProc::GetInstance()->Print("\n掴める1[%d]", bCanGrab1);
	CDebugProc::GetInstance()->Print("\n掴める2[%d]", bCanGrab2);

	return bCanGrab1 ^ bCanGrab2;
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