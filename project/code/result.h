//*****************************************************
//
// リザルト処理[result.h]
// Author:髙山桃也
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

	// メンバ関数
	void SetNumber(void);	// 数字の設定
	void UpdateNumber(void);	// 数字の更新
	void UpdateCaption(void);	// 見出しの更新

	// メンバ変数
	CTimer *m_pTimeOwn;	// 自身のタイム
	CUI *m_pCaption;	// 項目の見出し
	float m_fCntAnim;	// アニメーションカウンター
	vector<CUI*> m_aMenuPolygon;	// メニューのポリゴン
};

namespace Tutorial
{
CUI *CreateUIDefault(void);
}

#endif