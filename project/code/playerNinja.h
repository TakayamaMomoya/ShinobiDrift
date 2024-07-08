//*****************************************************
//
// �v���C���[�E��[playerNinja.cpp]
// Author:���R����
//
//*****************************************************
#ifndef _PLAYERNINJA_H_
#define _PLAYERNINJA_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "motion.h"

//*****************************************************
// �O���錾
//*****************************************************
class CBlockGrab;
class CObject3D;
class CPlayerNinja;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPlayerNinja : public CMotion
{
public:
	CPlayerNinja(int nPriority = 4);	// �R���X�g���N�^
	~CPlayerNinja();	// �f�X�g���N�^

	static CPlayerNinja *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Event(EVENT_INFO *pEventInfo);
	void ManagekatanaCollision(D3DXVECTOR3 pos);
};

#endif