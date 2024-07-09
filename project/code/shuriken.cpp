//*****************************************************
//
// �藠���̏���[shuriken.h]
// Author:�匴�叫
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "shuriken.h"
#include "effekseer.h"
#include "model.h"
#include "player.h"
#include "debugproc.h"

//*****************************************************
// �ÓI�����o�ϐ�
//*****************************************************
std::list<CShuriken*> CShuriken::m_aShuriken;

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const float MOVE_SPEED = 0.05f;  // �ړ���
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CShuriken::CShuriken()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CShuriken::~CShuriken()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CShuriken::Init(void)
{
	// �p���N���X�̏�����
	CObjectX::Init();

	// ���f���Ǎ�
	int nIdx = CModel::Load("data\\MODEL\\Player\\02_head.x");
	BindModel(nIdx);

	m_aShuriken.push_back(this);

	// �v���C���[�擾
	CPlayer* pPlayer = CPlayer::GetInstance();

	// �v���C���[�̑��x�擾
	float PlayerSpeed = pPlayer->GetSpeed();

	// �v���C���[�̓��̃}�g���b�N�X�擾
	m_PlayerMtx = *pPlayer->GetParts(2)->pParts->GetMatrix();

	// �v���C���[�̈ʒu�ɑ��x�����Z
	m_PlayerMtx._41 += (PlayerSpeed * 5.0f);
	m_PlayerMtx._43 += (PlayerSpeed * 5.0f);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CShuriken::Uninit(void)
{
	// �p���N���X�̏�����
	CObjectX::Uninit();

	m_aShuriken.remove(this);
}

//=====================================================
// �X�V����
//=====================================================
void CShuriken::Update(void)
{
	// �p���N���X�̏�����
	CObjectX::Update();

	// �v���C���[�̈ʒu�Ɍ�����
	MoveToPlayer();

	// �f�o�b�O�v���b�N�擾
	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
		return;

	pDebugProc->Print("\n�藠���̈ʒu[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
}

//=====================================================
// �`�揈��
//=====================================================
void CShuriken::Draw(void)
{
	// �p���N���X�̏�����
	CObjectX::Draw();
}

//=====================================================
// ��������
//=====================================================
CShuriken* CShuriken::Create(D3DXVECTOR3 pos)
{
	CShuriken *pShuriken = nullptr;
	pShuriken = new CShuriken;

	if (pShuriken != nullptr)
	{
		pShuriken->Init();
		pShuriken->SetPosition(pos);
	}
		
	return pShuriken;
}

//=====================================================
// �v���C���[�Ɍ������Ĉړ����鏈��
//=====================================================
void CShuriken::MoveToPlayer(void)
{
	// �v���C���[�擾
	CPlayer* pPlayer = CPlayer::GetInstance();

	// �����̈ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 Playerpos = {};

	//Playerpos = universal::LinePridiction(pos, MOVE_SPEED, D3DXVECTOR3(m_PlayerMtx._41, m_PlayerMtx._42 + 200.0f, m_PlayerMtx._43), pPlayer->GetMove());

	// �ڕW�̈ʒu�Ɍ�����
	universal::MoveToDest(&pos, D3DXVECTOR3(m_PlayerMtx._41, m_PlayerMtx._42 + 200.0f, m_PlayerMtx._43), MOVE_SPEED);

	// �ʒu�ݒ�
	SetPosition(pos);
}