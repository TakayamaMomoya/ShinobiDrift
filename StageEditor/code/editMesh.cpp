//*****************************************************
//
// �u���b�N�G�f�B�^�[�̏���[editBlock.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "editMesh.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "effect3D.h"
#include "meshRoad.h"
#include "objectX.h"
#include "debugproc.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float SPEED_MOVE = 5.0f;	// �ړ����x
const float SPEED_ROLL = 0.05f;	// ��]���x
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CEditMesh::CEditMesh()
{
	m_pMesh = nullptr;
	m_pManipulator = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEditMesh::~CEditMesh()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CEditMesh::Init(void)
{
	CEdit::Init();

	// �}�j�s�����[�^�̐���
	m_pManipulator = CObjectX::Create();

	// ���f���̊��蓖��
	int nIdx = CModel::Load("data\\MODEL\\block\\manipulator.x");
	m_pManipulator->BindModel(nIdx);

	ChangeState(new CStateEditMeshCreateMesh);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEditMesh::Uninit(void)
{
	CEdit::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEditMesh::Update(void)
{
	CEdit::Update();

	// �}�j�s�����[�^�[�̃g�����X�t�H�[���X�V
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	m_pManipulator->SetPosition(pos);
	m_pManipulator->SetRot(rot);

	if (m_pState != nullptr)	// �X�e�C�g�̍X�V
		m_pState->Update(this);
}

//=====================================================
// �X�e�C�g�̕ύX
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
// ���b�V���̐���
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
	{// �E�N���b�N���ĂȂ��Ƃ��ɁA�ړ��\
		float fMove = SPEED_MOVE;

		if (pKeyboard->GetPress(DIK_LSHIFT) == true)
		{// ����
			fMove *= 7;
		}

		// ���_�ړ�===============================================
		if (pKeyboard->GetPress(DIK_A) == true)
		{// ���ړ�
			pos.x -= sinf(rot.y - D3DX_PI * 0.5f) * fMove;
			pos.z -= cosf(rot.y - D3DX_PI * 0.5f) * fMove;
		}
		if (pKeyboard->GetPress(DIK_D) == true)
		{// �E�ړ�
			pos.x -= sinf(rot.y - D3DX_PI * -0.5f) * fMove;
			pos.z -= cosf(rot.y - D3DX_PI * -0.5f) * fMove;
		}
		if (pKeyboard->GetPress(DIK_W) == true)
		{// �O�ړ�
			pos.x += sinf(rot.x - D3DX_PI * 0.5f) * sinf(rot.y) * fMove;
			pos.y -= cosf(rot.x - D3DX_PI * 0.5f) * fMove;
			pos.z += sinf(rot.x - D3DX_PI * 0.5f) * cosf(rot.y) * fMove;
		}
		if (pKeyboard->GetPress(DIK_S) == true)
		{// ��ړ�
			pos.x += sinf(rot.x + D3DX_PI * 0.5f) * sinf(rot.y) * fMove;
			pos.y -= cosf(rot.x + D3DX_PI * 0.5f) * fMove;
			pos.z += sinf(rot.x + D3DX_PI * 0.5f) * cosf(rot.y) * fMove;
		}
		if (pKeyboard->GetPress(DIK_E) == true)
		{// �㏸
			pos.y += fMove;
		}
		if (pKeyboard->GetPress(DIK_Q) == true)
		{// ���~
			pos.y -= fMove;
		}

		// ��]
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
	CDebugProc::GetInstance()->Print("�I�t�Z�b�g[%f,%f,%f]", posD.x, posD.y, posD.z);
	posD = pos - vecPole * 200.0f;
	CDebugProc::GetInstance()->Print("�I�t�Z�b�g[%f,%f,%f]", posD.x, posD.y, posD.z);

	if (pKeyboard->GetTrigger(DIK_SPACE))
	{// ���b�V���̒ǉ�
		CMeshRoad *pMesh = CMeshRoad::GetInstance();

		pMesh->AddEdge(pos, rot.y - D3DX_PI * 0.5f, true);

		D3DXVECTOR3 pos = pos + vecPole * 200.0f;
		CDebugProc::GetInstance()->Print("�I�t�Z�b�g[%f,%f,%f]", pos.x, pos.y, pos.z);
		pos = pos - vecPole * 200.0f;
		CDebugProc::GetInstance()->Print("�I�t�Z�b�g[%f,%f,%f]", pos.x, pos.y, pos.z);
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