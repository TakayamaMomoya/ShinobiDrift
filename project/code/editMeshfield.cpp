//*****************************************************
//
// メッシュフィールドエディターの処理[editMeshfield.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "editMeshfield.h"
#include "meshfield.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{

}

//=====================================================
// コンストラクタ
//=====================================================
CEditMeshfield::CEditMeshfield()
{

}

//=====================================================
// デストラクタ
//=====================================================
CEditMeshfield::~CEditMeshfield()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEditMeshfield::Init(void)
{
	CEdit::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEditMeshfield::Uninit(void)
{
	CEdit::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEditMeshfield::Update(void)
{
	CEdit::Update();
}