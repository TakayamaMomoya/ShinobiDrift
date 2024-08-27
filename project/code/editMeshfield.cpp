//*****************************************************
//
// メッシュフィールドエディターの処理[editMeshfield.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "editMeshfield.h"
#include "meshfield.h"
#include "meshcylinder.h"
#include "inputmouse.h"
#include "inputkeyboard.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float DEFAULT_DEPTH = 100.0f;	// デフォルトの深さ
const float DEFAULT_RADIUS = 1000.0f;	// デフォルトの範囲
const float HEIGHT_CYLINDER = 50000.0f;	// シリンダーの高さ
const float SPEED_CHANGE_DEPTH = 10.0f;	// 深さ変更の速度
const float SPEED_CHANGE_RADIUS = 10.0f;	// 半径変更の速度
const string DEFAULT_PATH = "data\\MAP\\field00.bin";	// デフォルト保存パス
}

//=====================================================
// コンストラクタ
//=====================================================
CEditMeshfield::CEditMeshfield() : m_fDepthDent(0.0f), m_fRadiusDent(0.0f), m_pMeshCylinder(nullptr)
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

	m_fDepthDent = DEFAULT_DEPTH;
	m_fRadiusDent = DEFAULT_RADIUS;

	// メッシュシリンダー生成
	m_pMeshCylinder = CMeshCylinder::Create();

	if (m_pMeshCylinder != nullptr)
	{
		m_pMeshCylinder->SetIdxTexture(-1);
	}

	// デフォルトパス
	strcpy(&m_aSave[0], &DEFAULT_PATH[0]);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEditMeshfield::Uninit(void)
{
	if (m_pMeshCylinder != nullptr)
	{
		m_pMeshCylinder->Uninit();
		m_pMeshCylinder = nullptr;
	}

	CEdit::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEditMeshfield::Update(void)
{
	CEdit::Update();

	// カーソルを動かす処理
	MoveCursor();

	// パラメーターの設定
	ChangeParam();

	// メッシュフィールドをへこます処理
	DentMeshField();

	// もろもろのボタン
	OtherButton();
}

//=====================================================
// カーソルを動かす処理
//=====================================================
void CEditMeshfield::MoveCursor(void)
{
	D3DXVECTOR3 posNear;
	D3DXVECTOR3 posFar;
	D3DXVECTOR3 vecDiff;
	D3DXVECTOR3 posHit;

	universal::ConvertScreenPosTo3D(&posNear, &posFar, &vecDiff);

	universal::CalcRayFlat(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), posNear, posFar, &posHit);

	SetPosition(posHit);

	if (m_pMeshCylinder != nullptr)
	{
		m_pMeshCylinder->SetPosition(posHit);
		m_pMeshCylinder->SetHeight(HEIGHT_CYLINDER);
		m_pMeshCylinder->SetRadius(m_fRadiusDent);
		m_pMeshCylinder->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));

		m_pMeshCylinder->SetVtx();
	}
}

//=====================================================
// パラメーターの変更
//=====================================================
void CEditMeshfield::ChangeParam(void)
{
	CInputMouse *pMouse = CInputMouse::GetInstance();

	if (pMouse == nullptr)
		return;

	// へこませる深さの変更
	ImGui::DragFloat("Depth", &m_fDepthDent, SPEED_CHANGE_DEPTH, -FLT_MAX, FLT_MAX);

	if (pMouse->GetMoveIZ() > 0)	// マウスでの値操作
		m_fDepthDent += SPEED_CHANGE_DEPTH;
	else if(pMouse->GetMoveIZ() < 0)
		m_fDepthDent -= SPEED_CHANGE_DEPTH;

	// ブラシの半径を変更
	ImGui::DragFloat("Radius", &m_fRadiusDent, SPEED_CHANGE_RADIUS, -FLT_MAX, FLT_MAX);
}

//=====================================================
// メッシュフィールドをへこます処理
//=====================================================
void CEditMeshfield::DentMeshField(void)
{
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard == nullptr)
		return;

	if (!pKeyboard->GetPress(DIK_SPACE))
		return;

	CMeshField *pMeshField = CMeshField::GetInstance();

	if (pMeshField == nullptr)
		return;

	D3DXVECTOR3 pos = GetPosition();

	pMeshField->Dent(pos, m_fRadiusDent, m_fDepthDent);
}

//=====================================================
// もろもろのボタン
//=====================================================
void CEditMeshfield::OtherButton(void)
{
	CMeshField *pMesh = CMeshField::GetInstance();

	if (pMesh == nullptr)
		return;

	// 法線設定
	if (ImGui::Button("SetNormal"))
		pMesh->SetNormal();

	// 保存
	if (ImGui::Button("Save"))
		pMesh->Save(&m_aSave[0]);

	// 読込
	if (ImGui::Button("Load"))
		pMesh->Load(&m_aSave[0]);

	// リセット
	if (ImGui::Button("Reset"))
		pMesh->Reset();

	// テキストいじいじ
	ImGui::InputText("Savepath", &m_aSave[0],MAX_STRING);
}