//*****************************************************
//
// メッシュエディターの処理[editMesh.h]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "edit.h"
#include <vector>
#include <list>
#include "meshRoad.h"

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

//*****************************************************
// ステイトクラスの定義
//*****************************************************
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

private:
	void LimitPos(D3DXVECTOR3 *pPos);
};

class CStateEditMeshCreateTunnel : public CStateEditMesh
{// トンネルの生成
public:
	CStateEditMeshCreateTunnel();	// コンストラクタ
	virtual ~CStateEditMeshCreateTunnel() {};	// デストラクタ

	// メンバ関数
	void Update(CEditMesh *pEdit) override;	// 更新処理

private:
	// メンバ関数
	void SetTunnel(std::vector<CMeshRoad::SInfoRoadPoint>::iterator it);

	// メンバ変数
	bool m_bEnd;	// スタートの選択かどうか
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator m_itStart;	// トンネルの開始イテレイター
	std::vector<CMeshRoad::SInfoRoadPoint>::iterator m_itEnd;	// トンネルの終了イテレイター
};

class CStateEditMeshAdjustRoadPoint : public CStateEditMesh
{// ロードポイントの調節
public:
	CStateEditMeshAdjustRoadPoint();
	virtual ~CStateEditMeshAdjustRoadPoint() {};

	void Update(CEditMesh *pEdit) override;
};

class CStateEditMeshDeleteRoadPoint : public CStateEditMesh
{// ロードポイントの削除
public:
	CStateEditMeshDeleteRoadPoint();
	virtual ~CStateEditMeshDeleteRoadPoint() {};

	void Update(CEditMesh *pEdit) override;
};