//*****************************************************
//
// ��s���𑖂�Ԃ̏���[car.cpp]
// Author:�匴�叫
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "enemy.h"
#include "myLib.h"
#include "debugproc.h"
#include "player.h"
#include "effect3D.h"

//*****************************************************
// �ÓI�����o�ϐ�
//*****************************************************
CEnemy* CEnemy::m_pEnemy = nullptr;

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
// ����������
//=====================================================
HRESULT CEnemy::Init(void)
{
	// �p���N���X�̏�����
	CMotion::Init();

	// ���f���̐ݒ�
	CMotion::Load("data\\MOTION\\motionPlayer.txt");

	// �f�[�^�_�̃x�N�^�[�p��
	std::vector<D3DXVECTOR3> vPos;
	D3DXVECTOR3 Pos[3] = {};

	CPlayer* pPlayer = CPlayer::GetInstance();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();
	
	Pos[0] = { 0.0f, PlayerPos.y, 0.0f };
	Pos[1] = { 1000.0f, PlayerPos.y, 1000.0f };
	Pos[2] = { 2000.0f, PlayerPos.y, 1500.0f };

	//m_aRoadPoint.clear();

	//m_aRoadPoint.begin();

	// �x�N�^�[��K�v�ȃT�C�Y�ɒ���
	int nSize = 3;
	vPos.resize(nSize);

	for (int i = 0; i < nSize; i++)
	{
		vPos[i] = Pos[i];
	}

	m_pSpline = new CCutMullSpline;

	// ���S�X�v���C���̏�����
	m_pSpline->Init(vPos);

	SetPosition(pPlayer->GetPosition());

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemy::Uninit(void)
{
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

	D3DXVECTOR3 pos = {};
	pos = m_pSpline->Interpolate(m_t, m_nIdx);

	m_t += 0.01f;

	if (m_t >= 1.0f)
	{
		m_t = 0.0f;

		m_nIdx++;
	}

	if (m_nIdx >= 3)
		m_nIdx = 1;

	CEffect3D::Create(pos, 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\n�Ԃ̈ʒu[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemy::Draw(void)
{
	// �p���N���X�̕`��
	CMotion::Draw();
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
			m_pEnemy = pEnemy;

			// ������
			pEnemy->Init();
		}
	}

	return pEnemy;
}
