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
	std::map<int, CUI*> *GetMap(void) { return &m_mapUI; }	// マップコンテナ取得
	void ChangeState(CStateTutorial *pState);	// ステイトの変更

	// 静的メンバ関数
	static CTutorial *Create(void);	// 生成処理
private:
	// メンバ関数
	void StartGame(void);	// ゲーム開始の処理

	// メンバ変数
	std::map<int,CUI*> m_mapUI;	// UIのマップコンテナ
	CStateTutorial *m_pState;	// ステイトのポインタ
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

private:
};

#endif