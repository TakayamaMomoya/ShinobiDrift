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

	if (ImGui::Button("Curve", ImVec2(70, 30)))	// カーブの調節
		ChangeState(new CStateEditMeshCurve);

	if (ImGui::Button("DeleteEdge", ImVec2(70, 30)))	// 辺の削除
		ChangeState(new CStateEditMeshDeleteEdge);
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
	D3DXVECTOR3 rot = pEdit->GetRotation();

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

		pEdit->SetRotation(rot);
		pEdit->SetPosition(pos);
	}

	D3DXVECTOR3 posD = pos + vecPole * 200.0f;
	CDebugProc::GetInstance()->Print("オフセット[%f,%f,%f]", posD.x, posD.y, posD.z);
	posD = pos - vecPole * 200.0f;
	CDebugProc::GetInstance()->Print("オフセット[%f,%f,%f]", posD.x, posD.y, posD.z);

	if (pKeyboard->GetTrigger(DIK_SPACE))
	{// メッシュの追加
		CMeshRoad *pMesh = CMeshRoad::GetInstance();

		pMesh->AddEdge(pos, rot.y - D3DX_PI * 0.5f, true);

		D3DXVECTOR3 pos = pos + vecPole * 200.0f;
		CDebugProc::GetInstance()->Print("オフセット[%f,%f,%f]", pos.x, pos.y, pos.z);
		pos = pos - vecPole * 200.0f;
		CDebugProc::GetInstance()->Print("オフセット[%f,%f,%f]", pos.x, pos.y, pos.z);
		CEffect3D::Create(pos + vecPole * 200.0f, 50.0f, 50000, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		CEffect3D::Create(pos - vecPole * 200.0f, 50.0f, 50000, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (ImGui::Button("Save", ImVec2(100, 50)))
	{
		CMeshRoad *pMesh = CMeshRoad::GetInstance();

		if (pMesh != nullptr)
			pMesh->Save();
	}
}

//****************************************************************************************
// カーブの調節
//****************************************************************************************
CStateEditMeshCurve::CStateEditMeshCurve() : m_bStart(false), m_bEnd(false), m_fAngleCurve(0.0f)
{
	CMeshRoad *pMeshRoad = MeshRoad::GetInstance();
	pMeshRoad->ResetIterator();
}

void CStateEditMeshCurve::Update(CEditMesh *pEdit)
{
	// 辺の選択
	std::vector<CMeshRoad::SInfoEdge>::iterator it = CMeshRoad::GetInstance()->SelectEdge();

	// 選択している辺の上にエフェクトを出す
	D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, it->fRot, 0.0f));
	CEffect3D::Create(it->pos + vecPole * 200.0f, 50.0f, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CEffect3D::Create(it->pos - vecPole * 200.0f, 50.0f, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard == nullptr)
		return;

	if (pKeyboard->GetTrigger(DIK_SPACE))
	{// 辺の選択
		SetEdge(it);
	}

	if (pKeyboard->GetTrigger(DIK_R))
	{// 選択辺の削除
		m_bStart = false;
		m_bEnd = false;
	}

	// 選択した辺にエフェクトを出す
	if (m_bStart)
	{
		D3DXVECTOR3 pos = m_itStart->pos + vecPole * 200.0f;
		pos.y += 100.0f;
		CEffect3D::Create(pos, 50.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		CEffect3D::Create(pos, 50.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

	if (m_bEnd)
	{
		D3DXVECTOR3 pos = m_itEnd->pos + vecPole * 200.0f;
		pos.y += 100.0f;
		CEffect3D::Create(pos, 50.0f, 3, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
		CEffect3D::Create(pos, 50.0f, 3, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	}

	if (m_bStart && m_bEnd)
	{// カーブの強さの調節
		SetCurve();
	}
}

void CStateEditMeshCurve::SetEdge(std::vector<CMeshRoad::SInfoEdge>::iterator it)
{// 最初と最後の辺の設定
	if (!m_bStart)
	{// 最初の辺設定
		m_itStart = it;
		m_bStart = true;
	}
	else if (!m_bEnd)
	{// 最後の辺を設定
		m_itEnd = it;
		m_bEnd = true;
	}
}

void CStateEditMeshCurve::SetCurve(void)
{// カーブの調整
	ImGui::DragFloat("AngleCurve", &m_fAngleCurve, 1.0f, -FLT_MAX, FLT_MAX);

	// 辺をカーブに沿って設定
	D3DXVECTOR3 posStart = m_itStart->pos;
	D3DXVECTOR3 posEnd = m_itEnd->pos;
	D3DXVECTOR3 vecDiff = posEnd - posStart;
	D3DXVECTOR3 posMid = posStart + vecDiff * 0.5f;

	CEffect3D::Create(posMid, 50.0f, 3, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));	// 中心座標のエフェクト

	// 辺のリストの取得
	CMeshRoad *pMeshRoad = MeshRoad::GetInstance();
	std::vector<CMeshRoad::SInfoEdge> *pList = pMeshRoad->GetList();

	ptrdiff_t distance = std::distance(m_itStart, m_itEnd);	// イテレーター同士の距離

	int nCntEdge = 1;
	for (auto it = m_itStart; it != m_itEnd - 1; it++)
	{// 最初の辺から最後の辺の間をチェック
		ptrdiff_t distanceCurrent = std::distance(it, m_itEnd);
		float fRate = (float)nCntEdge / (distance);
		fRate -= 0.5f;

		D3DXVECTOR3 posEdge = posMid + vecDiff * fRate;	// 辺予測位置の整列

		// 放物線の計算
		float fLength = universal::ParabolaY(fRate, -m_fAngleCurve);
		D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, it->fRot, 0.0f)) * fLength;
		posEdge += vecPole;

		// ずらす分の放物線の計算
		fRate = 1.0f / (distance);
		fRate -= 0.5f;
		fLength = universal::ParabolaY(fRate, -m_fAngleCurve);
		posEdge -= universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, it->fRot, 0.0f)) * fLength;

		CEffect3D::Create(posEdge, 50.0f, 3, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));	// 曲がった先のエフェクト

		// 辺の決定
		CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
		
		if (pKeyboard->GetTrigger(DIK_RETURN))
		{
			it->pos = posEdge;

			
		}

		nCntEdge++;
	}
}

//****************************************************************************************
// 辺の削除
//****************************************************************************************
void CStateEditMeshDeleteEdge::Update(CEditMesh *pEdit)
{
	std::vector<CMeshRoad::SInfoEdge>::iterator it = CMeshRoad::GetInstance()->SelectEdge();

	D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, it->fRot, 0.0f));

	CEffect3D::Create(it->pos + vecPole * 200.0f, 50.0f, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CEffect3D::Create(it->pos - vecPole * 200.0f, 50.0f, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	if (ImGui::Button("Delete", ImVec2(100, 50)))
	{
		CMeshRoad::GetInstance()->DeleteEdge(it);

		return;
	}
}