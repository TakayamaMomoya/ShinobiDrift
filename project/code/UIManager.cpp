//*****************************************************
//
// UIマネージャー[UIManager.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "UIManager.h"
#include "UI.h"
#include "inputkeyboard.h"
#include "texture.h"
#include "player.h"
#include "meter.h"
#include "rankTime.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const D3DXVECTOR3 POS_FRAME = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f };
const D3DXCOLOR COL_NORMAL = { 1.0f,1.0f,1.0f,1.0f };
const D3DXCOLOR COL_DAMAGE = { 1.0f,0.0f,0.0f,1.0f };
const float SPEED_FRAME = 0.1f;	// フレームの速度
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CUIManager *CUIManager::m_pUIManager = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CUIManager::CUIManager()
{
	m_fCntFrame = 0.0f;
	m_bDisp = false;
	m_pMeter = nullptr;
	m_pRankTime = nullptr;
}

//=====================================================
// デストラクタ
//=====================================================
CUIManager::~CUIManager()
{

}

//=====================================================
// 生成処理
//=====================================================
CUIManager *CUIManager::Create(void)
{
	if (m_pUIManager == nullptr)
	{// インスタンス生成
		m_pUIManager = new CUIManager;

		// 初期化処理
		m_pUIManager->Init();
	}

	return m_pUIManager;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CUIManager::Init(void)
{
	m_bDisp = true;

	// メーター生成
	m_pMeter = CMeter::Create();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CUIManager::Uninit(void)
{
	ReleaseMeter();

	m_pUIManager = nullptr;

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CUIManager::Update(void)
{
#ifdef _DEBUG
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard != nullptr)
	{
		if (pKeyboard->GetTrigger(DIK_1))
		{
			m_bDisp = m_bDisp ? false : true;
		}
	}
#endif
}

//=====================================================
// 描画処理
//=====================================================
void CUIManager::Draw(void)
{
#ifdef _DEBUG

#endif
}

//=====================================================
// メーターの解放
//=====================================================
void CUIManager::ReleaseMeter(void)
{
	if (m_pMeter != nullptr)
	{
		m_pMeter->Uninit();
		m_pMeter = nullptr;
	}
}

//=====================================================
// ランクタイマーの生成
//=====================================================
void CUIManager::CreateRankTImer(void)
{
	if (m_pRankTime != nullptr)
		return;

	m_pRankTime = CRankTime::Create();
}

//=====================================================
// ランクタイマーの解放
//=====================================================
void CUIManager::ReleaseRankTimer(void)
{
	if (m_pRankTime != nullptr)
	{
		m_pRankTime->Uninit();
		m_pRankTime = nullptr;
	}
}

//=====================================================
// ゲームUIの一括解放
//=====================================================
void CUIManager::ReleaseGameUI(void)
{
	ReleaseMeter();
	ReleaseRankTimer();
}