//*****************************************************
//
// ���S�\������[logo.h]
// Author:���R����
//
//*****************************************************
#ifndef _LOGO_H_
#define _LOGO_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "scene.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CLogo : public CScene
{
public:
	CLogo();	// �R���X�g���N�^
	~CLogo();	// �f�X�g���N�^

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:
	// �����o�ϐ�
	CUI *m_pLogo;	// ���S
	float m_fTimerLogoDisp;	// ���S�̕\���J�E���^�[
};

#endif