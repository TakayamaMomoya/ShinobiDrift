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
#include "meshcylinder.h"
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
};
#endif