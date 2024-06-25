//*****************************************************
//
// ブロックエディターの処理[editBlock.h]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "block.h"
#include "edit.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CObjectX;
class CStateEditBlock;

//*****************************************************
// クラスの定義
//*****************************************************
class CEditBlock : public CEdit
{
public:
	CEditBlock();	// コンストラクタ
	~CEditBlock();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Save(void);
	void ChangeState(CStateEditBlock *pState);

private:
	char m_aPath[256];
	CStateEditBlock *m_pState;	// ステイトのポインタ
};

//*****************************************************
// ステイトクラスの定義
//*****************************************************
class CStateEditBlock
{// ブロックエディットのステイト基底クラス
public:
	CStateEditBlock() {};
	virtual ~CStateEditBlock() {};

	virtual void Init(CEditBlock *pEdit) = 0;
	virtual void Uninit(CEditBlock *pEdit) = 0;
	virtual void Update(CEditBlock *pEdit) = 0;
};

class CStateCreateBlockNormal : public CStateEditBlock
{// 通常ブロックの生成
public:
	CStateCreateBlockNormal() : m_pObjectCursor(nullptr), m_nIdxObject(-1), m_type(CBlock::TYPE::TYPE_WALL), m_behaviour(CBlock::BEHAVIOUR::BEHAVIOUR_NORMAL) {};
	virtual ~CStateCreateBlockNormal() {};

	void Init(CEditBlock *pEdit) override;
	void Uninit(CEditBlock *pEdit) override;
	void Update(CEditBlock *pEdit) override;

private:
	void ChangeBlockBehaviour(void);
	void CreateBlock(D3DXVECTOR3 pos);
	CBlock *CheckDelete(void);

	int m_nIdxObject;
	CBlock::TYPE m_type;
	CObjectX *m_pObjectCursor;	// カーソルの仮オブジェクト
	CBlock::BEHAVIOUR m_behaviour;	// ブロックのビヘイビア
};

class CStateEditGrabBlock : public CStateEditBlock
{// 掴むブロックの編集
public:
	CStateEditGrabBlock() {};
	virtual ~CStateEditGrabBlock() {};

	// メンバ関数
	void Init(CEditBlock *pEdit) override;
	void Uninit(CEditBlock *pEdit) override;
	void Update(CEditBlock *pEdit) override;

private:
	// メンバ関数
	void SelectGrabBlock(void);
	void EditGrabBlock(void);

	// メンバ変数
	std::list<CBlockGrab*>::iterator m_it;	// イテレーター
};