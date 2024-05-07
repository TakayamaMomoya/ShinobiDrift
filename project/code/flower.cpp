//*****************************************************
//
// 花の処理[flower.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "flower.h"
#include "collision.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float RADIUS_COLLISION = 100.0f;	// 当たり判定の半径
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
int CFlower::m_nNumAll = 0;	// 総数

//=====================================================
// コンストラクタ
//=====================================================
CFlower::CFlower(int nPriority)
{
	m_pCollisionSphere = nullptr;

	m_nNumAll++;
}

//=====================================================
// デストラクタ
//=====================================================
CFlower::~CFlower()
{
	m_nNumAll--;
}

//=====================================================
// 生成処理
//=====================================================
CFlower *CFlower::Create(void)
{
	CFlower *pFlower = nullptr;

	if (pFlower == nullptr)
	{
		pFlower = new CFlower;

		if (pFlower != nullptr)
		{
			pFlower->Init();
		}
	}

	return pFlower;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CFlower::Init(void)
{
	// 継承クラスの初期化
	CObjectX::Init();

	// 影の有効化
	EnableShadow(true);

	if (m_pCollisionSphere == nullptr)
	{// 当たり判定生成
		m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_FLOWER, CCollision::TYPE_SPHERE, this);

		if (m_pCollisionSphere != nullptr)
		{
			m_pCollisionSphere->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_pCollisionSphere->SetRadius(RADIUS_COLLISION);
		}
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CFlower::Uninit(void)
{
	// 当たり判定削除
	DeleteCollision();

	// 継承クラスの終了
	CObjectX::Uninit();
}

//=====================================================
// 当たり判定の削除
//=====================================================
void CFlower::DeleteCollision(void)
{
	if (m_pCollisionSphere != nullptr)
	{// 当たり判定の消去
		m_pCollisionSphere->Uninit();

		m_pCollisionSphere = nullptr;
	}
}

//=====================================================
// 更新処理
//=====================================================
void CFlower::Update(void)
{
	// 継承クラスの更新
	CObjectX::Update();
}

//=====================================================
// 描画処理
//=====================================================
void CFlower::Draw(void)
{
	// 継承クラスの描画
	CObjectX::Draw();
}

//=====================================================
// 位置設定
//=====================================================
void CFlower::SetPosition(D3DXVECTOR3 pos)
{
	if (m_pCollisionSphere != nullptr)
	{
		m_pCollisionSphere->SetPosition(pos);
	}

	CObjectX::SetPosition(pos);
}

//=====================================================
// ヒット処理
//=====================================================
void CFlower::Hit(float fDamage)
{
	DeleteCollision();
}