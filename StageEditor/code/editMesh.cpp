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

//=====================================================
// �R���X�g���N�^
//=====================================================
CEditMesh::CEditMesh()
{
	m_pMesh = nullptr;
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

	D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(0.0f, rot.y, 0.0f));

	CEffect3D::Create(pos + vecPole, 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}