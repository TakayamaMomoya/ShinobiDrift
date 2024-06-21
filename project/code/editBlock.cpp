//*****************************************************
//
// ブロックエディターの処理[editBlock.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "editBlock.h"
#include "objectX.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "manager.h"
#include "debugproc.h"
#include "block.h"
#include "blockManager.h"
#include "effect3D.h"
#include "manager.h"
#include "camera.h"
#include <assert.h>

//*****************************************************
// マクロ定義
//*****************************************************
#define SPEED_MOVE	(1.0f)	// 移動速度
#define SPEED_ROTATION	(0.01f)	// 回転

//=====================================================
// コンストラクタ
//=====================================================
CEditBlock::CEditBlock()
{
	ZeroMemory(&m_aPath[0], sizeof(m_aPath));
}

//=====================================================
// デストラクタ
//=====================================================
CEditBlock::~CEditBlock()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEditBlock::Init(void)
{
	// ステイトの初期設定
	ChangeState(new CStateCreateBlockNormal);

	CEdit::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEditBlock::Uninit(void)
{
	if (m_pState != nullptr)
	{
		m_pState->Uninit(this);
		delete m_pState;
		m_pState = nullptr;
	}

	CEdit::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEditBlock::Update(void)
{
	if (m_pState != nullptr)
	{// ステイトの更新
		m_pState->Update(this);
	}

	// ステイトの選択
	ImGui::Text("[ChangeMode]");

	if (ImGui::Button("CreateNormalBlock", ImVec2(70, 30)))	// 通常ブロックの生成
		ChangeState(new CStateCreateBlockNormal);

	if (ImGui::Button("EditGrabBlock", ImVec2(70, 30)))	// 掴めるブロックの編集
		ChangeState(new CStateEditGrabBlock);

	CEdit::Update();
}

//=====================================================
// 保存を行う処理
//=====================================================
void CEditBlock::Save(void)
{
	ImGui::Text("[Save]");

	ImGui::InputText("SavePath", &m_aPath[0], 256);

	if (ImGui::Button("Save", ImVec2(50.0f, 20.0f)))
	{// 保存
		CBlockManager *pBlockManager = CBlockManager::GetInstance();

		if (pBlockManager != nullptr)
		{
			pBlockManager->Save(&m_aPath[0]);
		}
	}
}

//=====================================================
// ステイトの変更
//=====================================================
void CEditBlock::ChangeState(CStateEditBlock *pState)
{
	if (m_pState != nullptr)
	{
		m_pState->Uninit(this);
		delete m_pState;
		m_pState = nullptr;
	}

	m_pState = pState;

	if (m_pState != nullptr)
	{
		m_pState->Init(this);
	}
}

//===================================================================================
// 通常ブロックの生成
//===================================================================================
//=====================================================
// 初期化処理
//=====================================================
void CStateCreateBlockNormal::Init(CEditBlock *pEdit)
{
	m_nIdxObject = 0;

	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager != nullptr)
	{
		CBlockManager::SInfoBlock *pInfoBlock = pBlockManager->GetInfoBlock();

		if (pInfoBlock == nullptr)
		{
			nullptr;
		}

		m_pObjectCursor = nullptr;

		m_pObjectCursor = CObjectX::Create();

		// タイプの初期設定
		m_type = CBlock::TYPE_WALL;

		// モデル番号の設定
		m_pObjectCursor->BindModel(pInfoBlock[0].nIdxModel);

		m_pObjectCursor->SetEmissiveCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}
}

//=====================================================
// 終了処理
//=====================================================
void CStateCreateBlockNormal::Uninit(CEditBlock *pEdit)
{
	if (m_pObjectCursor != nullptr)
	{
		m_pObjectCursor->Uninit();
		m_pObjectCursor = nullptr;
	}
}

//=====================================================
// 更新処理
//=====================================================
void CStateCreateBlockNormal::Update(CEditBlock *pEdit)
{
	// 情報取得
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	D3DXVECTOR3 rot = pEdit->GetRotation();
	D3DXVECTOR3 rotCamera = CManager::GetCamera()->GetCamera()->rot;
	D3DXVECTOR3 pos = pEdit->GetPosition();
	float fSpeed = SPEED_MOVE;

	if (pKeyboard == nullptr || pMouse == nullptr || pBlockManager == nullptr )
		return;

	if (!pMouse->GetPress(CInputMouse::BUTTON_RMB))
	{// 右クリックしてないときに、移動可能

		float fMove = SPEED_MOVE;

		if (pKeyboard->GetPress(DIK_LSHIFT) == true)
		{// 加速
			fMove *= 7;
		}

		// ブロック移動
		if (pKeyboard->GetPress(DIK_A) == true)
		{// 左移動
			pos.x += sinf(rotCamera.y - D3DX_PI * 0.5f) * fMove;
			pos.z += cosf(rotCamera.y - D3DX_PI * 0.5f) * fMove;
		}
		if (pKeyboard->GetPress(DIK_D) == true)
		{// 右移動
			pos.x += sinf(rotCamera.y - D3DX_PI * -0.5f) * fMove;
			pos.z += cosf(rotCamera.y - D3DX_PI * -0.5f) * fMove;
		}
		if (pKeyboard->GetPress(DIK_W) == true)
		{// 前移動
			pos.x += sinf(D3DX_PI * 0.5f) * sinf(rotCamera.y) * fMove;
			pos.z += sinf(D3DX_PI * 0.5f) * cosf(rotCamera.y) * fMove;
		}
		if (pKeyboard->GetPress(DIK_S) == true)
		{// 後移動
			pos.x += sinf(-D3DX_PI * 0.5f) * sinf(rotCamera.y) * fMove;
			pos.z += sinf(-D3DX_PI * 0.5f) * cosf(rotCamera.y) * fMove;
		}
		if (pKeyboard->GetPress(DIK_E) == true)
		{// 上昇
			pos.y += fMove;
		}
		if (pKeyboard->GetPress(DIK_Q) == true)
		{// 下降
			pos.y -= fMove;
		}
	}

	if (ImGui::TreeNode("ROT"))
	{
		// ブロック向き
		ImGui::DragFloat("ROT.X", &rot.x, 0.01f, -D3DX_PI, D3DX_PI);
		ImGui::DragFloat("ROT.Y", &rot.y, 0.01f, -D3DX_PI, D3DX_PI);
		ImGui::DragFloat("ROT.Z", &rot.z, 0.01f, -D3DX_PI, D3DX_PI);

		ImGui::TreePop();
	}

	int nNumBlock = pBlockManager->GetNumBlock();
	CBlockManager::SInfoBlock *pInfoBlock = pBlockManager->GetInfoBlock();

	if (ImGui::TreeNode("SelectBlock"))
	{
		for (int i = 0; i < nNumBlock; i++)
		{// ブロック選択
			if (ImGui::Button(&pInfoBlock[i].aTag[0], ImVec2(50.0f, 20.0f)))
			{
				m_nIdxObject = i;

				m_pObjectCursor->BindModel(pInfoBlock[i].nIdxModel);
			}
		}

		ImGui::TreePop();
	}

	// ブロックのビヘイビアの変更
	ChangeBlockBehaviour();

	ImGui::Text("[Action]");

	if (ImGui::Button("Create", ImVec2(50.0f, 20.0f)))
	{// ブロック生成
		CreateBlock(m_pObjectCursor->GetPosition());
	}

	// 削除ブロック選択
	CBlock *pBlock = CheckDelete();

	if (ImGui::Button("Delete", ImVec2(60.0f, 20.0f)))
	{// 削除
		if (pBlock != nullptr)
		{
			pBlock->Uninit();
		}
	}

	if (ImGui::Button("DeleteAll", ImVec2(80.0f, 20.0f)))
	{// 全削除
		CBlockManager *pBlockManager = CBlockManager::GetInstance();

		if (pBlockManager != nullptr)
		{
			pBlockManager->DeleteAll();
		}
	}

	// セーブ
	pEdit->Save();

	// エディットにトランスフォームを適用
	pEdit->SetPosition(pos);
	pEdit->SetRotation(rot);

	if (m_pObjectCursor != nullptr)
	{// カーソルのトランスフォーム
		m_pObjectCursor->SetPosition(pos);
		m_pObjectCursor->SetRotation(rot);
	}
}

//=====================================================
// ブロックのビヘイビア変更
//=====================================================
void CStateCreateBlockNormal::ChangeBlockBehaviour(void)
{
	ImGui::Text("[BlockBehaviour]");

	const char* apText[CBlock::BEHAVIOUR::BEHAVIOUR_MAX] =
	{
		"NORMAL",
		"GRAB"
	};

	ImGui::Text("Now[%s]",apText[m_behaviour]);

	for (int i = 0; i < CBlock::BEHAVIOUR::BEHAVIOUR_MAX; i++)
	{
		if (ImGui::Button(apText[i], ImVec2(80.0f, 20.0f)))
		{// ビヘイビア設定
			m_behaviour = (CBlock::BEHAVIOUR)i;
		}
	}
}

//=====================================================
// ブロックの生成
//=====================================================
void CStateCreateBlockNormal::CreateBlock(D3DXVECTOR3 pos)
{
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager == nullptr)
	{
		return;
	}

	CBlockManager::SInfoBlock *pInfoBlock = pBlockManager->GetInfoBlock();

	CBlock *pBlock = CBlock::Create(m_behaviour);

	if (pBlock != nullptr)
	{
		pBlock->BindModel(pInfoBlock[m_nIdxObject].nIdxModel);
		pBlock->SetPosition(pos);
		pBlock->SetRotation(m_pObjectCursor->GetRotation());
		pBlock->SetIdx(m_nIdxObject);
	}
}

//=====================================================
// 削除ブロックのチェック
//=====================================================
CBlock *CStateCreateBlockNormal::CheckDelete(void)
{
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager == nullptr)
	{
		return nullptr;
	}

	CBlock *pBlock = pBlockManager->GetHead();

	while (pBlock != nullptr)
	{
		CBlock *pBlockNext = pBlock->GetNext();

		if (pBlock != nullptr)
		{
			pBlock->ResetColor();

			D3DXVECTOR3 posBlock = pBlock->GetPosition();
			D3DXVECTOR3 pos = m_pObjectCursor->GetPosition();
			D3DXVECTOR3 vtxMax = pBlock->GetVtxMax();
			D3DXVECTOR3 vtxMin = pBlock->GetVtxMin();

			if (pos.x >= posBlock.x + vtxMin.x &&
				pos.x <= posBlock.x + vtxMax.x &&
				pos.z >= posBlock.z + vtxMin.z &&
				pos.z <= posBlock.z + vtxMax.z &&
				pos.y >= posBlock.y + vtxMin.y &&
				pos.y <= posBlock.y + vtxMax.y)
			{// ブロック内にいるとき
				pBlock->SetEmissiveCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

				return pBlock;
			}
		}

		pBlock = pBlockNext;
	}

	return nullptr;
}

//===================================================================================
// 掴むブロックの編集
//===================================================================================
//=====================================================
// 初期化処理
//=====================================================
void CStateEditGrabBlock::Init(CEditBlock *pEdit)
{
	// イテレーターの初期化
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager == nullptr)
		return;

	std::list<CBlockGrab*> *pList = pBlockManager->GetListGrab();

	m_it = pList->begin();
}

//=====================================================
// 終了処理
//=====================================================
void CStateEditGrabBlock::Uninit(CEditBlock *pEdit)
{

}

//=====================================================
// 更新処理
//=====================================================
void CStateEditGrabBlock::Update(CEditBlock *pEdit)
{
	// ブロックの選択
	SelectGrabBlock();

	// ブロックの編集
	EditGrabBlock();
}

//=====================================================
// ブロックの選択
//=====================================================
void CStateEditGrabBlock::SelectGrabBlock(void)
{
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager == nullptr)
		return;

	// ブロックの選択
	std::list<CBlockGrab*> *pList = pBlockManager->GetListGrab();

	if (ImGui::Button("NextBlock", ImVec2(70, 30)))
	{
		if (m_it != pList->end() && std::next(m_it) != pList->end())
			std::advance(m_it, 1);
	}
	if (ImGui::Button("PrevBlock", ImVec2(70, 30)))
	{
		if (m_it != pList->begin())
			std::advance(m_it, -1);
	}

	CEffect3D::Create((*m_it)->GetPosition(), 100.0f, 3, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
}

//=====================================================
// ブロックの編集
//=====================================================
void CStateEditGrabBlock::EditGrabBlock(void)
{
	ImGui::Text("[EditAngle]");

	float fAngle1 = (*m_it)->GetAngleOffset(0);
	float fAngle2 = (*m_it)->GetAngleOffset(1);

	ImGui::DragFloat("Angle1", &fAngle1, 0.05f, fAngle2, FLT_MAX);
	ImGui::DragFloat("Angle2", &fAngle2, 0.05f, -FLT_MAX, fAngle1);

	(*m_it)->SetAngleOffset(fAngle1, 0);
	(*m_it)->SetAngleOffset(fAngle2, 1);
}