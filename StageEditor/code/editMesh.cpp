//*****************************************************
//
// ブロックエディターの処理[editBlock.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "editMesh.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "effect3D.h"

//=====================================================
// コンストラクタ
//=====================================================
CEditMesh::CEditMesh()
{
	m_pMesh = nullptr;
}

//=====================================================
// デストラクタ
//=====================================================
CEditMesh::~CEditMesh()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEditMesh::Init(void)
{
	CEdit::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEditMesh::Uninit(void)
{
	CEdit::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEditMesh::Update(void)
{
	// 情報取得
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();

	CEdit::Update();

	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(0.0f, rot.y, 0.0f));

	CEffect3D::Create(pos + vecPole, 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}