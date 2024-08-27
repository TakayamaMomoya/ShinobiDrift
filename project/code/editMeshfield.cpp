//*****************************************************
//
// ���b�V���t�B�[���h�G�f�B�^�[�̏���[editMeshfield.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "editMeshfield.h"
#include "meshfield.h"
#include "meshcylinder.h"
#include "inputmouse.h"
#include "inputkeyboard.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float DEFAULT_DEPTH = 100.0f;	// �f�t�H���g�̐[��
const float DEFAULT_RADIUS = 1000.0f;	// �f�t�H���g�͈̔�
const float HEIGHT_CYLINDER = 50000.0f;	// �V�����_�[�̍���
const float SPEED_CHANGE_DEPTH = 10.0f;	// �[���ύX�̑��x
const float SPEED_CHANGE_RADIUS = 10.0f;	// ���a�ύX�̑��x
const string DEFAULT_PATH = "data\\MAP\\field00.bin";	// �f�t�H���g�ۑ��p�X
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CEditMeshfield::CEditMeshfield() : m_fDepthDent(0.0f), m_fRadiusDent(0.0f), m_pMeshCylinder(nullptr)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEditMeshfield::~CEditMeshfield()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CEditMeshfield::Init(void)
{
	CEdit::Init();

	m_fDepthDent = DEFAULT_DEPTH;
	m_fRadiusDent = DEFAULT_RADIUS;

	// ���b�V���V�����_�[����
	m_pMeshCylinder = CMeshCylinder::Create();

	if (m_pMeshCylinder != nullptr)
	{
		m_pMeshCylinder->SetIdxTexture(-1);
	}

	// �f�t�H���g�p�X
	strcpy(&m_aSave[0], &DEFAULT_PATH[0]);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEditMeshfield::Uninit(void)
{
	if (m_pMeshCylinder != nullptr)
	{
		m_pMeshCylinder->Uninit();
		m_pMeshCylinder = nullptr;
	}

	CEdit::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEditMeshfield::Update(void)
{
	CEdit::Update();

	// �J�[�\���𓮂�������
	MoveCursor();

	// �p�����[�^�[�̐ݒ�
	ChangeParam();

	// ���b�V���t�B�[���h���ւ��܂�����
	DentMeshField();

	// �������̃{�^��
	OtherButton();
}

//=====================================================
// �J�[�\���𓮂�������
//=====================================================
void CEditMeshfield::MoveCursor(void)
{
	D3DXVECTOR3 posNear;
	D3DXVECTOR3 posFar;
	D3DXVECTOR3 vecDiff;
	D3DXVECTOR3 posHit;

	universal::ConvertScreenPosTo3D(&posNear, &posFar, &vecDiff);

	universal::CalcRayFlat(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), posNear, posFar, &posHit);

	SetPosition(posHit);

	if (m_pMeshCylinder != nullptr)
	{
		m_pMeshCylinder->SetPosition(posHit);
		m_pMeshCylinder->SetHeight(HEIGHT_CYLINDER);
		m_pMeshCylinder->SetRadius(m_fRadiusDent);
		m_pMeshCylinder->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));

		m_pMeshCylinder->SetVtx();
	}
}

//=====================================================
// �p�����[�^�[�̕ύX
//=====================================================
void CEditMeshfield::ChangeParam(void)
{
	CInputMouse *pMouse = CInputMouse::GetInstance();

	if (pMouse == nullptr)
		return;

	// �ւ��܂���[���̕ύX
	ImGui::DragFloat("Depth", &m_fDepthDent, SPEED_CHANGE_DEPTH, -FLT_MAX, FLT_MAX);

	if (pMouse->GetMoveIZ() > 0)	// �}�E�X�ł̒l����
		m_fDepthDent += SPEED_CHANGE_DEPTH;
	else if(pMouse->GetMoveIZ() < 0)
		m_fDepthDent -= SPEED_CHANGE_DEPTH;

	// �u���V�̔��a��ύX
	ImGui::DragFloat("Radius", &m_fRadiusDent, SPEED_CHANGE_RADIUS, -FLT_MAX, FLT_MAX);
}

//=====================================================
// ���b�V���t�B�[���h���ւ��܂�����
//=====================================================
void CEditMeshfield::DentMeshField(void)
{
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard == nullptr)
		return;

	if (!pKeyboard->GetPress(DIK_SPACE))
		return;

	CMeshField *pMeshField = CMeshField::GetInstance();

	if (pMeshField == nullptr)
		return;

	D3DXVECTOR3 pos = GetPosition();

	pMeshField->Dent(pos, m_fRadiusDent, m_fDepthDent);
}

//=====================================================
// �������̃{�^��
//=====================================================
void CEditMeshfield::OtherButton(void)
{
	CMeshField *pMesh = CMeshField::GetInstance();

	if (pMesh == nullptr)
		return;

	// �@���ݒ�
	if (ImGui::Button("SetNormal"))
		pMesh->SetNormal();

	// �ۑ�
	if (ImGui::Button("Save"))
		pMesh->Save(&m_aSave[0]);

	// �Ǎ�
	if (ImGui::Button("Load"))
		pMesh->Load(&m_aSave[0]);

	// ���Z�b�g
	if (ImGui::Button("Reset"))
		pMesh->Reset();

	// �e�L�X�g��������
	ImGui::InputText("Savepath", &m_aSave[0],MAX_STRING);
}