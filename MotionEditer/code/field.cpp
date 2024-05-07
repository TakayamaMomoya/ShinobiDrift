//*****************************************************
//
// �n�ʂ̏���[field.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "field.h"
#include "manager.h"
#include "texture.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CField::CField()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CField::~CField()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CField::Init(void)
{
	// �p���N���X�̏�����
	CObject3D::Init();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CField::Uninit(void)
{
	// �p���N���X�̏I��
	CObject3D::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CField::Update(void)
{
	// �p���N���X�̍X�V
	CObject3D::Update();
}

//=====================================================
// �`�揈��
//=====================================================
void CField::Draw(void)
{
	// �p���N���X�̕`��
	CObject3D::Draw();
}

//=====================================================
// ��������
//=====================================================
CField *CField::Create(D3DXVECTOR2 tex,D3DXVECTOR3 pos,float width,float height)
{
	CField *pField = NULL;

	if (pField == NULL)
	{
		pField = new CField;

		if (pField != NULL)
		{
			pField->SetPosition(pos);
			pField->SetSize(width, height);

			// ����������
			pField->Init();

			// �e�N�X�`���̓Ǎ�
			int nIdx = CManager::GetTexture()->Regist("data\\TEXTURE\\BG\\metal000.jpg");
			pField->SetIdxTexture(nIdx);
		}
	}

	return pField;
}