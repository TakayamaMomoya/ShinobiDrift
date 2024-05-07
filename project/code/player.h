//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:髙山桃也
//
//*****************************************************

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "motion.h"

//*****************************************************
// 前方宣言
//*****************************************************

//*****************************************************
// クラスの定義
//*****************************************************
class CPlayer : public CMotion
{
public:
	enum MOTION
	{
		MOTION_NEUTRAL = 0,	// 待機
		MOTION_WALK_FRONT,	// 前歩
		MOTION_MAX
	};
	enum STATE
	{
		STATE_NONE = 0,	// 何でもない状態
		STATE_NORMAL,	// 通常状態
		STATE_MAX
	};
	struct SParam
	{
		float fSpeedMove;		// 移動速度
	};

	CPlayer(int nPriority = 4);	// コンストラクタ
	~CPlayer();	// デストラクタ

	static CPlayer *Create(void);
	static CPlayer *GetInstance(void) { return m_pPlayer; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(float fDamage);
	SParam GetParam(void) { return m_param; }

private:
	struct SFragMotion
	{
		bool bMove;	// 移動
	};
	struct SInfo
	{
		STATE state;	// 状態
		float fSpeed;	// 現在の速度
		float fSpeedDest;	// 目標速度
	};

	void Load(void);
	void Input(void);
	void InputMove(void);
	void InputCamera(void);
	void ManageSpeed(void);
	void ManageState(void);
	void ManageMotion(void);
	void Event(EVENT_INFO *pEventInfo);
	void Debug(void);

	SInfo m_info;	// 自身の情報
	SParam m_param;	// パラメータ情報
	SFragMotion m_fragMotion;	// モーションのフラグ

	static CPlayer *m_pPlayer;	// 自身のポインタ
};

#endif