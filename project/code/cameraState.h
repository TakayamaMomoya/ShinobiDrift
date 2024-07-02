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
	virtual void Update(CCamera *pCamera) = 0;

private:
};

// �v���C���[�Ǐ]
class CFollowPlayer : public CCameraState
{
public:
	CFollowPlayer();
	void Update(CCamera *pCamera) override;

private:
	float m_fTimerPosR;
	float m_fLengthPosR;
	D3DXVECTOR3 m_rotROld;
	bool m_bDebug;
};

// ����
class CMoveControl : public CCameraState
{
public:
	CMoveControl() {};
	void Update(CCamera *pCamera) override;

private:
	bool m_bAbove;	// ��󎋓_���ǂ���
};


#endif