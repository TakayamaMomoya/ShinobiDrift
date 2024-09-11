//*****************************************************
//
// �J�����X�e�C�g[cameraState.h]
// Author:���R����
//
//*****************************************************

#ifndef _CAMERASTATE_H_
#define _CAMERASTATE_H_

//****************************************************
// �O���錾
//****************************************************
class CCamera;

//****************************************************
// �N���X�̒�`
//****************************************************
// ���N���X
class CCameraState
{
public:
	CCameraState() {};
	virtual void Init(CCamera *pCamera) = 0;
	virtual void Update(CCamera *pCamera) = 0;

private:
};

// �v���C���[�o���J����
class CCameraStateApperPlayer : public CCameraState
{
public:
	CCameraStateApperPlayer();
	void Init(CCamera *pCamera);
	void Update(CCamera *pCamera) override;

private:
};

// �v���C���[�Ǐ]
class CFollowPlayer : public CCameraState
{
public:
	CFollowPlayer();
	void Init(CCamera *pCamera) {};
	void Update(CCamera *pCamera) override;

private:
	float m_fTimerPosR;
	float m_fLengthPosR;
	D3DXVECTOR3 m_rotROld;
	bool m_bDebug;
};

// �`���[�g���A���̏I�����̃J����
class CCameraStateTutorialEnd : public CCameraState
{
public:
	CCameraStateTutorialEnd();
	void Init(CCamera *pCamera);
	void Update(CCamera* pCamera) override;

private:

};

// ����
class CMoveControl : public CCameraState
{
public:
	CMoveControl() {};
	void Init(CCamera *pCamera) {};
	void Update(CCamera *pCamera) override;

private:
	bool m_bAbove = false;	// ��󎋓_���ǂ���
};

// �^�C�g��
class CCameraStateTitle : public CCameraState
{
public:
	CCameraStateTitle() {};
	void Init(CCamera *pCamera) {};
	void Update(CCamera* pCamera) override;

private:

};

// �^�C�g���Ńv���C���[��Ǐ]
class CCameraStateFollowPlayerTitle : public CCameraState
{
public:
	CCameraStateFollowPlayerTitle() {};
	void Init(CCamera *pCamera) {};
	void Update(CCamera* pCamera) override;

private:

};

// ���U���g
class CCameraStateResult : public CCameraState
{
public:
	CCameraStateResult();
	void Init(CCamera *pCamera) {};
	void Update(CCamera* pCamera) override;

private:

};

#endif