//*****************************************************
//
// タイトル処理[title.h]
// Author:��山桃也
//
//*****************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "scene.h"
#include "motion.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CMotion;
class COrbit;
class CTitleBehavior;
class CObjectX;
class CUI;
class CFan3D;

//*****************************************************
// クラスの定義
//*****************************************************
class CTitle : public CScene
{
public:
	enum STATE
	{
		STATE_NONE = 0,	// 何もしてない状態
		STATE_OUT,		// フェードアウト状態
		START_MAX
	};

	CTitle();	// コンストラクタ
	~CTitle();	// デストラクタ

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void ChangeBehavior(CTitleBehavior *pBehavior);
	STATE GetState(void) { return m_state; }
	static CMotion *GetPlayer(void) { return m_pPlayer; }
	static CMotion *GetBike(void) { return m_pBike; }
	void PlayerAcceleration(void);  // プレイヤーが加速する
	void DoorOpen(void);            // 格納庫のドアが開く
	
private:
	// メンバ関数
	void CreateLight(void);	// ライトの生成

	// メンバ変数
	STATE m_state;				    // 状態
	CUI *m_pTitleLogo;       // タイトルロゴのポインタ
	CUI *m_pTeamLogo;        // チームロゴのポインタ
	CFan3D *m_pFan3D;               // トンネルの扉のポインタ
	COrbit *m_pOrbitLamp;           // テールランプのポインタ
	CObjectX *m_pDoorFrame;         // 格納庫のドアフレームのポインタ
	CObjectX *m_pRightDoor;         // 格納庫のドアの右のポインタ
	CObjectX *m_pLeftDoor;          // 格納庫のドアの左のポインタ
	CObjectX *m_pGarage;            // 格納庫のポインタ
	static CMotion *m_pPlayer;	    // プレイヤーモデル
	static CMotion *m_pBike;        // バイクモデル
	CTitleBehavior *m_pBehavior;	// ビヘイビア
	float m_fTImerSmoke;	        // 煙のスポーンタイマー
};

class CTitleBehavior
{// 基本ビヘイビア
public:
	CTitleBehavior();	        // コンストラクタ
	virtual ~CTitleBehavior();	// デストラクタ

	virtual void Update(CTitle *pTItle) = 0;

private:
};

class CTitleStart : public CTitleBehavior
{// スタート表示状態
public:
	CTitleStart();	        // コンストラクタ
	virtual ~CTitleStart();	// デストラクタ
	void Update(CTitle *pTItle) override;

private:
	CUI *m_pStart;	// スタート表示のポインタ
	CUI *m_pAfter;	// スタート表示の残像
};

class CTitleMenu : public CTitleBehavior
{// メニュー
public:
	enum MENU
	{
		MENU_GAME = 0,	    // ゲーム
		MENU_TRANING,	    // 訓練場
		MENU_MAX
	};

	CTitleMenu();	        // コンストラクタ
	virtual ~CTitleMenu();	// デストラクタ
	void Update(CTitle *pTItle) override;

private:
	void Input(void);
	void ManageCursor(void);
	
	CUI *m_apMenu[MENU_MAX];	// メニュー項目
	CUI *m_pCursor;	        // カーソル
	MENU m_menu;	                // 選択メニュー項目

	bool m_IsGameStarted = false;
};

class CTitleBehindPlayer : public CTitleBehavior
{// プレイヤーの背後に回る
public:
	CTitleBehindPlayer();           // コンストラクタ
	virtual ~CTitleBehindPlayer();  // デストラクタ
	void Update(CTitle* pTItle) override;

private:

};

class CTitlePlayerAcceleration : public CTitleBehavior
{// プレイヤーが加速し始める
public:
	CTitlePlayerAcceleration();           // コンストラクタ
	virtual ~CTitlePlayerAcceleration();  // デストラクタ
	void Update(CTitle* pTItle) override;

private:

};

class CTitleMovePlayer : public CTitleBehavior
{
public:
	CTitleMovePlayer();           // コンストラクタ
	virtual ~CTitleMovePlayer();  // デストラクタ
	void Update(CTitle* pTItle) override;

private:

};

class CTitleFade : public CTitleBehavior
{
public:
	CTitleFade();           // コンストラクタ
	virtual ~CTitleFade();  // デストラクタ
	void Update(CTitle* pTItle) override;

private:
	void Fade(void);              // フェード処理

	float m_fVolume = 1.0f;
};

#endif