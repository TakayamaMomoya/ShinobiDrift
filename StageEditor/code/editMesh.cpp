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

	if (ImGui::Button("Curve", ImVec2(70, 30)))	// �J�[�u�̒���
		ChangeState(new CStateEditMeshCurve);

	if (ImGui::Button("DeleteEdge", ImVec2(70, 30)))	// �ӂ̍폜
		ChangeState(new CStateEditMeshDeleteEdge);
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

//****************************************************************************************
// �J�[�u�̒���
//****************************************************************************************
CStateEditMeshCurve::CStateEditMeshCurve() : m_bStart(false), m_bEnd(false), m_fAngleCurve(0.0f)
{
	CMeshRoad *pMeshRoad = MeshRoad::GetInstance();
	pMeshRoad->ResetIterator();
}

void CStateEditMeshCurve::Update(CEditMesh *pEdit)
{
	// �ӂ̑I��
	std::vector<CMeshRoad::SInfoEdge>::iterator it = CMeshRoad::GetInstance()->SelectEdge();

	// �I�����Ă���ӂ̏�ɃG�t�F�N�g���o��
	D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, it->fRot, 0.0f));
	CEffect3D::Create(it->pos + vecPole * 200.0f, 50.0f, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CEffect3D::Create(it->pos - vecPole * 200.0f, 50.0f, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard == nullptr)
		return;

	if (pKeyboard->GetTrigger(DIK_SPACE))
	{// �ӂ̑I��
		SetEdge(it);
	}

	if (pKeyboard->GetTrigger(DIK_R))
	{// �I��ӂ̍폜
		m_bStart = false;
		m_bEnd = false;
	}

	// �I�������ӂɃG�t�F�N�g���o��
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
	{// �J�[�u�̋����̒���
		SetCurve();
	}
}

void CStateEditMeshCurve::SetEdge(std::vector<CMeshRoad::SInfoEdge>::iterator it)
{// �ŏ��ƍŌ�̕ӂ̐ݒ�
	if (!m_bStart)
	{// �ŏ��̕Ӑݒ�
		m_itStart = it;
		m_bStart = true;
	}
	else if (!m_bEnd)
	{// �Ō�̕ӂ�ݒ�
		m_itEnd = it;
		m_bEnd = true;
	}
}

void CStateEditMeshCurve::SetCurve(void)
{// �J�[�u�̒���
	ImGui::DragFloat("AngleCurve", &m_fAngleCurve, 1.0f, -FLT_MAX, FLT_MAX);

	// �ӂ��J�[�u�ɉ����Đݒ�
	D3DXVECTOR3 posStart = m_itStart->pos;
	D3DXVECTOR3 posEnd = m_itEnd->pos;
	D3DXVECTOR3 vecDiff = posEnd - posStart;
	D3DXVECTOR3 posMid = posStart + vecDiff * 0.5f;

	CEffect3D::Create(posMid, 50.0f, 3, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));	// ���S���W�̃G�t�F�N�g

	// �ӂ̃��X�g�̎擾
	CMeshRoad *pMeshRoad = MeshRoad::GetInstance();
	std::vector<CMeshRoad::SInfoEdge> *pList = pMeshRoad->GetList();

	ptrdiff_t distance = std::distance(m_itStart, m_itEnd);	// �C�e���[�^�[���m�̋���

	int nCntEdge = 1;
	for (auto it = m_itStart; it != m_itEnd - 1; it++)
	{// �ŏ��̕ӂ���Ō�̕ӂ̊Ԃ��`�F�b�N
		ptrdiff_t distanceCurrent = std::distance(it, m_itEnd);
		float fRate = (float)nCntEdge / (distance);
		fRate -= 0.5f;

		D3DXVECTOR3 posEdge = posMid + vecDiff * fRate;	// �ӗ\���ʒu�̐���

		// �������̌v�Z
		float fLength = universal::ParabolaY(fRate, -m_fAngleCurve);
		D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, it->fRot, 0.0f)) * fLength;
		posEdge += vecPole;

		// ���炷���̕������̌v�Z
		fRate = 1.0f / (distance);
		fRate -= 0.5f;
		fLength = universal::ParabolaY(fRate, -m_fAngleCurve);
		posEdge -= universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, it->fRot, 0.0f)) * fLength;

		CEffect3D::Create(posEdge, 50.0f, 3, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));	// �Ȃ�������̃G�t�F�N�g

		// �ӂ̌���
		CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
		
		if (pKeyboard->GetTrigger(DIK_RETURN))
		{
			it->pos = posEdge;

			
		}

		nCntEdge++;
	}
}

//****************************************************************************************
// �ӂ̍폜
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