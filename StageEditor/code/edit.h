//*****************************************************
//
// エディターの処理[edit.h]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "block.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CObjectX;

//*****************************************************
// クラスの定義
//*****************************************************
class CEdit
{
public:
	CEdit();	// コンストラクタ
	~CEdit();	// デストラクタ

	static CEdit *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	static CEdit *GetInstatnce(void) { return m_pEdit; }

private:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	static CEdit *m_pEdit;	// 自身のポインタ
};