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
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator GetItStart(void) { return m_itStart; }
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator GetItEnd(void) { return m_itEnd; }

	// �ÓI�����o�֐�
	static CGuardRail *Create(std::vector<CMeshRoad::SInfoRoadPoint>::iterator itStart, std::vector<CMeshRoad::SInfoRoadPoint>::iterator itEnd);

private:
	// �����o�֐�
	void CreateVtx(void);	// ���_�̐���
	void VtxFollowRoad(void);	// ���_�𓹂ɉ��킹��

	// �����o�ϐ�
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator m_itStart;	// �J�n�C�e���C�^�[
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator m_itEnd;	// �I���C�e���C�^�[
};
#endif