//*****************************************************
//
// �Ԃ̏���[flower.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "flower.h"
#include "collision.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float RADIUS_COLLISION = 100.0f;	// �����蔻��̔��a
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CFlower::m_nNumAll = 0;	// ����

//=====================================================
// �R���X�g���N�^
//=====================================================
CFlower::CFlower(int nPriority)
{
	m_pCollisionSphere = nullptr;

	m_nNumAll++;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CFlower::~CFlower()
{
	m_nNumAll--;
}

//=====================================================
// ��������
//=====================================================
CFlower *CFlower::Create(void)
{
	CFlower *pFlower = nullptr;

	if (pFlower == nullptr)
	{
		pFlower = new CFlower;

		if (pFlower != nullptr)
		{
			pFlower->Init();
		}
	}

	return pFlower;
}

//=====================================================
// ����������
//=====================================================
HRESULT CFlower::Init(void)
{
	// �p���N���X�̏�����
	CObjectX::Init();

	// �e�̗L����
	EnableShadow(true);

	if (m_pCollisionSphere == nullptr)
	{// �����蔻�萶��
		m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_FLOWER, CCollision::TYPE_SPHERE, this);

		if (m_pCollisionSphere != nullptr)
		{
			m_pCollisionSphere->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_pCollisionSphere->SetRadius(RADIUS_COLLISION);
		}
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CFlower::Uninit(void)
{
	// �����蔻��폜
	DeleteCollision();

	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �����蔻��̍폜
//=====================================================
void CFlower::DeleteCollision(void)
{
	if (m_pCollisionSphere != nullptr)
	{// �����蔻��̏���
		m_pCollisionSphere->Uninit();

		m_pCollisionSphere = nullptr;
	}
}

//=====================================================
// �X�V����
//=====================================================
void CFlower::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();
}

//=====================================================
// �`�揈��
//=====================================================
void CFlower::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}

//=====================================================
// �ʒu�ݒ�
//=====================================================
void CFlower::SetPosition(D3DXVECTOR3 pos)
{
	if (m_pCollisionSphere != nullptr)
	{
		m_pCollisionSphere->SetPosition(pos);
	}

	CObjectX::SetPosition(pos);
}

//=====================================================
// �q�b�g����
//=====================================================
void CFlower::Hit(float fDamage)
{
	DeleteCollision();
}