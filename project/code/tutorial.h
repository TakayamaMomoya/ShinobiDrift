//*****************************************************
//
// �`���[�g���A������[tutorial.h]
// Author:���R����
//
//*****************************************************
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;
class CStateTutorial;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CTutorial : public CObject
{// �`���[�g���A���̃N���X
public:
	CTutorial();	// �R���X�g���N�^
	~CTutorial();	// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void);	// ������
	virtual void Uninit(void);	// �I��
	virtual void Update();	// �X�V
	virtual void Draw();	// �`��
	std::map<int, CUI*> *GetMap(void) { return &m_mapUI; }	// �}�b�v�R���e�i�擾
	void ChangeState(CStateTutorial *pState);	// �X�e�C�g�̕ύX

	// �ÓI�����o�֐�
	static CTutorial *Create(void);	// ��������
private:
	// �����o�֐�
	void StartGame(void);	// �Q�[���J�n�̏���

	// �����o�ϐ�
	std::map<int,CUI*> m_mapUI;	// UI�̃}�b�v�R���e�i
	CStateTutorial *m_pState;	// �X�e�C�g�̃|�C���^
};

class CStateTutorial
{// �X�e�C�g�̊��N���X
public:
	CStateTutorial() {};	// �R���X�g���N�^
	virtual ~CStateTutorial() {};	 // �f�X�g���N�^

	// �����o�֐�
	virtual void Init(CTutorial *pTutorial) = 0;	// ����������
	virtual void Uninit(CTutorial *pTutorial);	// �I������
	virtual void Update(CTutorial *pTutorial) = 0;	// �X�V����
private:
};

class CStateTutorialMove : public CStateTutorial
{// �ړ��̃`���[�g���A��
public:
	CStateTutorialMove();	// �R���X�g���N�^
	virtual ~CStateTutorialMove();	 // �f�X�g���N�^

	// �����o�֐�
	void Init(CTutorial *pTutorial) override;	// ����������
	void Uninit(CTutorial *pTutorial) override;	// �I������
	void Update(CTutorial *pTutorial) override;	// �X�V����

private:
};

#endif