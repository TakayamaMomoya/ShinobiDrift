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
#include "meshRoad.h"
#include "objectX.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float SPEED_MOVE = 5.0f;	// 移動速度
const float SPEED_ROLL = 0.05f;	// 回転速度
}

//=====================================================
// コンストラクタ
//=====================================================
CEditMesh::CEditMesh()
{
	m_pMesh = nullptr;
	m_pManipulator = nullptr;
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

	// マニピュレータの生成
	m_pManipulator = CObjectX::Create();

	// モデル番号の設定
	int nIdx = CModel::Load("data\\MODEL\\block\\manipulator.x");
	m_pManipulator->BindModel(nIdx);

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

	D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, rot.y - D3DX_PI * 0.5f, 0.0f));

	CEffect3D::Create(pos + vecPole * 200.0f, 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CEffect3D::Create(pos - vecPole * 200.0f, 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	if (!pMouse->GetPress(CInputMouse::BUTTON_RMB))
	{// 右クリックしてないときに、移動可能
		float fMove = SPEED_MOVE;

		if (pKeyboard->GetPress(DIK_LSHIFT) == true)
		{// 加速
			fMove *= 7;
		}

		// 視点移動===============================================
		if (pKeyboard->GetPress(DIK_A) == true)
		{// 左移動
			pos.x -= sinf(rot.y - D3DX_PI * 0.5f) * fMove;
			pos.z -= cosf(rot.y - D3DX_PI * 0.5f) * fMove;
		}
		if (pKeyboard->GetPress(DIK_D) == true)
		{// 右移動
			pos.x -= sinf(rot.y - D3DX_PI * -0.5f) * fMove;
			pos.z -= cosf(rot.y - D3DX_PI * -0.5f) * fMove;
		}
		if (pKeyboard->GetPress(DIK_W) == true)
		{// 前移動
			pos.x += sinf(rot.x - D3DX_PI * 0.5f) * sinf(rot.y) * fMove;
			pos.y -= cosf(rot.x - D3DX_PI * 0.5f) * fMove;
			pos.z += sinf(rot.x - D3DX_PI * 0.5f) * cosf(rot.y) * fMove;
		}
		if (pKeyboard->GetPress(DIK_S) == true)
		{// 後移動
			pos.x += sinf(rot.x + D3DX_PI * 0.5f) * sinf(rot.y) * fMove;
			pos.y -= cosf(rot.x + D3DX_PI * 0.5f) * fMove;
			pos.z += sinf(rot.x + D3DX_PI * 0.5f) * cosf(rot.y) * fMove;
		}
		if (pKeyboard->GetPress(DIK_E) == true)
		{// 上昇
			pos.y += fMove;
		}
		if (pKeyboard->GetPress(DIK_Q) == true)
		{// 下降
			pos.y -= fMove;
		}

		// 回転
		if (pKeyboard->GetPress(DIK_Z) == true)
		{
			rot.y += SPEED_ROLL;
		}
		if (pKeyboard->GetPress(DIK_C) == true)
		{
			rot.y -= SPEED_ROLL;
		}

		SetRotation(rot);
		SetPosition(pos);

		m_pManipulator->SetPosition(pos);
		m_pManipulator->SetRot(rot);
	}

	if (pKeyboard->GetTrigger(DIK_SPACE))
	{// メッシュの追加
		CMeshRoad *pMesh = CMeshRoad::GetInstance();

		pMesh->AddEdge(pos, rot.y - D3DX_PI * 0.5f,true);
	}
}