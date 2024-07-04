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
#include "player.h"
#include "effect3D.h"
#include "meshRoad.h"
#include "universal.h"

//*****************************************************
// �ÓI�����o�ϐ�
//*****************************************************
CEnemy* CEnemy::m_pEnemy = nullptr;

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const float SPEED = 0.004f;
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemy::CEnemy(int nPriority)
{
	m_pEnemyNinja = nullptr;
	m_nIdx = 1;
	m_nSize = 0;
	m_Info.fSpeed = 0.0f;
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
	CMotion::Load("data\\MOTION\\motionEnemy.txt");

	// �X�v���C���̏����擾
	m_pSpline = CMeshRoad::GetInstance()->GetCenterSpline();

	// ���[�h�|�C���g�̏����擾
	std::vector<CMeshRoad::SInfoRoadPoint> pRoadPoint = *CMeshRoad::GetInstance()->GetArrayRP();

	// �x�N�^�[��K�v�ȃT�C�Y�ɒ���
	m_nSize = pRoadPoint.size();
	m_vPos.resize(m_nSize);

	for (int i = 0; i < m_nSize; i++)
	{
		m_vPos[i] = pRoadPoint[i].pos;
	}

	// ���S�X�v���C���̏�����
	if(m_pSpline != nullptr)
	   m_pSpline->Init(m_vPos);

	SetPosition(D3DXVECTOR3(pRoadPoint[0].pos.x, pRoadPoint[0].pos.y, pRoadPoint[0].pos.z));

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemy::Uninit(void)
{
	m_pEnemy = nullptr;

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

	D3DXVECTOR3 pos = { 0.0f, 0.0f, 0.0f };

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// �ʒu���
	if(m_pSpline != nullptr)
	   pos = m_pSpline->Interpolate(m_Info.fSpeed, m_nIdx);

	m_Info.fSpeed += SPEED;

	if (m_Info.fSpeed >= 1.0f)
	{
		m_Info.fSpeed = 0.0f;

		m_nIdx++;
	}

	// �T�C�Y�𒴂�����߂�
	if (m_nIdx >= m_nSize)
		m_nIdx = 1;
		
	// ���̃|�C���g�Ɍ�������
	universal::FactingRotTarget(&rot, pos, m_vPos[m_nIdx], 0.05f);

	// �ʒu�ƌ����X�V
	SetPosition(pos);
	SetRotation(D3DXVECTOR3(0.0f, rot.y, 0.0f));

	CEffect3D::Create(pos, 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �f�o�b�O�v���b�N�擾
	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
		return;
	
	pDebugProc->Print("\n�G�̃o�C�N�̈ʒu[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	//pDebugProc->Print("\n�G�̈ʒu[%f,%f,%f]", m_pEnemyNinja->GetPosition().x, m_pEnemyNinja->GetPosition().y, m_pEnemyNinja->GetPosition().z);
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
