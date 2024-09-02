//*****************************************************
//
// ゲーム処理[game.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "scene.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CGame;
class CPlayer;
class CEdit;
class CTimer;

//*****************************************************
// クラスの定義
//*****************************************************
class CGame : public CScene
{
public:
	enum STATE
	{// 状態
		STATE_NONE,	// 何もしていない状態
		STATE_NORMAL,	// 通常状態
		STATE_RESULT,	// リザルト状態
		STATE_END,	// 終了状態
		STATE_MAX
	};

	CGame();	// コンストラクタ
	~CGame();	// デストラクタ

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

	// ゲームタイマー
	CTimer *GetGameTimer(void) { return m_pGameTimer; }	// ゲームタイマー
	void CreateGameTimer(void);	// 生成
	void ReleaseGameTimer(void);	// ゲームタイマーの解放

private:
	void UpdateCamera(void);
	void ManageState(void);
	void UpdateGameTimer(void);	// タイマーの更新
	void ToggleStop(void);
	void Debug(void);
	void ChangeEdit(CEdit *pEdit);

	static STATE m_state;	// 状態
	static CGame *m_pGame;	// 自身のポインタ

	int m_nCntState;	// 状態遷移カウンター
	bool m_bStop;	// 停止状態
	CEdit *m_pEdit;	// エディットのポインタ
	CTimer *m_pGameTimer;	// ゲームのタイマー
};

#endif