//*****************************************************
//
// UI�}�l�[�W���[[UIManager.h]
// Author:���R����
//
//*****************************************************

#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;
class CMeter;
class CRankTime;

//*****************************************************
// �萔��`
//*****************************************************

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CUIManager : public CObject
{
public:

	CUIManager();	// �R���X�g���N�^
	~CUIManager();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ReleaseMeter(void);	// ���[�^�[���
	void CreateRankTImer(void);	// �����N�^�C�}�[����
	void ReleaseRankTimer(void);	// �����N�^�C�}�[���
	void ReleaseGameUI(void);	// �Q�[��UI�̈ꊇ���

	// �ϐ��擾�E�ݒ�֐�
	bool IsDisp(void) { return m_bDisp; }
	void EnableDisp(bool bDisp) { m_bDisp = bDisp; }

	// �ÓI�����o�֐�
	static CUIManager *Create(void);
	static CUIManager *GetInstance(void) { return m_pUIManager; }

private:
	// �����o�ϐ�
	float m_fCntFrame;	// �t���[���̃J�E���^�[
	bool m_bDisp;	// �\�����邩�ǂ���
	CMeter *m_pMeter;	// ���[�^�[
	CRankTime *m_pRankTime;	// �����N�^�C��

	// �ÓI�����o�ϐ�
	static CUIManager *m_pUIManager;	// ���g�̃|�C���^
};

#endif
