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
// �萔��`
//*****************************************************
namespace
{
	
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

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CShuriken::Uninit(void)
{
	// �p���N���X�̏�����
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CShuriken::Update(void)
{
	// �p���N���X�̏�����
	CObjectX::Update();

	// �v���C���[�̈ʒu�Ɍ�����
	MoveToPlyaer();

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
void CShuriken::MoveToPlyaer(void)
{
	// �����̈ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �v���C���[�̎擾�ƈʒu�擾
	CPlayer* pPlayer = CPlayer::GetInstance();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();
	D3DXMATRIX PlayerMatrix = *pPlayer->GetParts(2)->pParts->GetMatrix();
	

	// �ڕW�̈ʒu�Ɍ�����
	universal::MoveToDest(&pos, D3DXVECTOR3(PlayerMatrix._41, PlayerMatrix._42 + 200.0f, PlayerMatrix._43), 0.05f);

	// �ʒu�ݒ�
	SetPosition(pos);
}