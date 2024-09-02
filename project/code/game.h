//*****************************************************
//
// �Q�[������[game.h]
// Author:���R����
//
//*****************************************************
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "scene.h"

//*****************************************************
// �O���錾
//*****************************************************
class CGame;
class CPlayer;
class CEdit;
class CTimer;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CGame : public CScene
{
public:
	enum STATE
	{// ���
		STATE_NONE,	// �������Ă��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_RESULT,	// ���U���g���
		STATE_END,	// �I�����
		STATE_MAX
	};

	CGame();	// �R���X�g���N�^
	~CGame();	// �f�X�g���N�^

	static CGame *GetInstance(void) { return m_pGame; }
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update();
	virtual void Draw();
	static void SetState(STATE state) { m_state = state; }
	static STATE GetState(void) { return m_state; }
	void EnableStop(bool bStop) { m_bStop = bStop; }
	bool GetStop(void) { return m_bStop; }
	CEdit *GetEdit(void) { return m_pEdit; }

	// �Q�[���^�C�}�[
	CTimer *GetGameTimer(void) { return m_pGameTimer; }	// �Q�[���^�C�}�[
	void CreateGameTimer(void);	// ����
	void ReleaseGameTimer(void);	// �Q�[���^�C�}�[�̉��

private:
	void UpdateCamera(void);
	void ManageState(void);
	void UpdateGameTimer(void);	// �^�C�}�[�̍X�V
	void ToggleStop(void);
	void Debug(void);
	void ChangeEdit(CEdit *pEdit);

	static STATE m_state;	// ���
	static CGame *m_pGame;	// ���g�̃|�C���^

	int m_nCntState;	// ��ԑJ�ڃJ�E���^�[
	bool m_bStop;	// ��~���
	CEdit *m_pEdit;	// �G�f�B�b�g�̃|�C���^
	CTimer *m_pGameTimer;	// �Q�[���̃^�C�}�[
};

#endif