//*****************************************************
//
// リザルト処理[result.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "result.h"
#include "player.h"
#include "camera.h"
#include "manager.h"
#include "cameraState.h"
#include "inputManager.h"
#include "game.h"
#include "number.h"
#include "timer.h"
#include "polygon2D.h"
#include "blur.h"
#include "debugproc.h"
#include "UIManager.h"
#include "UI.h"
#include "texture.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const D3DXVECTOR3 POS_DISP_TIME = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.4f, 0.0f };	// タイムの表示位置
const string PATH_SAVE = "data\\BYNARY\\gametime.bin";	// ゲームの記録時間の保存
const D3DXCOLOR COL_BACK = { 0.0f ,0.0f,0.0f,0.6f };	// 背景ポリゴンの色
const float SPEED_BACK_COLOR = 0.2f;	// 背景の出てくるスピード
const D3DXCOLOR COL_DEST_NUMBER = { 1.0f ,1.0f,1.0f,1.0f };	// 数字ポリゴンの目標色
const float SPEED_APPER_TIME = 0.1f;	// タイマーの出現スピード
const D3DXVECTOR3 POS_TIMER = { 0.4f,0.55f,0.0f };	// タイマーの初期位置
const D3DXVECTOR2 SIZE_CAPTION = { 0.3f, 0.05f };	// キャプションのサイズ
const string PATH_TEX_CAPTION = "data\\TEXTURE\\UI\\resultCaption00.png";	// キャプションのテクスチャパス
const D3DXVECTOR3 POS_CAPTION_INITIAL = { 1.0f + SIZE_CAPTION.x,0.4f,0.0f };	// キャプションの初期位置
const D3DXVECTOR3 POS_CAPTION_DEST = { 0.5f,0.4f,0.0f };	// キャプションの目標位置
const float SPEED_CAPTION = 0.05f;	// キャプションのスピード
}

//=====================================================
// コンストラクタ
//=====================================================
CResult::CResult() : CObject(1), m_pState(nullptr)
{

}

//=====================================================
// デストラクタ
//=====================================================
CResult::~CResult()
{

}

//=====================================================
// 生成処理
//=====================================================
CResult *CResult::Create(void)
{
	CResult *pResult = nullptr;

	pResult = new CResult;

	if (pResult != nullptr)
	{
		pResult->Init();
	}

	return pResult;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CResult::Init(void)
{
	// プレイヤーの設定
	SetPlayer();

	// カメラ位置の設定
	SetCamera();

	// タイムの保存
	SaveTime();

	// 背景の有効化
	EnableBack();

	// ステイトの変更
	ChangeState(new CStateResultDispTime);
	
	// ゲームタイマーの削除
	CGame *pGame = CGame::GetInstance();

	if (pGame == nullptr)
		return E_FAIL;

	pGame->ReleaseGameTimer();

	// ゲームUIの削除
	CUIManager *pUIManager = CUIManager::GetInstance();

	if (pUIManager != nullptr)
		pUIManager->ReleaseGameUI();

	return S_OK;
}

//=====================================================
// プレイヤー設定
//=====================================================
void CResult::SetPlayer(void)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;
	
	// プレイヤーを操作できないようにする
	pPlayer->SetEnableInput(false);
}

//=====================================================
// カメラ設定
//=====================================================
void CResult::SetCamera(void)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
		return;
	
	pCamera->ChangeState(new CCameraStateResult);
}

//=====================================================
// タイムの保存
//=====================================================
void CResult::SaveTime(void)
{
	CGame *pGame = CGame::GetInstance();

	if (pGame == nullptr)
		return;

	CTimer *pTimer = pGame->GetGameTimer();

	if (pTimer == nullptr)
		return;

	// タイムの取得
	float fSecond = pTimer->GetSecond();

	// ファイルに保存
	std::ofstream outputFile(PATH_SAVE, std::ios::binary);

	if (!outputFile.is_open())
		assert(("タイムのファイルを開けませんでした", false));

	outputFile.write(reinterpret_cast<const char*>(&fSecond), sizeof(float));
}

//=====================================================
// 終了処理
//=====================================================
void CResult::Uninit(void)
{
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CResult::Update(void)
{
	if (m_pState != nullptr)
	{
		m_pState->Update(this);
	}

	// 背景ポリゴンの色の補正
	UpdateBack();
}

//=====================================================
// 描画処理
//=====================================================
void CResult::Draw(void)
{

}

//=====================================================
// 背景ポリゴンの更新
//=====================================================
void CResult::UpdateBack(void)
{
	if (m_pBack == nullptr)
		return;

	// 色を目標の色に向かって補正する
	D3DXCOLOR col = m_pBack->GetCol();

	col += (COL_BACK - col) * SPEED_BACK_COLOR;

	m_pBack->SetCol(col);
}

//=====================================================
// ステイトの変更
//=====================================================
void CResult::ChangeState(CStateResult *pState)
{
	if (m_pState != nullptr)
	{
		m_pState->Uninit(this);
		delete m_pState;
		m_pState = nullptr;
	}

	m_pState = pState;

	if (m_pState != nullptr)
	{
		m_pState->Init(this);
	}
}

//=====================================================
// フェードを始める処理
//=====================================================
void CResult::StartFade(void)
{
	CGame *pGame = CGame::GetInstance();

	if (pGame == nullptr)
		return;

	pGame->SetState(CGame::STATE::STATE_END);
}

//=====================================================
// 背景の有効化
//=====================================================
void CResult::EnableBack(void)
{
	if (m_pBack != nullptr)
		return;

	// 背景ポリゴンの生成
	m_pBack = CPolygon2D::Create(6);

	if (m_pBack == nullptr)
		return;

	m_pBack->SetPosition(SCRN_MID);
	m_pBack->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pBack->SetVtx();
	m_pBack->EnableBlur(false);

	// 完全に透明に設定
	m_pBack->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
}

//=====================================================
// ステイトの終了
//=====================================================
void CStateResult::Uninit(CResult *pResult)
{

}

//********************************************************************************
// タイム表示
//********************************************************************************
//=====================================================
// コンストラクタ
//=====================================================
CStateResultDispTime::CStateResultDispTime() : m_pTimeOwn(nullptr), m_pCaption(nullptr), m_fCntAnim(0.0f)
{

}

//=====================================================
// デストラクタ
//=====================================================
CStateResultDispTime::~CStateResultDispTime()
{

}

//=====================================================
// 初期化
//=====================================================
void CStateResultDispTime::Init(CResult *pResult)
{
	// 数字の設定
	SetNumber();

	// 項目の見出し生成
	if (m_pCaption == nullptr)
	{
		m_pCaption = CUI::Create();

		if (m_pCaption != nullptr)
		{
			m_pCaption->SetSize(SIZE_CAPTION.x, SIZE_CAPTION.y);
			
			m_pCaption->SetPosition(POS_CAPTION_INITIAL);
			int nIdx = Texture::GetIdx(&PATH_TEX_CAPTION[0]);
			m_pCaption->SetIdxTexture(nIdx);
			m_pCaption->SetVtx();
		}
	}

	// メニュー項目の生成
	
}

//=====================================================
// 数字の設定
//=====================================================
void CStateResultDispTime::SetNumber(void)
{
	CGame *pGame = CGame::GetInstance();

	if (pGame == nullptr)
		return;

	CTimer *pGameTimer = pGame->GetGameTimer();

	if (pGameTimer == nullptr)
		return;

	pGameTimer->SetFlag(true);

	// 自身のタイマー生成
	m_pTimeOwn = CTimer::Create();

	if (m_pTimeOwn == nullptr)
		return;

	// ゲームタイマーのタイムをコピー
	float fTime = pGameTimer->GetSecond();
	m_pTimeOwn->SetSecond(fTime);
	m_pTimeOwn->SetColor(CTimer::E_Number::NUMBER_MAX, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pTimeOwn->SetPosition(POS_TIMER);
}

//=====================================================
// 終了
//=====================================================
void CStateResultDispTime::Uninit(CResult *pResult)
{
	CStateResult::Uninit(pResult);
}

//=====================================================
// 更新
//=====================================================
void CStateResultDispTime::Update(CResult *pResult)
{
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager == nullptr)
		return;

	// 数字の更新
	UpdateNumber();

	// 見出しの更新
	UpdateCaption();

	// フェードを始める
	if (pInputManager->GetTrigger(CInputManager::BUTTON_ENTER))
		pResult->StartFade();
}

//=====================================================
// 数字の更新
//=====================================================
void CStateResultDispTime::UpdateNumber(void)
{
	if (m_pTimeOwn == nullptr)
		return;

	D3DXCOLOR col = m_pTimeOwn->GetColor(CTimer::E_Number::NUMBER_MILLI);

	col += (COL_DEST_NUMBER - col) * SPEED_APPER_TIME;

	m_pTimeOwn->SetColor(CTimer::E_Number::NUMBER_MAX, col);
}

//=====================================================
// 見出しの更新
//=====================================================
void CStateResultDispTime::UpdateCaption(void)
{
	if (m_pCaption == nullptr)
		return;

	m_fCntAnim += SPEED_CAPTION;

	universal::LimitValuefloat(&m_fCntAnim, 1.0f, 0.0f);

	float fRate = universal::EaseOutBack(m_fCntAnim);

	// キャプションの位置を設定
	D3DXVECTOR3 vecDiff = POS_CAPTION_DEST - POS_CAPTION_INITIAL;
	D3DXVECTOR3 pos = POS_CAPTION_INITIAL + vecDiff * fRate;

	CDebugProc::GetInstance()->Print("\nキャプション位置[%f,%f]", m_pCaption->GetPosition().x, m_pCaption->GetPosition().y);

	m_pCaption->SetPosition(pos);
	m_pCaption->SetVtx();
}