//*****************************************************
//
// �G�l�~�[�r�w�C�r�A[enemyBehaviour.cpp]
// Author:�匴�叫
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "enemyBehaviour.h"
#include "enemy.h"
#include "effect3D.h"
#include "debugproc.h"
#include "player.h"
#include "myLib.h"
#include "meshRoad.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float SPEED_DEFAULT_CAHSE = 50.0f;	// �ǐՂ̕W�����x
}

//********************************************************************************
// �v���C���[�̒ǐ�
//********************************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyBehaviourChasePlayer::CEnemyBehaviourChasePlayer()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyBehaviourChasePlayer::~CEnemyBehaviourChasePlayer()
{

}

//=====================================================
// ������
//=====================================================
void CEnemyBehaviourChasePlayer::Init(CEnemy *pEnemy)
{
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
	if (m_pSpline != nullptr)
		m_pSpline->Init(m_vPos);

	// �����X�s�[�h�̌v�Z
	m_fSpeedDefault = SPEED_DEFAULT_CAHSE;
	CalcSpeed(pEnemy);

	pEnemy->SetPosition(D3DXVECTOR3(pRoadPoint[0].pos.x, pRoadPoint[0].pos.y, pRoadPoint[0].pos.z));
}

//=====================================================
// �I��
//=====================================================
void CEnemyBehaviourChasePlayer::Uninit(CEnemy *pEnemy)
{

}

//=====================================================
// �X�V
//=====================================================
void CEnemyBehaviourChasePlayer::Update(CEnemy *pEnemy)
{
	// �ʒu�̕��
	InterpolatePosition(pEnemy);
}

//=====================================================
// �ʒu�̕��
//=====================================================
void CEnemyBehaviourChasePlayer::InterpolatePosition(CEnemy *pEnemy)
{
	D3DXVECTOR3 pos = pEnemy->GetPosition();

	if (m_fRate >= 1.0f)
	{
		m_nIdx++;

		// �T�C�Y�𒴂�����߂�
		if (m_nIdx >= (int)m_vPos.size())
			m_nIdx = 1;

		// �X�s�[�h�̌v�Z
		CalcSpeed(pEnemy);

		m_fRate -= 1.0f;
	}

	m_fRate += m_fSpeed;

	CPlayer *pPlayer = CPlayer::GetInstance();

	m_fSpeedDefault = pPlayer->GetSpeed() * 0.85f;

	// �X�s�[�h�̌v�Z
	CalcSpeed(pEnemy);

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

		pos = m_pSpline->Interpolate(m_fRate, m_nIdx);
	}

	// �ʒu�ƌ����X�V
	pEnemy->SetPosition(pos);

	// �����̐���
	ControllRot(pEnemy);

	// �f�o�b�O�\��
	Debug(pEnemy);
}

//=====================================================
// �X�s�[�h�̌v�Z
//=====================================================
void CEnemyBehaviourChasePlayer::CalcSpeed(CEnemy *pEnemy)
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
// �����̐���
//=====================================================
void CEnemyBehaviourChasePlayer::ControllRot(CEnemy *pEnemy)
{
	D3DXVECTOR3 pos = pEnemy->GetPosition();
	D3DXVECTOR3 rot = pEnemy->GetRotation();

	// ���̃f�[�^�_�̕�������
	universal::FactingRotTarget(&rot, pos, m_vPos[m_nIdx], 0.05f);

	pEnemy->SetRotation(D3DXVECTOR3(0.0f, rot.y, 0.0f));
}

//=====================================================
// �f�o�b�O�\��
//=====================================================
void CEnemyBehaviourChasePlayer::Debug(CEnemy *pEnemy)
{
	// �f�o�b�O�v���b�N�擾
	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
		return;

	CEffect3D::Create(pEnemy->GetPosition(), 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	pDebugProc->Print("\n�G�̃o�C�N�̈ʒu[%f,%f,%f]", pEnemy->GetPosition().x, pEnemy->GetPosition().y, pEnemy->GetPosition().z);
	pDebugProc->Print("\n�G�̑��x[%f]", m_fSpeedDefault);
}
