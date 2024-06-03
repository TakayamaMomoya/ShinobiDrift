//*****************************************************
//
// ブロックの処理[block.cpp]
// Author:��山桃也
//
//*****************************************************

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "ObjectX.h"

//*****************************************************
// 前方宣言
//*****************************************************

//*****************************************************
// クラスの定義
//*****************************************************
//=====================================================
// 通常ブロッククラス
//=====================================================
class CBlock : public CObjectX
{
public:
	typedef enum
	{// 種類
		TYPE_WALL = 0,	// 壁
		TYPE_MAX
	}TYPE;

	typedef enum
	{// 行動
		BEHAVIOUR_NORMAL = 0,	// 通常
		BEHAVIOUR_GRAB,	// 掴めるもの
	}BEHAVIOUR;

	typedef struct
	{// 保存するときの情報
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		TYPE type;
	}MemBlock;

	CBlock(int nPriority = 3);	// コンストラクタ
	~CBlock();	// デストラクタ

	static CBlock *Create(int nIdxModel,BEHAVIOUR behaviour = BEHAVIOUR_NORMAL);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(float fDamage);
	void SetRotation(D3DXVECTOR3 rot);
	int GetIdx(void) { return m_nIdx; }
	void SetIdx(int nIdx) { m_nIdx = nIdx; }
	CBlock *GetNext(void) { return m_pNext; }
	static int GetNumAll(void) { return m_nNumAll; }
	void SetPosition(D3DXVECTOR3 pos);
	void EnableCurrent(bool bCurrent) { m_bCurrent = bCurrent; }
	bool CanGrab(D3DXVECTOR3 pos);

private:
	static int m_nNumAll;	// 総数
	float m_fLife;	// 体力
	int m_nIdx;	// 種類のインデックス
	bool m_bGrab;	// 掴めるかどうか
	bool m_bCurrent;	// 選択されているかどうか

	CBlock *m_pPrev;	// 前のアドレス
	CBlock *m_pNext;	// 次のアドレス
};

//=====================================================
// 掴むブロッククラス
//=====================================================
class CBlockGrab : public CBlock
{
public:
	CBlockGrab();	// コンストラクタ
	~CBlockGrab();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};

#endif
