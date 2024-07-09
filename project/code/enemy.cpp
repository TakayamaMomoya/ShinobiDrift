//*****************************************************
//
// �G�l�~�[�̏���[enemy.cpp]
// Author:�匴�叫
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "enemy.h"
#include "debugproc.h"
#include "effect3D.h"
#include "shuriken.h"
#include "player.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const float SPEED_DEFAULT = 50.0f;
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemy::CEnemy(int nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemy::~CEnemy()
{

}

//=====================================================
// ��������
//=====================================================
CEnemy* CEnemy::Create()
{
	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{
		pEnemy = new CEnemy;

		if (pEnemy != nullptr)
		{
			// ������
			pEnemy->Init();
		}
	}

	return pEnemy;
}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemy::Init(void)
{
	// �p���N���X�̏�����
	CMotion::Init();

	// ���f���̐ݒ�
	CMotion::Load("data\\MOTION\\motionEnemy.txt");

	CEnemyBehaviour *pBehaviour = new CEnemyBehaviourChasePlayer;

	pBehaviour->Init(this);

	m_listBehaviour.push_back(pBehaviour);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemy::Uninit(void)
{
	// �S�r�w�C�r�A���
	ReleaseAllBehaviour();

	// �p���N���X�̏I��
	CMotion::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemy::Update(void)
{
	// �p���N���X�̍X�V
	CMotion::Update();

	// �r�w�C�r�A�̍X�V
	for (auto it : m_listBehaviour)
	{
		it->Update(this);
	}
}

//=====================================================
// �S�r�w�C�r�A���
//=====================================================
void CEnemy::ReleaseAllBehaviour(void)
{
	for (auto it : m_listBehaviour)
	{
		it->Uninit(this);
	}

	m_listBehaviour.clear();
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemy::Draw(void)
{
	// �p���N���X�̕`��
	CMotion::Draw();
}