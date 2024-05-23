//*****************************************************
//
// メッシュエディターの処理[editMesh.h]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "edit.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CObject3D;
class CObjectX;
class CStateEditMesh;

//*****************************************************
// クラスの定義
//*****************************************************
class CEditMesh : public CEdit
{
public:
	CEditMesh();
	~CEditMesh();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void ChangeState(CStateEditMesh *pState);

private:
	CObject3D *m_pMesh;	// メッシュのポインタ
	CObjectX *m_pManipulator;	// マニピュレーター
	CStateEditMesh *m_pState;	// ステイト
};

class CStateEditMesh
{// メッシュエディットのステイト基底クラス
public:
	CStateEditMesh() {};
	virtual ~CStateEditMesh() {};

	virtual void Update(CEditMesh *pEdit) = 0;
};

class CStateEditMeshCreateMesh : public CStateEditMesh
{// メッシュの生成
public:
	CStateEditMeshCreateMesh() {};
	virtual ~CStateEditMeshCreateMesh() {};

	void Update(CEditMesh *pEdit) override;
};

class CStateEditMeshCurve : public CStateEditMesh
{// カーブの調節
public:
	CStateEditMeshCurve() {};
	virtual ~CStateEditMeshCurve() {};

	void Update(CEditMesh *pEdit) override;
};

class CStateEditMeshDeleteEdge : public CStateEditMesh
{// 辺の削除
public:
	CStateEditMeshDeleteEdge() {};
	virtual ~CStateEditMeshDeleteEdge() {};

	void Update(CEditMesh *pEdit) override;
};