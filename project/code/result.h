//*****************************************************
//
// リザルト処理[result.h]
// Author:��山桃也
//
//*****************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CUI;
class CStateResult;
class CNumber;
class CTimer;
class CPolygon2D;

//*****************************************************
// クラスの定義
//*****************************************************
class CResult : public CObject
{// チュートリアルのクラス
public:
	CResult();	// コンストラクタ
	~CResult();	// デストラクタ

	// メンバ関数
	virtual HRESULT Init(void);	// 初期化
	virtual void Uninit(void);	// 終了
	virtual void Update();	// 更新
	virtual void Draw();	// 描画
	void UpdateBack(void);	// 背景ポリゴンの更新
	void ChangeState(CStateResult *pState);	// ステイトの変更
	void StartFade(void);	// フェード
	void EnableBack(void);	// 背景の有効化

	// 変数取得・設定関数
	float GetTime(void) { return m_fTime; }	// タイムの取得

	// 静的メンバ関数
	static CResult *Create(void);	// 生成処理
private:
	// メンバ関数
	void SetPlayer(void);	// プレイヤー設定
	void SetCamera(void);	// カメラ設定
	void SaveTime(void);	// タイムの保存

	// メンバ変数
	CStateResult *m_pState;
	CPolygon2D *m_pBack;	// 背景のポリゴン
	float m_fTime;	// タイムの保存用
};

class CStateResult
{// ステイトの基底クラス
public:
	CStateResult() {};	// コンストラクタ
	virtual ~CStateResult() {};	 // デストラクタ

	// メンバ関数
	virtual void Init(CResult *pResult) = 0;	// 初期化処理
	virtual void Uninit(CResult *pResult);	// 終了処理
	virtual void Update(CResult *pResult) = 0;	// 更新処理

private:
};

class CStateResultApperPlayer : public CStateResult
{// プレイヤー登場
public:
	CStateResultApperPlayer();	// コンストラクタ
	virtual ~CStateResultApperPlayer();	 // デストラクタ

	// メンバ関数
	void Init(CResult *pResult) override;	// 初期化処理
	void Uninit(CResult *pResult) override;	// 終了処理
	void Update(CResult *pResult) override;	// 更新処理

private:
	// メンバ関数
	void MovePlayer(void);	// プレイヤーを動かす処理
	void Particle(CResult *pResult);	// パーティクルを出す処理

	// メンバ変数
	D3DXVECTOR3 m_posDest;	// 目標の位置
};

class CStateResultDispTime : public CStateResult
{// タイム表示
public:
	CStateResultDispTime();	// コンストラクタ
	virtual ~CStateResultDispTime();	 // デストラクタ

	// メンバ関数
	void Init(CResult *pResult) override;	// 初期化処理
	void Uninit(CResult *pResult) override;	// 終了処理
	void Update(CResult *pResult) override;	// 更新処理

private:
	// 列挙型定義
	enum E_Menu
	{// メニュー項目
		MENU_CONTINUE = 0,	// コンティニュー
		MENU_QUIT,	// 戻る
		MENU_MAX
	};
	enum E_State
	{// 状態
		STATE_NONE = 0,	// 何もしていない状態
		STATE_APPER,	// 出現状態
		STATE_SELECT,	// メニュー選択状態
		STATE_MAX
	};

	// メンバ関数
	void SetNumber(CResult *pResult);	// 数字の設定
	void UpdateNumber(void);	// 数字の更新
	void UpdateCaption(void);	// 見出しの更新
	void UpdateMenu(void);	// メニュー項目の更新
	void Input(void);	// 入力処理
	void Fade(E_Menu menu);	// フェード処理
	void Sort(void);	// ソート処理
	void CreateNewRecord(void);	// ニューレコード表示の生成
	void UpdateNewRecord(void);	// ニューレコード表示の更新

	// メンバ変数
	CTimer *m_pTimeOwn;	// 自身のタイム
	CUI *m_pCaption;	// 項目の見出し
	CUI *m_pNewRecord;	// ニューレコード表示
	float m_fCntAnim;	// アニメーションカウンター
	vector<CUI*> m_aMenuPolygon;	// メニューのポリゴン
	E_State m_state;	// 状態
	int m_nCurrent;	// 選択番号
	float m_fTimerFlash; // 点滅タイマー
};

namespace Tutorial
{
CUI *CreateUIDefault(void);
}

#endif