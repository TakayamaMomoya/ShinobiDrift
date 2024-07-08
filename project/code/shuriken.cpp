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
// 静的メンバ変数
//*****************************************************
std::list<CShuriken*> CShuriken::m_aShuriken;

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const float MOVE_SPEED = 0.05f;  // 移動量
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

	m_aShuriken.push_back(this);

	// プレイヤー取得
	CPlayer* pPlayer = CPlayer::GetInstance();

	// プレイヤーの頭のマトリックス取得
	m_PlayerMtx = *pPlayer->GetParts(2)->pParts->GetMatrix();

	float PlayerSpeed = pPlayer->GetSpeed();

	m_PlayerMtx._41 += PlayerSpeed;
	m_PlayerMtx._43 += PlayerSpeed;

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CShuriken::Uninit(void)
{
	// 継承クラスの初期化
	CObjectX::Uninit();

	m_aShuriken.remove(this);
}

//=====================================================
// 更新処理
//=====================================================
void CShuriken::Update(void)
{
	// 継承クラスの初期化
	CObjectX::Update();

	// プレイヤーの位置に向かう
	MoveToPlayer();

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
void CShuriken::MoveToPlayer(void)
{
	// 自分の位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 目標の位置に向かう
	universal::MoveToDest(&pos, D3DXVECTOR3(m_PlayerMtx._41, m_PlayerMtx._42 + 200.0f, m_PlayerMtx._43), MOVE_SPEED);

	// 位置設定
	SetPosition(pos);
}