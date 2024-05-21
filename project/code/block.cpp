//*****************************************************
//
// �u���b�N�̏���[block.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "block.h"
#include "blockManager.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "debrisSpawner.h"
#include "effect3D.h"
#include "debugproc.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const float SPEED_MOVE(1.0f);	// �ړ����x
	const char* MAP_FILE = "data\\MAP\\map01.bin";	// �}�b�v�̃t�@�C���p�X
	const float RADIUS_DRIFT_DEFAULT = 1000.0f;	// �h���t�g���a�̃f�t�H���g�l
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CBlock::m_nNumAll = 0;	// ����

//=====================================================
// �R���X�g���N�^
//=====================================================
CBlock::CBlock(int nPriority)
{
	m_fLife = 0.0f;
	m_pPrev = nullptr;
	m_pNext = nullptr;
	m_nIdx = -1;
	m_bGrab = true;
	m_bCurrent = false;

	// �擪�A�Ō���A�h���X�擾
	CBlockManager *pManager = CBlockManager::GetInstance();
	CBlock *pHead = nullptr;
	CBlock *pTail = nullptr;

	if (pManager != nullptr)
	{
		pHead = pManager->GetHead();
		pTail = pManager->GetTail();
	}

	if (pHead == nullptr)
	{// �擪�ƍŌ���A�h���X�̑��
		pManager->SetHead(this);
		pManager->SetTail(this);

		return;
	}

	// �O�̃A�h���X�ɍŌ���̃A�h���X��������
	m_pPrev = pTail;

	// �Ō���̃A�h���X�������ɂ���
	pManager->SetTail(this);

	if (m_pPrev != nullptr)
	{
		// �O�̃I�u�W�F�N�g�̎��̃A�h���X�������ɂ���
		m_pPrev->m_pNext = this;
	}

	m_nNumAll++;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CBlock::~CBlock()
{
	// �擪�A�Ō���A�h���X�擾
	CBlockManager *pManager = CBlockManager::GetInstance();
	CBlock *pHead = nullptr;
	CBlock *pTail = nullptr;

	if (pManager != nullptr)
	{
		pHead = pManager->GetHead();
		pTail = pManager->GetTail();
	}

	m_nNumAll--;

	if (pTail != this && pHead != this)
	{// �^�񒆂̃A�h���X�̔j��
		if (m_pPrev != nullptr)
		{
			// �O�̃A�h���X���玟�̃A�h���X���Ȃ�
			m_pPrev->m_pNext = m_pNext;
		}

		if (m_pNext != nullptr)
		{
			// ���̃A�h���X����O�̃A�h���X���Ȃ�
			m_pNext->m_pPrev = m_pPrev;
		}
	}

	if (pHead == this)
	{// �擪�A�h���X�̔j��
		//if (m_pNext != nullptr)
		{// �擪�A�h���X�����̃A�h���X�Ɉ����p��
			pManager->SetHead(m_pNext);

			if (m_pNext != nullptr)
			{
				m_pNext->m_pPrev = nullptr;
			}
		}
	}

	if (pTail == this)
	{// �Ō���A�h���X�̔j��
		if (m_pPrev != nullptr)
		{// �Ō���A�h���X��O�̃A�h���X�Ɉ����p��
			pManager->SetTail(m_pPrev);

			m_pPrev->m_pNext = nullptr;
		}
	}

	m_nNumAll--;
}

//=====================================================
// ��������
//=====================================================
CBlock *CBlock::Create(int nIdxModel)
{
	CBlock *pBlock = nullptr;

	if (pBlock == nullptr)
	{// �C���X�^���X����
		pBlock = new CBlock;

		// ����������
		pBlock->Init();

		// ��ނ��Ƃ̃��f���Ǎ�
		pBlock->BindModel(nIdxModel);
	}

	return pBlock;
}

//=====================================================
// ����������
//=====================================================
HRESULT CBlock::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �p���N���X�̏�����
	CObjectX::Init();

	// �^�C�v�̐ݒ�
	SetType(TYPE_BLOCK);

	m_fLife = 300.0f;

	// �e�̗L����
	EnableShadow(true);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CBlock::Uninit(void)
{
	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CBlock::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();

	if (m_bCurrent)
	{
		CEffect3D::Create(GetPosition(),200.0f,5,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	}
}

//=====================================================
// �͂߂邩�̔���
//=====================================================
bool CBlock::CanGrab(D3DXVECTOR3 pos)
{
	bool bCanGrab = true;

	// ����̐ݒu
	D3DXMATRIX mtxVec;
	D3DXMATRIX mtx = *GetMatrix();
	universal::SetOffSet(&mtxVec, mtx, D3DXVECTOR3(200.0f, 0.0f, 0.0f));

	D3DXVECTOR3 posMtx = { mtxVec._41,mtxVec._42 ,mtxVec._43 };

#ifdef _DEBUG
	CEffect3D::Create(posMtx, 100.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
#endif

	bCanGrab = universal::IsCross(pos, GetPosition(), posMtx, nullptr);

	CDebugProc::GetInstance()->Print("\n�͂߂�[%d]", bCanGrab);

	return bCanGrab;
}

//=====================================================
// �ʒu�ݒ�
//=====================================================
void CBlock::SetPosition(D3DXVECTOR3 pos)
{
	CObjectX::SetPosition(pos);
}

//=====================================================
// �`�揈��
//=====================================================
void CBlock::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}

//=====================================================
// �q�b�g����
//=====================================================
void CBlock::Hit(float fDamage)
{

}

//=====================================================
// ���_�����ւ��鏈��
//=====================================================
void CBlock::SetRotation(D3DXVECTOR3 rot)
{
	CObjectX::SetRotation(rot);
}