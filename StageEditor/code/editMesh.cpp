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

	// ���f���ԍ��̐ݒ�
	int nIdx = CModel::Load("data\\MODEL\\block\\manipulator.x");
	m_pManipulator->BindModel(nIdx);

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
	// ���擾
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();

	CEdit::Update();

	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

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

		SetRotation(rot);
		SetPosition(pos);

		m_pManipulator->SetPosition(pos);
		m_pManipulator->SetRot(rot);
	}

	if (pKeyboard->GetTrigger(DIK_SPACE))
	{// ���b�V���̒ǉ�
		CMeshRoad *pMesh = CMeshRoad::GetInstance();

		pMesh->AddEdge(pos, rot.y - D3DX_PI * 0.5f,true);
	}
}