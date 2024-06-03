//*****************************************************
//
// ブロックエディターの処理[editBlock.h]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
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
	CStateCreateBlockNormal() : m_pObjectCursor(nullptr) {};
	virtual ~CStateCreateBlockNormal() {};

	void Init(CEditBlock *pEdit) override;
	void Uninit(CEditBlock *pEdit) override;
	void Update(CEditBlock *pEdit) override;

private:
	void CreateBlock(D3DXVECTOR3 pos);
	CBlock *CheckDelete(void);

	int m_nIdxObject;
	CBlock::TYPE m_type;
	CObjectX *m_pObjectCursor;	// カーソルの仮オブジェクト
};