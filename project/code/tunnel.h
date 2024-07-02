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

	// �ϐ��擾�E�ݒ�֐�
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator GetItStart(void) { return m_itStart; }
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator GetItEnd(void) { return m_itEnd; }

	// �ÓI�����o�֐�
	static CTunnel *Create(std::vector<CMeshRoad::SInfoRoadPoint>::iterator itStart, std::vector<CMeshRoad::SInfoRoadPoint>::iterator itEnd);

private:
	// �����o�֐�
	void CreateVtx(void);	// ���_�̐���
	void VtxFollowRoad(void);	// ���_�𓹂ɉ��킹��
	void DetectionPlayer(void);	// �v���C���[�̌��m
	void CollidePlayerEnter(VERTEX_3D *pVtx);	// �v���C���[�����Ă��锻��
	void CollidePlayerExit(VERTEX_3D *pVtx);	// �v���C���[�o�Ă�������

	// �����o�ϐ�
	bool m_bInPlayer;	// �v���C���[�������Ă��邩�ǂ���
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator m_itStart;	// �J�n�C�e���C�^�[
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator m_itEnd;	// �I���C�e���C�^�[
};
#endif