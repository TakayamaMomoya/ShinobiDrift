//*****************************************************
//
// パーツの処理[parts.cpp]
// Author:髙山桃也
//
//*****************************************************

#ifndef _PARTS_H_
#define _PARTS_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "model.h"
#include "physics.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define NUM_TEX	(5)	// テクスチャの数

//*****************************************************
// クラス定義
//*****************************************************
class CParts
{
public:
	CParts();	// コンストラクタ
	~CParts();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DrawShadow(void);
	void InitPhysics(void);
	static CParts *Create(D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f }, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f });
	float GetWidth(void) { return 0.0f; }	// サイズ取得
	float GetHeight(void) { return 0.0f; }	// サイズ取得
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// 設定処理
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// 取得処理
	void SetMove(D3DXVECTOR3 move) { m_move = move; }	// 設定処理
	D3DXVECTOR3 GetMove(void) { return m_move; }	// 取得処理
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	D3DXVECTOR3 GetPosOrg(void) { return m_posOrg; }	// 取得処理
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }// 向き設定処理
	void SetPosOrg(D3DXVECTOR3 pos) { m_posOrg = pos; }// 向き設定処理
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	// 向き取得処理
	void BindModel(int nIdx);
	int GetIdxModel(void) { return m_IdxModel; }
	void SetIdxModel(int nIdx) { m_IdxModel = nIdx; }
	void SetRadius(void);
	float GetRadius(void) { return m_fRadius; }
	D3DXMATRIX *GetMatrix(void) { return &m_mtxWorld; }
	D3DXMATRIX* GetMatrixOld(void) { return &m_mtxWorldOld; }
	void SetMatrix(void);
	CModel::Model *GetModel(void) { return m_pModel; }
	void SetModel(CModel::Model *pModel) { m_pModel = pModel; }
	void SetEmissiveCol(D3DXCOLOR col) { m_col = col; m_bChangeCol = true; }
	D3DXCOLOR GetEmissiveCol(void) { return m_col; }
	void ResetColor(void) { m_bChangeCol = false; }

private:
	D3DXVECTOR3 m_pos;								// 位置
	D3DXVECTOR3 m_posOrg;							// 最初の位置
	D3DXVECTOR3 m_posOld;	                        // 前回の位置
	D3DXVECTOR3 m_move;	                            // 移動量
	D3DXVECTOR3 m_rot;								// 向き
	D3DXVECTOR3 m_vtxMax;	                        // 最大頂点
	D3DXVECTOR3 m_vtxMin;	                        // 最小頂点
	D3DXCOLOR m_col;	                            // 色
	D3DXMATRIX m_mtxWorld;							// ワールドマトリックス
	D3DXMATRIX m_mtxWorldOld;						// 前回のワールドマトリックス
	CModel::Model *m_pModel;	                    // モデル情報
	int m_IdxModel;	                                // モデルの番号
	float m_fRadius;	                            // モデルの半径
	bool m_bChangeCol;	                            // 色を変えるかどうか

	// 物理演算に必要
	btDiscreteDynamicsWorld* m_pDynamicsWorld;      // ダイナミクスワールド
	btScalar m_nMass;                               // 物体の質量：0だと動かないよ
	int m_nIdxPhysics;                              // 番号
};

#endif