//*****************************************************
//
// チュートリアル処理[tutorial.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CUI;
class CStateTutorial;

//*****************************************************
// クラスの定義
//*****************************************************
class CTutorial : public CObject
{// チュートリアルのクラス
public:
	CTutorial();	// コンストラクタ
	~CTutorial();	// デストラクタ

	// メンバ関数
	virtual HRESULT Init(void);	// 初期化
	virtual void Uninit(void);	// 終了
	virtual void Update();	// 更新
	virtual void Draw();	// 描画
	void ChangeState(CStateTutorial *pState);	// ステイトの変更

	// 変数取得・設定関数
	void EnableEnd(bool bEnd) { m_bEnd = bEnd; }	// 終了フラグ
	bool IsEnd(void) { return m_bEnd; }
	std::map<int, CUI*> *GetMap(void) { return &m_mapUI; }	// UIのマップコンテナ取得
	std::map<int, float> GetMapCounter(void) { return m_mapCounter; }	// カウンターのマップコンテナ取得
	void SetMapCounter(std::map<int, float> map) { m_mapCounter = map; }	// カウンターのマップコンテナ取得

	// 静的メンバ関数
	static CTutorial *Create(void);	// 生成処理
private:
	// メンバ関数
	void StartGame(void);	// ゲーム開始の処理

	// メンバ変数
	std::map<int, CUI*> m_mapUI;	// UIのマップコンテナ
	std::map<int, float> m_mapCounter;	// カウンターのマップコンテナ
	CStateTutorial *m_pState;	// ステイトのポインタ
	bool m_bEnd;	// 終了フラグ
};

class CStateTutorial
{// ステイトの基底クラス
public:
	CStateTutorial() {};	// コンストラクタ
	virtual ~CStateTutorial() {};	 // デストラクタ

	// メンバ関数
	virtual void Init(CTutorial *pTutorial) = 0;	// 初期化処理
	virtual void Uninit(CTutorial *pTutorial);	// 終了処理
	virtual void Update(CTutorial *pTutorial) = 0;	// 更新処理
	virtual bool IsEndInput(void) { return false; }	// 終了しているかどうか
private:
};

class CStateTutorialMove : public CStateTutorial
{// 移動のチュートリアル
public:
	CStateTutorialMove();	// コンストラクタ
	virtual ~CStateTutorialMove();	 // デストラクタ

	// メンバ関数
	void Init(CTutorial *pTutorial) override;	// 初期化処理
	void Uninit(CTutorial *pTutorial) override;	// 終了処理
	void Update(CTutorial *pTutorial) override;	// 更新処理
	bool IsEndInput(CTutorial *pTutorial);	// 終了判定

private:
	enum E_MENU
	{// メニュー項目
		MENU_ACCELE = 0,	// アクセル
		MENU_BRAKE,	// ブレーキ
		MENU_MAX
	};
};

namespace Tutorial
{
CUI *CreateUIDefault(void);
}

#endif