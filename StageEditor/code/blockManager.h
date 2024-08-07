//*****************************************************
//
// ブロック管理[blockManager.h]
// Author:��山桃也
//
//*****************************************************

#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "block.h"
#include <list>

//*****************************************************
// 前方宣言
//*****************************************************
class CModel;

//*****************************************************
// クラスの定義
//*****************************************************
class CBlockManager : public CObject
{
public:
	struct SInfoBlock
	{// ブロックの情報
		char aTag[256];	// タグ
		int nIdxModel;	// モデル番号
		bool bSnag;	// 障害物になるかどうか
	};

	CBlockManager();	// コンストラクタ
	~CBlockManager();	// デストラクタ

	static CBlockManager *Create(void);
	static CBlockManager *GetInstance(void) { return m_pBlockManager; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int GetNumBlock(void) { return m_nNumInfoBlock; }
	SInfoBlock *GetInfoBlock(void) { return m_pInfoBlock; }
	void Save(char *pPath);
	void DeleteAll(void);
	std::list<CBlockGrab*> *GetListGrab(void) { return &m_listGrab; }
	void AddGrabList(CBlockGrab *pBlock);
	void RemoveGrabList(CBlockGrab *pBlock);
	CBlock *GetHead(void) { return m_pHead; }
	CBlock *GetTail(void) { return m_pTail; }
	void SetHead(CBlock *pBlock) { m_pHead = pBlock; }
	void SetTail(CBlock *pBlock) { m_pTail = pBlock; }

private:
	void Load(void);
	void LoadMap(FILE *pFile,char *pTemp,CBlock *pBlock);

	SInfoBlock *m_pInfoBlock;	// ブロック情報のポインタ
	int m_nNumInfoBlock;	// ブロック情報の数

	CBlock *m_pHead;	// 先頭のアドレス
	CBlock *m_pTail;	// 最後尾のアドレス
	std::list<CBlockGrab*> m_listGrab;	// 掴めるブロックのリスト
	static CBlockManager *m_pBlockManager;	// 自身のポインタ
};

namespace BlockManager
{
CBlockManager *GetInstance(void);
}

#endif