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
#include "effect3D.h"
#include "manager.h"
#include "camera.h"
#include <assert.h>

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float SPEED_MOVE = 3.0f;	// �ړ����x
const float SPEED_ROTATION = 0.01f;	// ��]���x
}

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
	if (m_pState != nullptr)
	{
		m_pState->Uninit(this);
		delete m_pState;
		m_pState = nullptr;
	}

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

	// �X�e�C�g�̑I��
	ImGui::Text("[ChangeMode]");

	if (ImGui::Button("CreateNormalBlock", ImVec2(70, 30)))	// �ʏ�u���b�N�̐���
		ChangeState(new CStateCreateBlockNormal);

	if (ImGui::Button("EditGrabBlock", ImVec2(70, 30)))	// �͂߂�u���b�N�̕ҏW
		ChangeState(new CStateEditGrabBlock);

	CEdit::Update();
}

//=====================================================
// �ۑ����s������
//=====================================================
void CEditBlock::Save(void)
{
	ImGui::Text("[Save]");

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
	m_nIdxObject = 0;
	m_pBlockCurrent = nullptr;

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
	D3DXVECTOR3 rotCamera = CManager::GetCamera()->GetCamera()->rot;
	D3DXVECTOR3 pos = pEdit->GetPosition();
	float fSpeed = SPEED_MOVE;

	if (pKeyboard == nullptr || pMouse == nullptr || pBlockManager == nullptr )
		return;

	if (!pMouse->GetPress(CInputMouse::BUTTON_RMB))
	{// �E�N���b�N���ĂȂ��Ƃ��ɁA�ړ��\

		float fMove = SPEED_MOVE;

		if (pKeyboard->GetPress(DIK_LSHIFT) == true)
		{// ����
			fMove *= 7;
		}

		// �u���b�N�ړ�
		if (pKeyboard->GetPress(DIK_A) == true)
		{// ���ړ�
			pos.x -= sinf(rotCamera.y - D3DX_PI * 0.5f) * fMove;
			pos.z -= cosf(rotCamera.y - D3DX_PI * 0.5f) * fMove;
		}
		if (pKeyboard->GetPress(DIK_D) == true)
		{// �E�ړ�
			pos.x -= sinf(rotCamera.y - D3DX_PI * -0.5f) * fMove;
			pos.z -= cosf(rotCamera.y - D3DX_PI * -0.5f) * fMove;
		}
		if (pKeyboard->GetPress(DIK_W) == true)
		{// �O�ړ�
			pos.x -= sinf(D3DX_PI * 0.5f) * sinf(rotCamera.y) * fMove;
			pos.z -= sinf(D3DX_PI * 0.5f) * cosf(rotCamera.y) * fMove;
		}
		if (pKeyboard->GetPress(DIK_S) == true)
		{// ��ړ�
			pos.x -= sinf(-D3DX_PI * 0.5f) * sinf(rotCamera.y) * fMove;
			pos.z -= sinf(-D3DX_PI * 0.5f) * cosf(rotCamera.y) * fMove;
		}
		if (pKeyboard->GetPress(DIK_E) == true)
		{// �㏸
			pos.y += fMove;
		}
		if (pKeyboard->GetPress(DIK_Q) == true)
		{// ���~
			pos.y -= fMove;
		}
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

	if (ImGui::TreeNode("SelectBlockType"))
	{
		for (int i = 0; i < nNumBlock; i++)
		{// �u���b�N�̎�ޑI��
			if (ImGui::Button(&pInfoBlock[i].aTag[0], ImVec2(50.0f, 20.0f)))
			{
				m_nIdxObject = i;

				m_pObjectCursor->BindModel(pInfoBlock[i].nIdxModel);
			}
		}

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("SelectBlock"))
	{
		// �u���b�N�I��
		SelectBlock();

		ImGui::TreePop();
	}

	// �u���b�N�̃r�w�C�r�A�̕ύX
	ChangeBlockBehaviour();

	ImGui::Text("[Action]");

	if (ImGui::Button("Create", ImVec2(50.0f, 20.0f)))
	{// �u���b�N����
		CreateBlock(m_pObjectCursor->GetPosition());
	}

	if (ImGui::Button("DeleteAll", ImVec2(80.0f, 20.0f)))
	{// �S�폜
		CBlockManager *pBlockManager = CBlockManager::GetInstance();

		if (pBlockManager != nullptr)
		{
			pBlockManager->DeleteAll();
		}
	}

	// �Z�[�u
	pEdit->Save();

	// �G�f�B�b�g�Ƀg�����X�t�H�[����K�p
	pEdit->SetPosition(pos);
	pEdit->SetRotation(rot);

	if (m_pObjectCursor != nullptr)
	{// �J�[�\���̃g�����X�t�H�[��
		m_pObjectCursor->SetPosition(pos);
		m_pObjectCursor->SetRotation(rot);
	}
}

//=====================================================
// �u���b�N�̑I��
//=====================================================
void CStateCreateBlockNormal::SelectBlock(void)
{
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager == nullptr)
		return;

	if (m_pBlockCurrent != nullptr)
		m_pBlockCurrent->ResetColor();

	if (ImGui::Button("NextBlock", ImVec2(70, 30)))
	{
		if (m_pBlockCurrent == nullptr)
			m_pBlockCurrent = pBlockManager->GetHead();

		if (m_pBlockCurrent == nullptr)
			return;

		CBlock *pNext = m_pBlockCurrent->GetNext();

		if (pNext != nullptr)
			m_pBlockCurrent = pNext;
	}
	if (ImGui::Button("PrevBlock", ImVec2(70, 30)))
	{
		if (m_pBlockCurrent == nullptr)
			m_pBlockCurrent = pBlockManager->GetHead();

		if (m_pBlockCurrent == nullptr)
			return;

		CBlock *pPrev = m_pBlockCurrent->GetPrev();

		if (pPrev != nullptr)
			m_pBlockCurrent = pPrev;
	}

	if (m_pBlockCurrent != nullptr)
	{
		m_pBlockCurrent->SetEmissiveCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		D3DXVECTOR3 pos = m_pBlockCurrent->GetPosition();

		ImGui::DragFloat("PosSelectBlock.X", &pos.x, 10.0f, -FLT_MAX, FLT_MAX);
		ImGui::DragFloat("PosSelectBlock.Y", &pos.y, 10.0f, -FLT_MAX, FLT_MAX);
		ImGui::DragFloat("PosSelectBlock.Z", &pos.z, 10.0f, -FLT_MAX, FLT_MAX);

		m_pBlockCurrent->SetPosition(pos);
	}

	if (ImGui::Button("DeleteSelectBlock", ImVec2(70, 30)))
	{
		if (m_pBlockCurrent != nullptr)
		{
			m_pBlockCurrent->Uninit();

			m_pBlockCurrent = pBlockManager->GetHead();
		}
	}
}

//=====================================================
// �u���b�N�̃r�w�C�r�A�ύX
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
		{// �r�w�C�r�A�ݒ�
			m_behaviour = (CBlock::BEHAVIOUR)i;
		}
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

//===================================================================================
// �͂ރu���b�N�̕ҏW
//===================================================================================
//=====================================================
// ����������
//=====================================================
void CStateEditGrabBlock::Init(CEditBlock *pEdit)
{
	// �C�e���[�^�[�̏�����
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager == nullptr)
		return;

	std::list<CBlockGrab*> *pList = pBlockManager->GetListGrab();

	m_it = pList->begin();
}

//=====================================================
// �I������
//=====================================================
void CStateEditGrabBlock::Uninit(CEditBlock *pEdit)
{

}

//=====================================================
// �X�V����
//=====================================================
void CStateEditGrabBlock::Update(CEditBlock *pEdit)
{
	// �u���b�N�̑I��
	SelectGrabBlock();

	// �u���b�N�̕ҏW
	EditGrabBlock();
}

//=====================================================
// �u���b�N�̑I��
//=====================================================
void CStateEditGrabBlock::SelectGrabBlock(void)
{
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager == nullptr)
		return;

	// �u���b�N�̑I��
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
// �u���b�N�̕ҏW
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

	(*m_it)->SetFan();
}