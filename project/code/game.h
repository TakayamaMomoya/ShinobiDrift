//*****************************************************
//
// Q[[game.h]
// Author:ûüRç
//
//*****************************************************
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************
// CN[h
//*****************************************************
#include "main.h"
#include "scene.h"

//*****************************************************
// Oûé¾
//*****************************************************
class CGame;
class CPlayer;
class CEdit;
class CTimer;
class CLight;

//*****************************************************
// NXÌè`
//*****************************************************
class CGame : public CScene
{
public:
	enum STATE
	{// óÔ
		STATE_NONE,	// ½àµÄ¢È¢óÔ
		STATE_NORMAL,	// ÊíóÔ
		STATE_RESULT,	// UgóÔ
		STATE_END,	// I¹óÔ
		STATE_MAX
	};

	CGame();	// RXgN^
	~CGame();	// fXgN^

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

	// Ïæ¾EÝèÖ
	vector<CLight*> GetLight(void) { return m_aLight; };	// CgÌzñ
	void SetDestColLight(D3DXCOLOR col) { m_colLight = col; }	// CgÌF
	void ResetDestColLight(void);	// CgFZbgs

	// Q[^C}[
	CTimer *GetGameTimer(void) { return m_pGameTimer; }	// Q[^C}[
	void CreateGameTimer(void);	// ¶¬
	void ReleaseGameTimer(void);	// Q[^C}[Ìðú

private:
	// oÖ
	void UpdateCamera(void);
	void ManageState(void);
	void UpdateGameTimer(void);	// ^C}[ÌXV
	void ToggleStop(void);
	void Debug(void);
	void ChangeEdit(CEdit *pEdit);
	void CreateLight(void);	// CgÌ¶¬
	void UpdateLight(void);	// CgÌXV

	// oÏ
	int m_nCntState;	// óÔJÚJE^[
	bool m_bStop;	// â~óÔ
	CEdit *m_pEdit;	// GfBbgÌ|C^
	CTimer *m_pGameTimer;	// Q[Ì^C}[
	vector<CLight*> m_aLight;	// Q[ÌCg
	D3DXCOLOR m_colLight;	// CgF

	// ÃIoÏ
	static STATE m_state;	// óÔ
	static CGame *m_pGame;	// ©gÌ|C^
};

#endif