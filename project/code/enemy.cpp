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
#include "myLib.h"
#include "debugproc.h"
#include "effect3D.h"
#include "meshRoad.h"
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
	m_nIdx = 1;
	m_Info.fRate = 0.0f;
	m_fSpeedDefault = 0.0f;
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

	// �X�v���C���̏����擾
	m_pSpline = CMeshRoad::GetInstance()->GetCenterSpline();

	// ���[�h�|�C���g�̏����擾
	std::vector<CMeshRoad::SInfoRoadPoint> pRoadPoint = *CMeshRoad::GetInstance()->GetArrayRP();

	// �x�N�^�[��K�v�ȃT�C�Y�ɒ���
	int nSize = pRoadPoint.size();
	m_vPos.resize(nSize);

	for (int i = 0; i < nSize; i++)
	{
		m_vPos[i] = pRoadPoint[i].pos;
	}

	// ���S�X�v���C���̏�����
	if(m_pSpline != nullptr)
	   m_pSpline->Init(m_vPos);

	// �����X�s�[�h�̌v�Z
	m_fSpeedDefault = SPEED_DEFAULT;
	CalcSpeed();

	SetPosition(D3DXVECTOR3(pRoadPoint[0].pos.x, pRoadPoint[0].pos.y, pRoadPoint[0].pos.z));

	return S_OK;
}

//=====================================================
// �X�s�[�h�̌v�Z
//=====================================================
void CEnemy::CalcSpeed(void)
{
	if (m_pSpline == nullptr)
		return;

	if (m_pSpline->IsEmpty())
		return;

	float fLength = m_pSpline->GetLength(m_nIdx, 50);

	if (fLength == 0)
		return;	// 0����h�~

	m_fSpeed = m_fSpeedDefault / fLength;
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

	// �ʒu�̕��
	InterpolatePosition();
}

//=====================================================
// �ʒu�̕��
//=====================================================
void CEnemy::InterpolatePosition(void)
{
	D3DXVECTOR3 pos = GetPosition();

	if (m_Info.fRate >= 1.0f)
	{
		m_nIdx++;

		// �T�C�Y�𒴂�����߂�
		if (m_nIdx >= (int)m_vPos.size())
			m_nIdx = 1;

		// �X�s�[�h�̌v�Z
		CalcSpeed();

		m_Info.fRate -= 1.0f;
	}

	m_Info.fRate += m_fSpeed;

	CPlayer *pPlayer = CPlayer::GetInstance();

	m_fSpeedDefault = pPlayer->GetSpeed() * 0.85f;

	// �X�s�[�h�̌v�Z
	CalcSpeed();

	// �ʒu���
	if (m_pSpline != nullptr)
	{
		if (m_pSpline->IsEmpty())
		{// �X�v���C�����󂾂������̍Ď擾
			CMeshRoad *pMesh = CMeshRoad::GetInstance();

			if (pMesh == nullptr)
				return;

			m_pSpline = pMesh->GetCenterSpline();

			if (m_pSpline->IsEmpty())
				return;	// �Ď擾���Ă��󂾂����珈����ʂ��Ȃ�
		}

		pos = m_pSpline->Interpolate(m_Info.fRate, m_nIdx);
	}

	// �ʒu�ƌ����X�V
	SetPosition(pos);

	// �����̐���
	ControllRot();

	// �f�o�b�O�\��
	Debug();
}

//=====================================================
// �����̐���
//=====================================================
void CEnemy::ControllRot(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// ���̃f�[�^�_�̕�������
	universal::FactingRotTarget(&rot, pos, m_vPos[m_nIdx], 0.05f);

	SetRotation(D3DXVECTOR3(0.0f, rot.y, 0.0f));
}

//=====================================================
// �f�o�b�O�\��
//=====================================================
void CEnemy::Debug(void)
{
	// �f�o�b�O�v���b�N�擾
	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
		return;

	CEffect3D::Create(GetPosition(), 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	pDebugProc->Print("\n�G�̃o�C�N�̈ʒu[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	pDebugProc->Print("\n�G�̑��x[%f]", m_fSpeedDefault);
}

//=====================================================
// �S�r�w�C�r�A���
//=====================================================
void CEnemy::ReleaseAllBehaviour(void)
{
	for (auto it : m_listBehaviour)
	{
		it->Uninit(this);
		m_listBehaviour.remove(it);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemy::Draw(void)
{
	// �p���N���X�̕`��
	CMotion::Draw();
}