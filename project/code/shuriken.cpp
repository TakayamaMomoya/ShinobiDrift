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
#include "manager.h"
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
	const float MOVE_SPEED = 30.0f;  // �X�s�[�h
	const float LIFE_DEFAULT = 5.0f;	// �f�t�H���g�̎���
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CShuriken::CShuriken() : m_fLife(0.0f)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CShuriken::~CShuriken()
{

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
		pShuriken->SetPosition(pos);
		pShuriken->Init();
	}

	return pShuriken;
}

//=====================================================
// ����������
//=====================================================
HRESULT CShuriken::Init(void)
{
	CObjectX::Init();

	// ���f���Ǎ�
	int nIdx = CModel::Load("data\\MODEL\\Player\\shuriken.x");
	BindModel(nIdx);

	m_aShuriken.push_back(this);

	// �v���C���[�擾
	CPlayer* pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return E_FAIL;

	// �v���C���[�̈ړ��x�N�g���擾
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();
	movePlayer.y = 0.0f;

	// �v���C���[�̓��̃}�g���b�N�X�擾
	D3DXVECTOR3 posHeadPlayer = pPlayer->GetNInjaBody()->GetMtxPos(2);

	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 vecDiff = posHeadPlayer - pos;

	universal::VecConvertLength(&vecDiff, MOVE_SPEED);

	D3DXVECTOR3 move = movePlayer + vecDiff;

	SetMove(move);

	m_fLife = LIFE_DEFAULT;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CShuriken::Uninit(void)
{
	CObjectX::Uninit();

	m_aShuriken.remove(this);
}

//=====================================================
// �X�V����
//=====================================================
void CShuriken::Update(void)
{
	CObjectX::Update();

	// �ړ��ʂ̔��f
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();

	pos += move;

	SetPosition(pos);

	// �����̌���
	m_fLife -= CManager::GetDeltaTime();

	if (m_fLife <= 0.0f)
	{
		m_fLife = 0.0f;

		Uninit();

		return;
	}

#ifdef _DEBUG
	// �f�o�b�O����
	Debug();
#endif
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
// �f�o�b�O����
//=====================================================
void CShuriken::Debug(void)
{
	// �f�o�b�O�v���b�N�擾
	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
		return;

	pDebugProc->Print("\n�藠���̈ړ�[%f,%f,%f]", GetMove().x, GetMove().y, GetMove().z);
	pDebugProc->Print("\n�藠���̈ʒu[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
}