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
class CBlockGrab;
class CObject3D;

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
		char aPathBody[MAX_STRING];	// 見た目のパス
		float fSpeedMax;	// 最大速度
		float fFactAccele;	// 加速係数
		float fFactAttenu;	// 減速係数
		float fFactBrake;	// ブレーキ減速係数
		float fAngleMaxCurve;	// カーブの最大角度
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
	CBlockGrab *GetBlock(void) { return m_info.pBlockGrab; }
	float GetSpeed() { return m_info.fSpeed; }

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
		float fAngleHandle;	// ハンドルをきっている値
		float fTimerFlip;	// ドリフトカウンター
		float fAngleDrift;	// ドリフト時の角度倍率の値
		int nCntFlip;	// 弾きカウンター
		CBlockGrab *pBlockGrab;	// 掴んでいるブロック
		CObject3D *pRoap;
		float fCntAngle;	// アングルのカウンター
		bool bGrabOld;
		bool bManual;		// マニュアル操作
		float fLengthDrift;
		float fTimerDriftChange;
		float fSizeBlurDrift;	// ドリフト時のブラーの強さ
		float fDesityBlurDrift;	// ドリフト時のブラーの濃さ
	};

	void Load(void);
	void Input(void);
	void InputMove(void);
	void InputCamera(void);
	void InputWire(void);
	void ForwardFollowWire(float vecLength, D3DXVECTOR3 vecDiff);	// ワイヤーに沿って進める
	void JudgeChangeDrift(float fAngle, float fAngleDiff, float fLength);	// ドリフト変化の判定
	void ControlRoap(void);	// ロープの制御
	void SarchGrab(void);	// 掴むブロックの探知
	void ManageRotateGrab(float fAngleDiff);	// 掴んでいるときの回転制御
	void JudgeRemoveWire(float fLength);	// ワイヤーを外すかの判定
	void RemoveWire(void);	// ワイヤーを外す処理
	void LimitDrift(float fLength);
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