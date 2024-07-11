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
#include "manager.h"
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
	const float MOVE_SPEED = 30.0f;  // スピード
	const float LIFE_DEFAULT = 5.0f;	// デフォルトの寿命
}

//=====================================================
// コンストラクタ
//=====================================================
CShuriken::CShuriken() : m_fLife(0.0f)
{

}

//=====================================================
// デストラクタ
//=====================================================
CShuriken::~CShuriken()
{

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
		pShuriken->SetPosition(pos);
		pShuriken->Init();
	}

	return pShuriken;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CShuriken::Init(void)
{
	CObjectX::Init();

	// モデル読込
	int nIdx = CModel::Load("data\\MODEL\\Player\\shuriken.x");
	BindModel(nIdx);

	m_aShuriken.push_back(this);

	// プレイヤー取得
	CPlayer* pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return E_FAIL;

	// プレイヤーの移動ベクトル取得
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();
	movePlayer.y = 0.0f;

	// プレイヤーの頭のマトリックス取得
	D3DXVECTOR3 posHeadPlayer = pPlayer->GetNInjaBody()->GetMtxPos(2);

	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 vecDiff = posHeadPlayer - pos;

	universal::VecConvertLength(&vecDiff, MOVE_SPEED);

	D3DXVECTOR3 move = movePlayer + vecDiff;

	SetMove(move);

	m_fLife = LIFE_DEFAULT;

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CShuriken::Uninit(void)
{
	CObjectX::Uninit();

	m_aShuriken.remove(this);
}

//=====================================================
// 更新処理
//=====================================================
void CShuriken::Update(void)
{
	CObjectX::Update();

	// 移動量の反映
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();

	pos += move;

	SetPosition(pos);

	// 寿命の減少
	m_fLife -= CManager::GetDeltaTime();

	if (m_fLife <= 0.0f)
	{
		m_fLife = 0.0f;

		Uninit();

		return;
	}

#ifdef _DEBUG
	// デバッグ処理
	Debug();
#endif
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
// デバッグ処理
//=====================================================
void CShuriken::Debug(void)
{
	// デバッグプロック取得
	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
		return;

	pDebugProc->Print("\n手裏剣の移動[%f,%f,%f]", GetMove().x, GetMove().y, GetMove().z);
	pDebugProc->Print("\n手裏剣の位置[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
}