//*****************************************************
//
// �g���l���̏���[tunnel.h]
// Author:���R����
//
//*****************************************************
#ifndef _TUNNEL_H_	// ��d�C���N���[�h�h�~
#define _TUNNEL_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "meshCylinder.h"
#include "meshRoad.h"

//*****************************************************
// �N���X��`
//*****************************************************
class CTunnel : public CMeshCylinder
{
public:
	CTunnel(int nPriority = 5);	// �R���X�g���N�^
	~CTunnel();	// �f�X�g���N�^

	// �����o�ϐ�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CTunnel *Create(std::vector<CMeshRoad::SInfoRoadPoint>::iterator itStart, std::vector<CMeshRoad::SInfoRoadPoint>::iterator itEnd);

private:
	// �����o�֐�
	void CreateVtx(void);	// ���_�̐���
	void VtxFollowRoad(void);	// ���_�𓹂ɉ��킹��

	// �����o�ϐ�
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator m_itStart;	// �J�n�C�e���C�^�[
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator m_itEnd;	// �I���C�e���C�^�[
};
#endif