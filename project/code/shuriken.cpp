//*****************************************************
//
// 手裏剣の処理[shuriken.h]
// Author:大原怜将
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "shuriken.h"
#include "effekseer.h"
#include "model.h"
#include "player.h"
#include "debugproc.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	
}

//=====================================================
// コンストラクタ
//=====================================================
CShuriken::CShuriken()
{

}

//=====================================================
// デストラクタ
//=====================================================
CShuriken::~CShuriken()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CShuriken::Init(void)
{
	// 継承クラスの初期化
	CObjectX::Init();

	// モデル読込
	int nIdx = CModel::Load("data\\MODEL\\Player\\02_head.x");
	BindModel(nIdx);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CShuriken::Uninit(void)
{
	// 継承クラスの初期化
	CObjectX::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CShuriken::Update(void)
{
	// 継承クラスの初期化
	CObjectX::Update();

	// プレイヤーの位置に向かう
	MoveToPlyaer();

	// デバッグプロック取得
	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
		return;

	pDebugProc->Print("\n手裏剣の位置[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
}

//=====================================================
// 描画処理
//=====================================================
void CShuriken::Draw(void)
{
	// 継承クラスの初期化
	CObjectX::Draw();
}

//=====================================================
// 生成処理
//=====================================================
CShuriken* CShuriken::Create(D3DXVECTOR3 pos)
{
	CShuriken *pShuriken = nullptr;
	pShuriken = new CShuriken;

	if (pShuriken != nullptr)
	{
		pShuriken->Init();
		pShuriken->SetPosition(pos);
	}
		
	return pShuriken;
}

//=====================================================
// プレイヤーに向かって移動する処理
//=====================================================
void CShuriken::MoveToPlyaer(void)
{
	// 自分の位置取得
	D3DXVECTOR3 pos = GetPosition();

	// プレイヤーの取得と位置取得
	CPlayer* pPlayer = CPlayer::GetInstance();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();
	D3DXMATRIX PlayerMatrix = *pPlayer->GetParts(2)->pParts->GetMatrix();
	

	// 目標の位置に向かう
	universal::MoveToDest(&pos, D3DXVECTOR3(PlayerMatrix._41, PlayerMatrix._42 + 200.0f, PlayerMatrix._43), 0.05f);

	// 位置設定
	SetPosition(pos);
}