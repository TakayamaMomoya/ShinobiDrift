//*****************************************************
//
// �S�[��[goal.h]
// Author:�X��x��
//
//*****************************************************

#ifndef _GOAL_H_
#define _GOAL_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "player.h"
#include "object3D.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CGoal : public CObject
{
public:
	CGoal(int nPriority = 7);	// �R���X�g���N�^
	~CGoal();	//	�f�X�g���N�^

	// �����o�֐�
	static CGoal* Create();	// ����

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

private:
	//�����o�ϐ�
	CPlayer* m_pPlayer;	// �v���C���[�̃|�C���^
};

#endif