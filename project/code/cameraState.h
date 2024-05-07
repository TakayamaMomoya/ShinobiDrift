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
	virtual void Update(CCamera *pCamera) = 0;

private:
};

// �o���J����
class CApperPlayer : public CCameraState
{
public:
	void Update(CCamera *pCamera) override;

private:
};

// �v���C���[�Ǐ]
class CFollowPlayer : public CCameraState
{
public:
	void Update(CCamera *pCamera) override;

private:
};

// ����
class CMoveControl : public CCameraState
{
public:
	void Update(CCamera *pCamera) override;

private:

};


#endif