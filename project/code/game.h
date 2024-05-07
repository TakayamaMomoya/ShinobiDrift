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
	int GetAddReward(void) { return m_nAddReward; }
	void AddReward(int nValue) { m_nAddReward += nValue; }
	void SetAddReward(int nValue) { m_nAddReward = nValue; }
	void SetEventCamera(float fTime, D3DXVECTOR3 posRDest, D3DXVECTOR3 posVDest);

private:
	void UpdateCamera(void);
	void ManageState(void);
	void Debug(void);

	static STATE m_state;	// ���
	static CGame *m_pGame;	// ���g�̃|�C���^

	int m_nAddReward;	// ���Z��V
	int m_nCntState;	// ��ԑJ�ڃJ�E���^�[
	bool m_bStop;	// ��~���
};

#endif