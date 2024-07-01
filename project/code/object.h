//*****************************************************
//
// オブジェクトの処理[object.h]
// Author:��山桃也
//
//*****************************************************

#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CPlayer;
class CBlock;

//*****************************************************
// マクロ定義
//*****************************************************
#define NUM_OBJECT	(4096)	//	オブジェクトの数
#define NUM_PRIORITY	(8)	// 優先順位の最大数

//*****************************************************
// クラスの定義
//*****************************************************
class CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// 何でもない
		TYPE_PLAYER,	// プレイヤー
		TYPE_ENEMY,	// 敵
		TYPE_BLOCK,	// ブロック
		TYPE_BULLET,	// 弾
		TYPE_PARTICLE,	// パーティクル
		TYPE_MAX
	}TYPE;

	CObject(int nPriority = 4);	// コンストラクタ
	virtual ~CObject();	//	デストラクタ

	virtual HRESULT Init(void) = 0;	// 初期化処理
	virtual void Uninit(void) = 0;	// 終了処理
	virtual void Update(void) = 0;	// 更新処理
	virtual void Draw(void) {};	// 描画処理
	static void ReleaseAll(void);	// 全てリリース
	static void UpdateAll(void);	// 全て更新
	static void UpdateNotStop(void);	// 動かないオブジェクトの更新
	static void DeleteAll(void);	// 全削除処理
	static void DrawAll(void);	// 全て描画
	static void DrawObject(bool bBlur);	// オブジェクトの描画
	virtual void Hit(float fDamage){}	// ヒット処理
	void SetType(TYPE type);
	TYPE GetType(void) { return m_type; }
	virtual void SetPosition(D3DXVECTOR3 pos) {};	// 設定処理
	virtual D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(); }	// 位置取得処理
	virtual D3DXVECTOR3 GetPositionOld(void) { return D3DXVECTOR3(); }	// 位置取得処理
	virtual float GetWidth(void) { return 0.0f; };	// サイズ取得
	virtual float GetHeight(void) { return 0.0f; }	// サイズ取得
	void EnableWire(bool bWire) { m_bWire = bWire; }
	static int GetNumAll(void) { return m_nNumAll; }
	bool IsDeath(void) { return m_bDeath; }
	void EnableZtest(bool bZtest) { m_bZtest = bZtest; }
	void EnableLighting(bool bLighting) { m_bLighting = bLighting; }
	void EnableAdd(bool bAdd) { m_bAdd = bAdd; }
	void EnableNotStop(bool bNotStop);
	void EnableFog(bool bFog) { m_bFog = bFog; }
	void EnableCull(bool bCull) { m_bCull = bCull; }
	void SetAlphaTest(DWORD dValue) { m_dAlpha = dValue; }
	DWORD GetAlpha(void) { return m_dAlpha; }
	void EnableBlur(bool bBlur) { m_bBlur = bBlur; }

protected:
	void Release(void);	// 個別リリース処理

private:
	void Delete(void);	// 個別削除処理

	static int m_nNumAll;	// 総数
	int m_nID;	// 自分のID
	TYPE m_type;	// 種類
	int m_nPriority;	// 描画の優先順位
	static CObject *m_apTop[NUM_PRIORITY];	// 先頭のオブジェクトのアドレス
	static CObject *m_apCur[NUM_PRIORITY];	// 最後尾のオブジェクトのアドレス
	CObject *m_pPrev;	// 前のオブジェクトのアドレス
	CObject *m_pNext;	// 次のオブジェクトのアドレス
	bool m_bDeath;	// 死亡フラグ
	bool m_bWire;	// ワイヤーフレームで表示するかどうか
	bool m_bZtest;	// Zテストで前に出すかどうか
	bool m_bLighting;	// ライティングを有効化するかどうか
	bool m_bNotStop;	// 止まらないオブジェクトかどうか
	bool m_bAdd;	// 加算合成するかどうか
	bool m_bFog;	// フォグをかけるかどうか
	bool m_bCull;	// カリングするかどうか
	DWORD m_dAlpha;	// アルファテストの値
	bool m_bBlur;	// ブラーをかけるかどうか
	static CObject *m_apNotStop[NUM_OBJECT];	// 停止中にも動くオブジェクトの配列
};

namespace Object
{
void DeleteObject(CObject **ppObject, int nSize = 1);
}


#endif