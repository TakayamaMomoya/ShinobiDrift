//*****************************************************
//
// �u���b�N�G�f�B�^�[�̏���[editBlock.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
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
// �}�N����`
//*****************************************************
#define SPEED_MOVE	(1.0f)	// �ړ����x
#define SPEED_ROTATION	(0.01f)	// ��]

//=====================================================
// �R���X�g���N�^
//=====================================================
CEditBlock::CEditBlock()
{
	ZeroMemory(&m_aPath[0], sizeof(m_aPath));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEditBlock::~CEditBlock()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CEditBlock::Init(void)
{
	// �X�e�C�g�̏����ݒ�
	ChangeState(new CStateCreateBlockNormal);

	CEdit::Init();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEditBlock::Uninit(void)
{
	CEdit::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEditBlock::Update(void)
{
	if (m_pState != nullptr)
	{// �X�e�C�g�̍X�V
		m_pState->Update(this);
	}

	CEdit::Update();
}

//=====================================================
// �ۑ����s������
//=====================================================
void CEditBlock::Save(void)
{
	ImGui::InputText("SavePath", &m_aPath[0], 256);

	if (ImGui::Button("Save", ImVec2(50.0f, 20.0f)))
	{// �ۑ�
		CBlockManager *pBlockManager = CBlockManager::GetInstance();

		if (pBlockManager != nullptr)
		{
			pBlockManager->Save(&m_aPath[0]);
		}
	}
}

//=====================================================
// �X�e�C�g�̕ύX
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
// �ʏ�u���b�N�̐���
//===================================================================================
//=====================================================
// ����������
//=====================================================
void CStateCreateBlockNormal::Init(CEditBlock *pEdit)
{
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

		// �^�C�v�̏����ݒ�
		m_type = CBlock::TYPE_WALL;

		// ���f���ԍ��̐ݒ�
		m_pObjectCursor->BindModel(pInfoBlock[0].nIdxModel);

		m_pObjectCursor->SetEmissiveCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}
}

//=====================================================
// �I������
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
// �X�V����
//=====================================================
void CStateCreateBlockNormal::Update(CEditBlock *pEdit)
{
	// ���擾
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	D3DXVECTOR3 rot = pEdit->GetRotation();
	D3DXVECTOR3 pos = pEdit->GetPosition();
	float fSpeed = SPEED_MOVE;

	if (pKeyboard != nullptr && pMouse != nullptr && pBlockManager != nullptr)
	{
		if (ImGui::TreeNode("POS"))
		{
			// �u���b�N�ړ�
			ImGui::DragFloat("POS.X", &pos.x, SPEED_MOVE, -FLT_MAX, FLT_MAX);
			ImGui::DragFloat("POS.Y", &pos.y, SPEED_MOVE, -FLT_MAX, FLT_MAX);
			ImGui::DragFloat("POS.Z", &pos.z, SPEED_MOVE, -FLT_MAX, FLT_MAX);

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("ROT"))
		{
			// �u���b�N����
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
			{// �u���b�N�I��
				if (ImGui::Button(&pInfoBlock[i].aTag[0], ImVec2(50.0f, 20.0f)))
				{
					m_nIdxObject = i;

					m_pObjectCursor->BindModel(pInfoBlock[i].nIdxModel);
				}
			}

			ImGui::TreePop();
		}

		if (ImGui::Button("Create", ImVec2(50.0f, 20.0f)))
		{// �u���b�N����
			CreateBlock(m_pObjectCursor->GetPosition());
		}

		// �폜�u���b�N�I��
		CBlock *pBlock = CheckDelete();

		if (ImGui::Button("Delete", ImVec2(60.0f, 20.0f)))
		{// �폜
			pBlock->Uninit();
		}

		// �Z�[�u
		pEdit->Save();

		if (ImGui::Button("DeleteAll", ImVec2(80.0f, 20.0f)))
		{// �S�폜
			CBlockManager *pBlockManager = CBlockManager::GetInstance();

			if (pBlockManager != nullptr)
			{
				pBlockManager->DeleteAll();
			}
		}
	}

	// �G�f�B�b�g�Ƀg�����X�t�H�[����K�p
	pEdit->SetPosition(pos);
	pEdit->SetRotation(rot);

	if (m_pObjectCursor != nullptr)
	{// �J�[�\���̃g�����X�t�H�[��
		m_pObjectCursor->SetPosition(pos);
		m_pObjectCursor->SetRot(rot);
	}
}

//=====================================================
// �u���b�N�̐���
//=====================================================
void CStateCreateBlockNormal::CreateBlock(D3DXVECTOR3 pos)
{
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager == nullptr)
	{
		return;
	}

	CBlockManager::SInfoBlock *pInfoBlock = pBlockManager->GetInfoBlock();

	CBlock *pBlock = CBlock::Create(pInfoBlock[m_nIdxObject].nIdxModel);

	if (pBlock != nullptr)
	{
		pBlock->SetPosition(pos);
		pBlock->SetRot(m_pObjectCursor->GetRot());
		pBlock->SetIdx(m_nIdxObject);
	}
}

//=====================================================
// �폜�u���b�N�̃`�F�b�N
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
			{// �u���b�N���ɂ���Ƃ�
				pBlock->SetEmissiveCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

				return pBlock;
			}
		}

		pBlock = pBlockNext;
	}

	return nullptr;
}