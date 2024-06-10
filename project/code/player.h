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
class CBlockGrab;
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
		STATE_MAX
	};
	struct SParam
	{
		char aPathBody[MAX_STRING];	// �����ڂ̃p�X
		float fSpeedMax;	// �ő呬�x
		float fFactAccele;	// �����W��
		float fFactAttenu;	// �����W��
		float fFactBrake;	// �u���[�L�����W��
		float fAngleMaxCurve;	// �J�[�u�̍ő�p�x
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
	SParam GetParam(void) { return m_param; }
	CBlockGrab *GetBlock(void) { return m_info.pBlockGrab; }
	float GetSpeed() { return m_info.fSpeed; }

private:
	struct SFragMotion
	{
		bool bMove;	// �ړ�
	};
	struct SInfo
	{
		STATE state;	// ���
		float fSpeed;	// ���݂̑��x
		float fSpeedDest;	// �ڕW���x
		float fAngleHandle;	// �n���h���������Ă���l
		float fTimerFlip;	// �h���t�g�J�E���^�[
		float fAngleDrift;	// �h���t�g���̊p�x�{���̒l
		int nCntFlip;	// �e���J�E���^�[
		CBlockGrab *pBlockGrab;	// �͂�ł���u���b�N
		CObject3D *pRoap;
		float fCntAngle;	// �A���O���̃J�E���^�[
		bool bGrabOld;
		bool bManual;		// �}�j���A������
		float fLengthDrift;
		float fTimerDriftChange;
		float fSizeBlurDrift;	// �h���t�g���̃u���[�̋���
		float fDesityBlurDrift;	// �h���t�g���̃u���[�̔Z��
	};

	void Load(void);
	void Input(void);
	void InputMove(void);
	void InputCamera(void);
	void InputWire(void);
	void ForwardFollowWire(float vecLength, D3DXVECTOR3 vecDiff);	// ���C���[�ɉ����Đi�߂�
	void JudgeChangeDrift(float fAngle, float fAngleDiff, float fLength);	// �h���t�g�ω��̔���
	void ControlRoap(void);	// ���[�v�̐���
	void SarchGrab(void);	// �͂ރu���b�N�̒T�m
	void ManageRotateGrab(float fAngleDiff);	// �͂�ł���Ƃ��̉�]����
	void JudgeRemoveWire(float fLength);	// ���C���[���O�����̔���
	void RemoveWire(void);	// ���C���[���O������
	void LimitDrift(float fLength);
	void ManageSpeed(void);
	void ManageState(void);
	void ManageMotion(void);
	void Event(EVENT_INFO *pEventInfo);
	void Debug(void);

	SInfo m_info;	// ���g�̏��
	SParam m_param;	// �p�����[�^���
	SFragMotion m_fragMotion;	// ���[�V�����̃t���O

	static CPlayer *m_pPlayer;	// ���g�̃|�C���^
};

#endif