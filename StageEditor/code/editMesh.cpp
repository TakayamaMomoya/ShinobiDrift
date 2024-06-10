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
#include "debugproc.h"
#include "camera.h"
#include "manager.h"

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
	m_pState = nullptr;
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

	// モデルの割り当て
	int nIdx = CModel::Load("data\\MODEL\\block\\manipulator.x");
	m_pManipulator->BindModel(nIdx);

	ChangeState(new CStateEditMeshCreateMesh);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEditMesh::Uninit(void)
{
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	if (m_pManipulator != nullptr)
	{
		m_pManipulator->Uninit();
		m_pManipulator = nullptr;
	}

	CEdit::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEditMesh::Update(void)
{
	CEdit::Update();

	// マニピュレーターのトランスフォーム更新
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	m_pManipulator->SetPosition(pos);
	m_pManipulator->SetRot(rot);

	if (m_pState != nullptr)	// ステイトの更新
		m_pState->Update(this);

	// ステイトによるモードの切り替え
	ImGui::Text("ModeSelect");

	if (ImGui::Button("CreateEdge", ImVec2(70, 30)))	// メッシュ生成
		ChangeState(new CStateEditMeshCreateMesh);

	if (ImGui::Button("AdjustRoadPoint", ImVec2(70, 30)))	// ロードポイントの調節
		ChangeState(new CStateEditMeshAdjustRoadPoint);

	if (ImGui::Button("DeleteRoadPoint", ImVec2(70, 30)))	// 辺の削除
		ChangeState(new CStateEditMeshDeleteRoadPoint);
}

//=====================================================
// ステイトの変更
//=====================================================
void CEditMesh::ChangeState(CStateEditMesh *pState)
{
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	m_pState = pState;
}

//****************************************************************************************
// メッシュの生成
//****************************************************************************************
void CStateEditMeshCreateMesh::Update(CEditMesh *pEdit)
{
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();

	D3DXVECTOR3 pos = pEdit->GetPosition();
	D3DXVECTOR3 rot = CManager::GetCamera()->GetCamera()->rot;

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
			pos.x += sinf(rot.y - D3DX_PI * 0.5f) * fMove;
			pos.z += cosf(rot.y - D3DX_PI * 0.5f) * fMove;
		}
		if (pKeyboard->GetPress(DIK_D) == true)
		{// 右移動
			pos.x += sinf(rot.y - D3DX_PI * -0.5f) * fMove;
			pos.z += cosf(rot.y - D3DX_PI * -0.5f) * fMove;
		}
		if (pKeyboard->GetPress(DIK_W) == true)
		{// 前移動
			pos.x += sinf(D3DX_PI * 0.5f) * sinf(rot.y) * fMove;
			pos.z += sinf(D3DX_PI * 0.5f) * cosf(rot.y) * fMove;
		}
		if (pKeyboard->GetPress(DIK_S) == true)
		{// 後移動
			pos.x += sinf(-D3DX_PI * 0.5f) * sinf(rot.y) * fMove;
			pos.z += sinf(-D3DX_PI * 0.5f) * cosf(rot.y) * fMove;
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

		// 位置の制限
		LimitPos(&pos);

		pEdit->SetRotation(rot);
		pEdit->SetPosition(pos);
	}

	if (pKeyboard->GetTrigger(DIK_SPACE))
	{// ロードポイントの追加
		CMeshRoad *pMesh = CMeshRoad::GetInstance();

		pMesh->AddRoadPoint(pos, true);
	}
	
	if (ImGui::Button("Save", ImVec2(100, 50)))
	{// 保存
		CMeshRoad *pMesh = CMeshRoad::GetInstance();

		if (pMesh != nullptr)
			pMesh->Save();
	}
}

void CStateEditMeshCreateMesh::LimitPos(D3DXVECTOR3 *pPos)
{// 位置の制限
	// リストの取得
	CMeshRoad *pMesh = MeshRoad::GetInstance();
	
	std::vector<CMeshRoad::SInfoRoadPoint> *pVectorRoadPoint = pMesh->GetList();
	
	if (!pVectorRoadPoint->empty())
	{
		std::vector<CMeshRoad::SInfoRoadPoint>::iterator itLast = pVectorRoadPoint->end() - 1;

		if (pPos->x <= itLast->pos.x)
		{
			pPos->x = itLast->pos.x;
		}
	}
}

//****************************************************************************************
// ロードポイントの調節
//****************************************************************************************
CStateEditMeshAdjustRoadPoint::CStateEditMeshAdjustRoadPoint()
{// コンストラクタ
	CMeshRoad *pMesh = MeshRoad::GetInstance();

	pMesh->ResetIterator();
}

void CStateEditMeshAdjustRoadPoint::Update(CEditMesh *pEdit)
{
	CMeshRoad *pMesh = MeshRoad::GetInstance();

	// ロードポイントの選択
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator it = pMesh->SelectRoadPoint();

	D3DXVECTOR3 pos = it->pos;

	ImGui::DragFloat("posRoadPointPOS.X", &pos.x, 2.0f, -FLT_MAX, FLT_MAX);
	ImGui::DragFloat("posRoadPointPOS.Y", &pos.y, 2.0f, -FLT_MAX, FLT_MAX);
	ImGui::DragFloat("posRoadPointPOS.Z", &pos.z, 2.0f, -FLT_MAX, FLT_MAX);

	it->pos = pos;

	pMesh->CreateVtxBuffEdge();
}

//****************************************************************************************
// 辺の削除
//****************************************************************************************
CStateEditMeshDeleteRoadPoint::CStateEditMeshDeleteRoadPoint()
{// コンストラクタ
	CMeshRoad *pMesh = MeshRoad::GetInstance();

	pMesh->ResetIterator();
}

void CStateEditMeshDeleteRoadPoint::Update(CEditMesh *pEdit)
{
	CMeshRoad *pMesh = MeshRoad::GetInstance();

	// 辺の選択
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator it = pMesh->SelectRoadPoint();

	if (ImGui::Button("Delete", ImVec2(100, 50)))
	{
		CMeshRoad::GetInstance()->DeleteEdge(it);

		return;
	}
}