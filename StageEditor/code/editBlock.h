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

private:
	void LoopCursor(void);
	void CreateBlock(D3DXVECTOR3 pos);
	CBlock *CheckDelete(void);

	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	CObjectX *m_pObjectCursor;	// カーソルのオブジェクトXへのポインタ
	int m_nIdxObject;
	char m_aPath[256];
	CBlock::TYPE m_type;
};