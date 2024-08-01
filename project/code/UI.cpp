//*****************************************************
//
// UI�̏���[UI.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "UI.h"
#include "UIManager.h"
#include "blur.h"

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CUI::CUI(int nPriority) : CPolygon2D(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CUI::~CUI()
{

}

//=====================================================
// ��������
//=====================================================
CUI *CUI::Create(void)
{
	CUI *pUI = nullptr;

	if (pUI == nullptr)
	{
		// �C���X�^���X����
		pUI = new CUI;

		if (pUI != nullptr)
		{
			// ����������
			pUI->Init();
		}
	}

	return pUI;
}

//=====================================================
// ������
//=====================================================
HRESULT CUI::Init(void)
{
	CPolygon2D::Init();

	EnableBlur(false);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CUI::Uninit(void)
{
	CPolygon2D::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CUI::Update(void)
{
	CPolygon2D::Update();
}

//=====================================================
// �`��
//=====================================================
void CUI::Draw(void)
{
	bool bDisp = true;

	CUIManager *pUIManager = CUIManager::GetInstance();

	if (pUIManager != nullptr)
	{// �`�悷�邩�̎擾
		bDisp = pUIManager->IsDisp();
	}

	if (bDisp)
	{
		CPolygon2D::Draw();
	}
}

//=====================================================
// �T�C�Y�̐ݒ�
//=====================================================
void CUI::SetSize(float width, float height)
{
	float fWidth;
	float fHeigth;

	fWidth = SCREEN_WIDTH * width;
	fHeigth = SCREEN_WIDTH * height;

	CPolygon2D::SetSize(fWidth, fHeigth);
}

//=====================================================
// �T�C�Y�̎擾
//=====================================================
D3DXVECTOR2 CUI::GetSize(void)
{
	D3DXVECTOR2 size = CPolygon2D::GetSize();

	size.x /= SCREEN_WIDTH;
	size.y /= SCREEN_HEIGHT;

	return size;
}

//=====================================================
// �ʒu�ݒ�
//=====================================================
void CUI::SetPosition(D3DXVECTOR3 pos)
{
	pos.x *= SCREEN_WIDTH;
	pos.y *= SCREEN_HEIGHT;

	CPolygon2D::SetPosition(pos);
}

//=====================================================
// �ʒu�擾
//=====================================================
D3DXVECTOR3 CUI::GetPosition(void)
{
	D3DXVECTOR3 pos = CPolygon2D::GetPosition();

	pos.x /= SCREEN_WIDTH;
	pos.y /= SCREEN_HEIGHT;

	return pos;
}