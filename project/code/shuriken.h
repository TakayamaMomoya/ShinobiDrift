//*****************************************************
//
// 手裏剣の処理[shuriken.h]
// Author:大原怜将
//
//*****************************************************

#ifndef _SHURIKEN_H_
#define _SHURIKEN_H_

//*****************************************************
// インクルード
//*****************************************************
#include "objectX.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CShuriken : public CObjectX
{
public:

	CShuriken();	// コンストラクタ
	~CShuriken();	                // デストラクタ

	HRESULT Init(void);             // 初期化処理
	void Uninit(void);              // 終了処理
	void Update(void);              // 更新処理
	void Draw(void);                // 描画処理
	static CShuriken* Create(D3DXVECTOR3 pos);     // 生成処理

private:

	void MoveToPlyaer(void);  // プレイヤーに向かって移動する処理

};

#endif