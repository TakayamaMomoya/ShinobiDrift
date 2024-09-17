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
class CLight;

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

	// �ϐ��擾�E�ݒ�֐�
	vector<CLight*> GetLight(void) { return m_aLight; };	// ���C�g�̔z��
	void SetDestColLight(D3DXCOLOR col) { m_colLight = col; }	// ���C�g�̐F
	void ResetDestColLight(void);	// ���C�g�F���Z�b�gs

	// �Q�[���^�C�}�[
	CTimer *GetGameTimer(void) { return m_pGameTimer; }	// �Q�[���^�C�}�[
	void CreateGameTimer(void);	// ����
	void ReleaseGameTimer(void);	// �Q�[���^�C�}�[�̉��

private:
	// �����o�֐�
	void UpdateCamera(void);
	void ManageState(void);
	void UpdateGameTimer(void);	// �^�C�}�[�̍X�V
	void ToggleStop(void);
	void Debug(void);
	void ChangeEdit(CEdit *pEdit);
	void CreateLight(void);	// ���C�g�̐���
	void UpdateLight(void);	// ���C�g�̍X�V

	// �����o�ϐ�
	int m_nCntState;	// ��ԑJ�ڃJ�E���^�[
	bool m_bStop;	// ��~���
	CEdit *m_pEdit;	// �G�f�B�b�g�̃|�C���^
	CTimer *m_pGameTimer;	// �Q�[���̃^�C�}�[
	vector<CLight*> m_aLight;	// �Q�[�����̃��C�g
	D3DXCOLOR m_colLight;	// ���C�g�F

	// �ÓI�����o�ϐ�
	static STATE m_state;	// ���
	static CGame *m_pGame;	// ���g�̃|�C���^
};

#endif