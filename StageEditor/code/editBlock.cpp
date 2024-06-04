//*****************************************************
//
// ブロックエディターの処理[editBlock.cpp]
// Author:髙山桃也
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
	D3DXVECTOR3 pos = pEdit->GetPosition();
	float fSpeed = SPEED_MOVE;

	if (pKeyboard == nullptr || pMouse == nullptr || pBlockManager == nullptr)
		return;

	if (ImGui::TreeNode("POS"))
	{
		// ブロック移動
		ImGui::DragFloat("POS.X", &pos.x, SPEED_MOVE, -FLT_MAX, FLT_MAX);
		ImGui::DragFloat("POS.Y", &pos.y, SPEED_MOVE, -FLT_MAX, FLT_MAX);
		ImGui::DragFloat("POS.Z", &pos.z, SPEED_MOVE, -FLT_MAX, FLT_MAX);

		ImGui::TreePop();
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

	if (ImGui::Button("Create", ImVec2(50.0f, 20.0f)))
	{// ブロック生成
		CreateBlock(m_pObjectCursor->GetPosition());
	}

	// 削除ブロック選択
	CBlock *pBlock = CheckDelete();

	if (ImGui::Button("Delete", ImVec2(60.0f, 20.0f)))
	{// 削除
		pBlock->Uninit();
	}

	// セーブ
	pEdit->Save();

	if (ImGui::Button("DeleteAll", ImVec2(80.0f, 20.0f)))
	{// 全削除
		CBlockManager *pBlockManager = CBlockManager::GetInstance();

		if (pBlockManager != nullptr)
		{
			pBlockManager->DeleteAll();
		}
	}

	// エディットにトランスフォームを適用
	pEdit->SetPosition(pos);
	pEdit->SetRotation(rot);

	if (m_pObjectCursor != nullptr)
	{// カーソルのトランスフォーム
		m_pObjectCursor->SetPosition(pos);
		m_pObjectCursor->SetRot(rot);
	}
}

//=====================================================
// ブロックのビヘイビア変更
//=====================================================
void CStateCreateBlockNormal::ChangeBlockBehaviour(void)
{
	ImGui::Text("Behaviour");

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

	CBlock *pBlock = CBlock::Create(pInfoBlock[m_nIdxObject].nIdxModel, m_behaviour);

	if (pBlock != nullptr)
	{
		pBlock->SetPosition(pos);
		pBlock->SetRot(m_pObjectCursor->GetRotation());
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

}