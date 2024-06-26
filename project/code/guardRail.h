//*****************************************************
//
// �K�[�h���[���̏���[guardRail.h]
// Author:���R����
//
//*****************************************************
#ifndef _GUARDRAIL_H_	// ��d�C���N���[�h�h�~
#define _GUARDRAIL_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object3D.h"
#include "meshRoad.h"

//*****************************************************
// �N���X��`
//*****************************************************
class CGuardRail : public CObject3D
{
public:
	CGuardRail(int nPriority = 5);	// �R���X�g���N�^
	~CGuardRail();	// �f�X�g���N�^

	// �����o�ϐ�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ϐ��擾�E�ݒ�֐�
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator GetItStart(void) { return m_itStart; }	// �J�n�C�e���[�^�[
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator GetItEnd(void) { return m_itEnd; }	// �I���C�e���[�^�[
	bool IsLeft(void) { return m_bLeft; }	// ���ɂ��邩�ǂ���
	void EnableLeft(bool bLeft) { m_bLeft = bLeft; }

	bool CollideGuardRail(D3DXVECTOR3* pos, D3DXVECTOR3 vecAxial);

	// �ÓI�����o�֐�
	static CGuardRail *Create(std::vector<CMeshRoad::SInfoRoadPoint>::iterator itStart, std::vector<CMeshRoad::SInfoRoadPoint>::iterator itEnd,bool bLeft = false,float fHeight = 600.0f);

private:
	// �����o�֐�
	void CreateVtx(void);	// ���_�̐���
	void VtxFollowRoad(void);	// ���_�𓹂ɉ��킹��
	void SetNormal(VERTEX_3D *pVtx);	// �@���̐ݒ�

	// �����o�ϐ�
	int m_nNumVtx;	// ���_��
	float m_fHeight;	// ����
	bool m_bLeft;	// �����ɂ��邩�ǂ���
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator m_itStart;	// �J�n�C�e���C�^�[
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator m_itEnd;	// �I���C�e���C�^�[
};
#endif