//*****************************************************
//
// マニピュレーター[manipulater.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _MANIPULATER_H_
#define _MANIPULATER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "objectX.h"

//*****************************************************
// 前方定義
//*****************************************************
class CStateManipulater;
class CMotion;

//*****************************************************
// クラスの定義
//*****************************************************
class CManipulater : public CObject
{// マニピュレータークラス
public:
    CManipulater(int nPriority = 4);	// コンストラクタ
	~CManipulater();    // デストラクタ

    // メンバ関数
	HRESULT Init(void); // 初期化処理
	void Uninit(void);  // 終了処理
	void Update(void);  // 更新処理
	void Draw(void);    // 描画処理
    void ChangeState(CStateManipulater *pState);  // ステイトの変更

    // 変数取得・設定関数
    int GetIdxPart(void) { return m_nIdxPart; } // パーツ番号
    void SetIdxPart(int nIdx) { m_nIdxPart = nIdx; }

    // 静的メンバ関数
    static CManipulater* Create(int nIdxPart, CMotion *pMotion);    // 生成処理

private:
	// メンバ関数


	// メンバ変数
    int m_nIdxPart; // パーツの番号
    CStateManipulater *m_pState;    // ステイトのポインタ
    CMotion *m_pMotion; // モーションのポインタ
};

class CStateManipulater
{// ステイトの基底クラス
public:
    CStateManipulater() {};	// コンストラクタ
    virtual ~CStateManipulater() {};    // デストラクタ

    // メンバ関数
    virtual void Init(CManipulater *pManipulater) = 0; // 初期化処理
    virtual void Uninit(void) = 0;  // 終了処理
    virtual void Update(void) = 0;  // 更新処理

private:
};

class CStateManipulaterTranslate : public CStateManipulater
{// 移動のステイト
public:
    CStateManipulaterTranslate() {};    // コンストラクタ
    virtual ~CStateManipulaterTranslate() {};   // デストラクタ

    // メンバ関数
    void Init(void) override; // 初期化処理
    void Uninit(void) override;  // 終了処理
    void Update(void) override;  // 更新処理

private:
};

#endif
