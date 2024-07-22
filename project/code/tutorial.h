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
	void ChangeState(CStateTutorial *pState);	// �X�e�C�g�̕ύX

	// �ϐ��擾�E�ݒ�֐�
	void EnableEnd(bool bEnd) { m_bEnd = bEnd; }	// �I���t���O
	bool IsEnd(void) { return m_bEnd; }
	std::map<int, CUI*> *GetMap(void) { return &m_mapUI; }	// UI�̃}�b�v�R���e�i�擾
	std::map<int, float> GetMapCounter(void) { return m_mapCounter; }	// �J�E���^�[�̃}�b�v�R���e�i�擾
	void SetMapCounter(std::map<int, float> map) { m_mapCounter = map; }	// �J�E���^�[�̃}�b�v�R���e�i�擾

	// �ÓI�����o�֐�
	static CTutorial *Create(void);	// ��������
private:
	// �����o�֐�
	void StartGame(void);	// �Q�[���J�n�̏���

	// �����o�ϐ�
	std::map<int, CUI*> m_mapUI;	// UI�̃}�b�v�R���e�i
	std::map<int, float> m_mapCounter;	// �J�E���^�[�̃}�b�v�R���e�i
	CStateTutorial *m_pState;	// �X�e�C�g�̃|�C���^
	bool m_bEnd;	// �I���t���O
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
	virtual bool IsEndInput(void) { return false; }	// �I�����Ă��邩�ǂ���
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
	bool IsEndInput(CTutorial *pTutorial);	// �I������

private:
	enum E_MENU
	{// ���j���[����
		MENU_ACCELE = 0,	// �A�N�Z��
		MENU_BRAKE,	// �u���[�L
		MENU_MAX
	};
};

namespace Tutorial
{
CUI *CreateUIDefault(void);
}

#endif