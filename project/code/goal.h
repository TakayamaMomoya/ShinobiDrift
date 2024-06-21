//*****************************************************
//
// �S�[������[goal.h]
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

	float GetRotation() { return m_fRot; }	// �����擾����

private:
	//�����o�ϐ�
	int m_nTransitionTime;		// �J�ڎ���

	D3DXVECTOR3 m_pos;		// �ʒu
	float m_fPosX;		// X���W
	float m_fPosZ;		// Z���W
	float m_fRot;		// ����

	CPlayer* m_pPlayer;		// �v���C���[�̃|�C���^
	CObject3D* m_pObj3D;	// �I�u�W�F�N�g3D�̃|�C���^
};

#endif
