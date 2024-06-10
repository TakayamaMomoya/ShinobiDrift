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
#include "camera.h"
#include "manager.h"

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
	m_pState = nullptr;
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

	// �X�e�C�g�ɂ�郂�[�h�̐؂�ւ�
	ImGui::Text("ModeSelect");

	if (ImGui::Button("CreateEdge", ImVec2(70, 30)))	// ���b�V������
		ChangeState(new CStateEditMeshCreateMesh);

	if (ImGui::Button("AdjustRoadPoint", ImVec2(70, 30)))	// ���[�h�|�C���g�̒���
		ChangeState(new CStateEditMeshAdjustRoadPoint);

	if (ImGui::Button("DeleteRoadPoint", ImVec2(70, 30)))	// �ӂ̍폜
		ChangeState(new CStateEditMeshDeleteRoadPoint);
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
	D3DXVECTOR3 rot = CManager::GetCamera()->GetCamera()->rot;

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
			pos.x += sinf(rot.y - D3DX_PI * 0.5f) * fMove;
			pos.z += cosf(rot.y - D3DX_PI * 0.5f) * fMove;
		}
		if (pKeyboard->GetPress(DIK_D) == true)
		{// �E�ړ�
			pos.x += sinf(rot.y - D3DX_PI * -0.5f) * fMove;
			pos.z += cosf(rot.y - D3DX_PI * -0.5f) * fMove;
		}
		if (pKeyboard->GetPress(DIK_W) == true)
		{// �O�ړ�
			pos.x += sinf(D3DX_PI * 0.5f) * sinf(rot.y) * fMove;
			pos.z += sinf(D3DX_PI * 0.5f) * cosf(rot.y) * fMove;
		}
		if (pKeyboard->GetPress(DIK_S) == true)
		{// ��ړ�
			pos.x += sinf(-D3DX_PI * 0.5f) * sinf(rot.y) * fMove;
			pos.z += sinf(-D3DX_PI * 0.5f) * cosf(rot.y) * fMove;
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

		// �ʒu�̐���
		LimitPos(&pos);

		pEdit->SetRotation(rot);
		pEdit->SetPosition(pos);
	}

	if (pKeyboard->GetTrigger(DIK_SPACE))
	{// ���[�h�|�C���g�̒ǉ�
		CMeshRoad *pMesh = CMeshRoad::GetInstance();

		pMesh->AddRoadPoint(pos, true);
	}
	
	if (ImGui::Button("Save", ImVec2(100, 50)))
	{// �ۑ�
		CMeshRoad *pMesh = CMeshRoad::GetInstance();

		if (pMesh != nullptr)
			pMesh->Save();
	}
}

void CStateEditMeshCreateMesh::LimitPos(D3DXVECTOR3 *pPos)
{// �ʒu�̐���
	// ���X�g�̎擾
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
// ���[�h�|�C���g�̒���
//****************************************************************************************
CStateEditMeshAdjustRoadPoint::CStateEditMeshAdjustRoadPoint()
{// �R���X�g���N�^
	CMeshRoad *pMesh = MeshRoad::GetInstance();

	pMesh->ResetIterator();
}

void CStateEditMeshAdjustRoadPoint::Update(CEditMesh *pEdit)
{
	CMeshRoad *pMesh = MeshRoad::GetInstance();

	// ���[�h�|�C���g�̑I��
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator it = pMesh->SelectRoadPoint();

	D3DXVECTOR3 pos = it->pos;

	ImGui::DragFloat("posRoadPointPOS.X", &pos.x, 2.0f, -FLT_MAX, FLT_MAX);
	ImGui::DragFloat("posRoadPointPOS.Y", &pos.y, 2.0f, -FLT_MAX, FLT_MAX);
	ImGui::DragFloat("posRoadPointPOS.Z", &pos.z, 2.0f, -FLT_MAX, FLT_MAX);

	it->pos = pos;

	pMesh->CreateVtxBuffEdge();
}

//****************************************************************************************
// �ӂ̍폜
//****************************************************************************************
CStateEditMeshDeleteRoadPoint::CStateEditMeshDeleteRoadPoint()
{// �R���X�g���N�^
	CMeshRoad *pMesh = MeshRoad::GetInstance();

	pMesh->ResetIterator();
}

void CStateEditMeshDeleteRoadPoint::Update(CEditMesh *pEdit)
{
	CMeshRoad *pMesh = MeshRoad::GetInstance();

	// �ӂ̑I��
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator it = pMesh->SelectRoadPoint();

	if (ImGui::Button("Delete", ImVec2(100, 50)))
	{
		CMeshRoad::GetInstance()->DeleteEdge(it);

		return;
	}
}