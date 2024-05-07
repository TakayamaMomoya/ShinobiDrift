//*****************************************************
//
// �v���C���[�̏���[player.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "motion.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionSphere;
class CCollisionCube;
class CObject3D;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPlayer : public CMotion
{
public:
	enum MOTION
	{
		MOTION_NEUTRAL = 0,	// �ҋ@
		MOTION_WALK_FRONT,	// �O��
		MOTION_MAX
	};
	enum STATE
	{
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_BLOW,	// ������΂���Ă�����
		STATE_DAMAGE,	// �_���[�W���
		STATE_DEATH,	// ���S���
		STATE_MAX
	};
	enum PARAM
	{
		PARAM_GUN = 0,	// �e�̔M
		PARAM_MELEE,	// �ߐڕ���̔M
		PARAM_HAND,	// �r�̔M
		PARAM_MAX
	};
	struct SParam
	{
		float fSpeedMove;		// �ړ����x
		float fInitialBoost;		// �u�[�X�g�c�ʏ����l
		float fInitialLife;	// �����̗�
	};

	CPlayer(int nPriority = 4);	// �R���X�g���N�^
	~CPlayer();	// �f�X�g���N�^

	static CPlayer *Create(void);
	static CPlayer *GetInstance(void) { return m_pPlayer; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(float fDamage);
	float GetLife(void) { return m_info.fLife; }
	SParam GetParam(void) { return m_param; }

private:
	struct SFragMotion
	{
		bool bMove;	// �ړ�
		bool bJump;	// �W�����v
		bool bDodge;	// ���
		bool bStamp;	// ���݂�
		bool bShot;	// �ˌ�
		bool bMelee;	// �ߐڍU��
		bool bAddAttack;	// �ǉ��U��
		bool bGrab;	// �͂�
		bool bAir;	// �؋�
		bool bStop;	// �}��~
	};
	struct SInfo
	{
		float fLife;	// �̗�
		STATE state;	// ���
		CCollisionSphere *pCollisionSphere;	// ���̓����蔻��
		CCollisionSphere *pClsnAttack;	// �U���̓����蔻��
		CCollisionCube *pCollisionCube;	// �����̂̓����蔻��
		bool bLand;	// ���n���Ă��邩�ǂ���
		D3DXVECTOR3 rotDest;	// �ڕW�̌���
	};

	void Load(void);
	void Input(void);
	void InputMove(void);
	void InputCamera(void);
	void InputAttack(void);
	void Rotation(void);
	void ManageCollision(void);
	void ManageState(void);
	void ManageMotion(void);
	void AddMoveForward(float fSpeed);
	void AddMoveUp(float fSpeed);
	void Event(EVENT_INFO *pEventInfo);
	void Death(void);
	void Debug(void);

	SInfo m_info;	// ���g�̏��
	SParam m_param;	// �p�����[�^���
	SFragMotion m_fragMotion;	// ���[�V�����̃t���O

	static CPlayer *m_pPlayer;	// ���g�̃|�C���^
};

#endif