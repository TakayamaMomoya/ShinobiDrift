//*****************************************************
//
// 敵スポナー[enemySpawner.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _ENEMYSPAWNER_H_
#define _ENEMYSPAWNER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object3D.h"
#include "polygon3D.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemySpawner : public CObject3D
{
public:
	CEnemySpawner(int nPriority = 7);	// コンストラクタ
	~CEnemySpawner();	//	デストラクタ

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// 位置設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// 位置取得
	void SetRotation(float fRot) { m_fRot = fRot; }	// 向き取得設定
	float GetRotation() { return m_fRot; }	// 向き取得処理

	// 静的メンバ関数
	static CEnemySpawner* Create(D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f }, float fRot = 0.0f, float fLength = 1000.0f);	// 生成

private:
	// メンバ関数
	void SetPolygon(void);

	// メンバ変数
	int m_nTransitionTime;		// 遷移時間
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_posStart;	// ゴールの始点
	D3DXVECTOR3 m_posEnd;	// ゴールの終点
	float m_fRot;		// 向き
	float m_fLength;	// 長さ
	CPolygon3D* m_pObj3D;	// オブジェクト3Dのポインタ
};

#endif
