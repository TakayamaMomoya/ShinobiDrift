//*****************************************************
//
// タイトル処理[title.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "title.h"
#include "object.h"
#include "inputManager.h"
#include "manager.h"
#include "fade.h"
#include "texture.h"
#include "camera.h"
#include "CameraState.h"
#include "renderer.h"
#include "sound.h"
#include "polygon3D.h"
#include "objectX.h"
#include "skybox.h"
#include "player.h"
#include "smoke.h"
#include "meshcylinder.h"
#include "fan3D.h"
#include "meshfield.h"
#include "particle.h"
#include "orbit.h"
#include "debugproc.h"

//*****************************************************
// マクロ定義
//*****************************************************

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const D3DXVECTOR3 TITLE_LOGO_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 200.0f, 0.0f);	// タイトルロゴの位置
	const float TITLE_LOGO_WIDTH = 875.0f * 0.35f;	// タイトルロゴの幅
	const float TITLE_LOGO_HEIGHT = 320.0f * 0.35f;	// タイトルロゴの高さ
	const char* TITLE_LOGO_PATH = "data\\TEXTURE\\UI\\title_logo00.png";	// タイトルロゴのパス

	const D3DXVECTOR3 TEAM_LOGO_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.9f, 75.0f, 0.0f);	// チームロゴの位置
	float TEAM_LOGO_WIDTH = 100.0f;         // チームロゴの幅
	const float TEAM_LOGO_HEIGHT = 35.0f;	// チームロゴの高さ
	const char* TEAM_LOGO_PATH = "data\\TEXTURE\\UI\\logoTeam.png";	// チームロゴのパス

	const D3DXVECTOR3 STATE_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.7f, 0.0f);	// スタート表示の位置
	const float START_WIDTH = 400.0f;	// スタート表示の幅
	const float START_HEIGHT = 100.0f;	// スタート表示の高さ
	const char* START_PATH = "data\\TEXTURE\\UI\\gamestart.png";	// スタート表示のパス
	const float SPEED_AFTER_EXPAND = 2.0f;	// 残像の膨らむ速度
	const float SPEED_START_AVOID = 0.03f;	// スタート表示の消える速度
	D3DXVECTOR2 SIZE_MENU = { 200.0f,60.0f };	//　メニューのサイズ
	const D3DXCOLOR COL_INITIAL_MENU = { 0.4f,0.4f,0.4f,1.0f };	// メニュー項目の初期色
	const D3DXCOLOR COL_CURRENT_MENU = { 1.0f,1.0f,1.0f,1.0f };	// メニュー項目の選択色
	const D3DXVECTOR3 POS_PLAYER = { -154.31f, 130.62f, 570.51f };	// プレイヤーモデルの位置
	const D3DXVECTOR3 POS_BIKE = { -154.31f, 82.62f, 600.51f };	    // バイクモデルの位置

	const float REBOOST_POS_Z = 20000.0f;  // プレイヤーが再び加速するZ座標
	const float MAX_SPEED = 120.0f;        // タイトルでのバイクのスピード上限
}

//*****************************************************
// 静的メンバ変数
//*****************************************************
CMotion* CTitle::m_pBike = nullptr;
CMotion* CTitle::m_pPlayer = nullptr;

//=====================================================
// コンストラクタ
//=====================================================
CTitle::CTitle()
{
	m_state = STATE_NONE;
	m_pTitleLogo = nullptr;
	m_pTeamLogo = nullptr;
	m_pPlayer = nullptr;
	m_pBehavior = nullptr;
	m_pOrbitLamp = nullptr;
	m_fTImerSmoke = 0.0f;
}

//=====================================================
// デストラクタ
//=====================================================
CTitle::~CTitle()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CTitle::Init(void)
{
	ChangeBehavior(new CTitleStart);

	// フォグをかけない
	CRenderer *pRenderer = CRenderer::GetInstance();

	if (pRenderer != nullptr)
	{
		pRenderer->EnableFog(false);
	}

	// サウンドインスタンスの取得
	CSound* pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		// BGMの再生
		pSound->Play(pSound->LABEL_BGM_TITLE);
	}
	else if (pSound == nullptr)
	{
		return E_FAIL;
	}

	// タイトルロゴの生成
	m_pTitleLogo = CPolygon2D::Create(7);

	if (m_pTitleLogo != nullptr)
	{
		m_pTitleLogo->SetSize(TITLE_LOGO_WIDTH, TITLE_LOGO_HEIGHT);
		m_pTitleLogo->SetPosition(TITLE_LOGO_POS);
		int nIdx = CTexture::GetInstance()->Regist(TITLE_LOGO_PATH);
		m_pTitleLogo->SetIdxTexture(nIdx);
		m_pTitleLogo->SetVtx();
	}

	// チームロゴの生成
	m_pTeamLogo = CPolygon2D::Create(7);

	if (m_pTeamLogo != nullptr)
	{
		m_pTeamLogo->SetSize(TEAM_LOGO_WIDTH, TEAM_LOGO_HEIGHT);
		m_pTeamLogo->SetPosition(TEAM_LOGO_POS);
		int nIdx = CTexture::GetInstance()->Regist(TEAM_LOGO_PATH);
		m_pTeamLogo->SetIdxTexture(nIdx);
		m_pTeamLogo->SetVtx();
	}

	// カメラ位置の設定
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
		return E_FAIL;

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();

	pInfoCamera->posV = { 45.38f, 500.0f, 270.10f };
	pInfoCamera->posR = { POS_PLAYER.x, 300.0f, POS_PLAYER.z };

	Camera::ChangeState(new CCameraStateTitle);

	//// 背景オブジェクトの生成
	//CObjectX* pArsenal = CObjectX::Create();

	//if (pArsenal != nullptr)
	//{
	//	int nIdx = CModel::Load("data\\MODEL\\other\\arsenal.x");
	//	pArsenal->BindModel(nIdx);
	//}

	CMeshCylinder *pCylinder = CMeshCylinder::Create(32, 1000);

	if (pCylinder != nullptr)
	{
		pCylinder->SetPosition(D3DXVECTOR3(0.0f, -200.0f, 3000.0f));
		pCylinder->SetRotation(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
		pCylinder->SetRadius(2000.0f);
		pCylinder->SetVtx();
		pCylinder->SetIdxTexture(Texture::GetIdx("data\\TEXTURE\\MATERIAL\\concrete.jpg"));
	}

	m_pFan3D = CFan3D::Create();

	if (m_pFan3D != nullptr)
	{
		m_pFan3D->SetPosition(D3DXVECTOR3(0.0f, -200.0f, 3000.0f));
		m_pFan3D->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pFan3D->SetRadius(2000.0f);
		m_pFan3D->SetVtx();
		m_pFan3D->SetIdxTexture(Texture::GetIdx("data\\TEXTURE\\MATERIAL\\potal00.png"));
	}

	CMeshField *pField = CMeshField::Create();

	if (pField != nullptr)
	{
		pField->SetPosition(D3DXVECTOR3(0.0f, -800.0f, 0.0f));
	}

	// バイクモデルの設置
	m_pBike = CMotion::Create("data\\MOTION\\motionBike.txt");

	if (m_pBike != nullptr)
	{
		m_pBike->SetPosition(POS_BIKE);
		m_pBike->SetMotion(CPlayer::MOTION::MOTION_NEUTRAL);
	}

	// プレイヤーモデルの設置
	m_pPlayer = CMotion::Create("data\\MOTION\\motionPlayer.txt");

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->SetPosition(POS_PLAYER);
		m_pPlayer->SetMotion(CPlayer::MOTION::MOTION_NEUTRAL);
		m_pPlayer->InitPose(CPlayer::MOTION::MOTION_NEUTRAL);
		m_pPlayer->SetMatrix(m_pBike->GetMatrix());
	}

	// テールランプ生成
	m_pOrbitLamp = COrbit::Create(m_pPlayer->GetMatrix(), D3DXVECTOR3(20.0f, 220.0f, -80.0f), D3DXVECTOR3(-20.0f, 220.0f, -80.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 60,-1);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CTitle::Uninit(void)
{
	Object::DeleteObject((CObject**)&m_pTitleLogo);
	Object::DeleteObject((CObject**)&m_pTeamLogo);

	if (m_pBehavior != nullptr)
	{
		delete m_pBehavior;
		m_pBehavior = nullptr;
	}

	// オブジェクト全破棄
	CObject::ReleaseAll();
}

//=====================================================
// 更新処理
//=====================================================
void CTitle::Update(void)
{
	// シーンの更新
	CScene::Update();

	if (m_pBehavior != nullptr)
	{
		m_pBehavior->Update(this);
	}

	m_pBike->MultiplyMtx(false);
	D3DXMATRIX mtx = m_pBike->GetParts(3)->pParts->GetMatrix();

	D3DXVECTOR3 pos = { mtx._41, mtx._42, mtx._43 };

	float fSpeed = m_pBike->GetMove().z;

	if (fSpeed > MAX_SPEED * 0.4f)
		CParticle::Create(pos, CParticle::TYPE::TYPE_RUN);

	D3DXMATRIX mtxNinja = m_pBike->GetParts(3)->pParts->GetMatrix();
	mtxNinja._42 = mtxNinja._42 - 100.0f;
	mtxNinja._43 = mtxNinja._43 + 100.0f;
	
	m_pOrbitLamp->SetOffset(mtxNinja, D3DXCOLOR(1.0f, 0.15f, 0.0f, 1.0f));
		
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
		return;

	// カメラの更新
	pCamera->Update();
}

//=====================================================
// 描画処理
//=====================================================
void CTitle::Draw(void)
{
	
}

//=====================================================
// ビヘイビアの変更
//=====================================================
void CTitle::ChangeBehavior(CTitleBehavior *pBehavior)
{
	if (m_pBehavior != nullptr)
	{
		delete m_pBehavior;
	}

	m_pBehavior = pBehavior;
}

//=====================================================
// プレイヤーが加速する処理
//=====================================================
void CTitle::PlayerAcceleration(void)
{
	D3DXVECTOR3 BikePos = m_pBike->GetPosition();

	float fSpeed = m_pBike->GetMove().z;

	BikePos.z += fSpeed;

	// バイクの位置設定
	m_pBike->SetPosition(BikePos);

	// バイクに乗った忍者の追従
	m_pPlayer->SetPosition(D3DXVECTOR3(0.0f, 50.0f, -10.0f));
	m_pBike->MultiplyMtx(false);
	m_pPlayer->SetMatrixParent(m_pBike->GetMatrix());
}

//=====================================================================
// Behavior
//=====================================================================
//=====================================================
// 基底Behavior
//=====================================================
CTitleBehavior::CTitleBehavior()
{// コンストラクタ

}

CTitleBehavior::~CTitleBehavior()
{// デストラクタ

}

//=====================================================
// スタート表示状態
//=====================================================
CTitleStart::CTitleStart()
{// コンストラクタ
	m_pStart = nullptr;
	m_pAfter = nullptr;

	// スタート表示の生成
	m_pStart = CPolygon2D::Create(7);

	if (m_pStart != nullptr)
	{
		m_pStart->SetSize(START_WIDTH, START_HEIGHT);
		m_pStart->SetPosition(STATE_POS);
		int nIdx = CTexture::GetInstance()->Regist(START_PATH);
		m_pStart->SetIdxTexture(nIdx);
		m_pStart->SetVtx();
	}
}

CTitleStart::~CTitleStart()
{// デストラクタ
	Object::DeleteObject((CObject**)&m_pStart);
	Object::DeleteObject((CObject**)&m_pAfter);
}

void CTitleStart::Update(CTitle *pTitle)
{// 更新
	if (m_pAfter == nullptr)
	{
		CInputManager *pInput = CInputManager::GetInstance();

		if (pInput == nullptr)
			return;

		if (pInput->GetTrigger(CInputManager::BUTTON_ENTER))
		{
			// 残像の生成
			m_pAfter = CPolygon2D::Create(6);

			if (m_pAfter != nullptr)
			{
				m_pAfter->SetSize(START_WIDTH, START_HEIGHT);
				m_pAfter->SetPosition(STATE_POS);
				int nIdx = CTexture::GetInstance()->Regist(START_PATH);
				m_pAfter->SetIdxTexture(nIdx);
				m_pAfter->SetVtx();
			}
		}
	}
	else
	{
		// サイズの変更
		float fWidth = m_pAfter->GetWidth();
		float fHeight = m_pAfter->GetHeight();

		fWidth += SPEED_AFTER_EXPAND;
		fHeight += SPEED_AFTER_EXPAND;

		m_pAfter->SetSize(fWidth, fHeight);
		m_pAfter->SetVtx();

		// 色の変更
		D3DXCOLOR col = m_pAfter->GetCol();

		col.a -= SPEED_START_AVOID;

		if (col.a <= 0.0f)
		{
			col.a = 0.0f;

			pTitle->ChangeBehavior(new CTitleMenu);

			return;
		}

		if (m_pStart != nullptr)
		{
			m_pStart->SetCol(col);
		}

		m_pAfter->SetCol(col);
	}
}

//=====================================================
// スタート表示状態
//=====================================================
CTitleMenu::CTitleMenu()
{// コンストラクタ
	const char* aPath[MENU_MAX] =
	{// メニューのテクスチャパス
		"data\\TEXTURE\\UI\\menu00.png",
		"data\\TEXTURE\\UI\\menu01.png",
	};

	ZeroMemory(&m_apMenu[0], sizeof(m_apMenu));
	m_menu = MENU_GAME;
	m_pCursor = nullptr;

	for (int i = 0; i < MENU_MAX; i++)
	{
		int nCnt = i - 1;

		m_apMenu[i] = CPolygon2D::Create(6);

		if (m_apMenu[i] != nullptr)
		{
			D3DXVECTOR3 pos = SCRN_MID;
			pos.x = SIZE_MENU.x + 20.0f;
			pos.y += SIZE_MENU.y * i * 2 + 40.0f;

			m_apMenu[i]->SetPosition(pos);
			m_apMenu[i]->SetSize(SIZE_MENU.x, SIZE_MENU.y);
			m_apMenu[i]->SetCol(COL_INITIAL_MENU);
			m_apMenu[i]->SetVtx();

			int nIdx = CTexture::GetInstance()->Regist(aPath[i]);
			m_apMenu[i]->SetIdxTexture(nIdx);
		}
	}

	//// カーソルの生成
	//m_pCursor = CPolygon2D::Create(6);

	//if (m_pCursor != nullptr)
	//{
	//	m_pCursor->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	//	m_pCursor->SetVtx();

	//	int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\cursorMenu.png");
	//	m_pCursor->SetIdxTexture(nIdx);
	//}
}

CTitleMenu::~CTitleMenu()
{// デストラクタ
	Object::DeleteObject((CObject**)&m_apMenu, MENU_MAX);
}

void CTitleMenu::Update(CTitle *pTitle)
{// 更新
	// 入力
	Input();

	// カーソルの制御
	ManageCursor();

	// 色の管理
	for (int i = 0; i < MENU_MAX; i++)
	{
		if (m_apMenu[i] != nullptr)
		{
			D3DXCOLOR colDest = COL_INITIAL_MENU;

			if (i == m_menu)
			{
				colDest = COL_CURRENT_MENU;
			}

			D3DXCOLOR col = m_apMenu[i]->GetCol();

			col += (colDest - col) * 0.3f;

			m_apMenu[i]->SetCol(col);
		}
	}

	if (m_bFade)
		pTitle->ChangeBehavior(new CTitleBehindPlayer);
}

void CTitleMenu::Input(void)
{// 入力
	CInputManager *pInput = CInputManager::GetInstance();

	if (pInput == nullptr)
		return;

	// 項目選択
	if (pInput->GetTrigger(CInputManager::BUTTON_AXIS_UP))
	{
		Sound::Play(CSound::LABEL_SE_PAUSE_ARROW);

		m_menu = (MENU)((m_menu + MENU_MAX - 1) % MENU_MAX);
	}
	else if (pInput->GetTrigger(CInputManager::BUTTON_AXIS_DOWN))
	{
		Sound::Play(CSound::LABEL_SE_PAUSE_ARROW);

		m_menu = (MENU)((m_menu + 1) % MENU_MAX);
	}

	if (pInput->GetTrigger(CInputManager::BUTTON_ENTER))
	{// フェード処理
		//Fade();

		m_bFade = true;
	}
}

//void CTitleMenu::Fade(void)
//{// 各種フェード
//	CFade *pFade = CFade::GetInstance();
//
//	if (pFade == nullptr)
//		return;
//
//	if (pFade->GetState() != CFade::FADE_NONE)
//		return;
//
//	switch (m_menu)
//	{
//	case CTitleMenu::MENU_GAME:
//
//		//pFade->SetFade(CScene::MODE_GAME);
//		m_bFade = true;
//		break;
//	default:
//		break;
//	}
//}

void CTitleMenu::ManageCursor(void)
{// カーソルの制御
	if (m_pCursor == nullptr)
		return;

	D3DXVECTOR3 pos = m_pCursor->GetPosition();
	D3DXVECTOR3 posDest;

	posDest = SCRN_MID;
	posDest.x = 20.0f;
	posDest.y += SIZE_MENU.y * m_menu * 2 + SIZE_MENU.y * 1.5f;

	pos += (posDest - pos) * 0.4f;

	m_pCursor->SetPosition(pos);
	m_pCursor->SetVtx();
}

CTitleBehindPlayer::CTitleBehindPlayer()
{// コンストラクタ

	Camera::ChangeState(new CCameraStateFollowPlayerTitle);
}

CTitleBehindPlayer::~CTitleBehindPlayer()
{// デストラクタ

}

void CTitleBehindPlayer::Update(CTitle* pTItle)
{// 更新処理

	CMotion* pNinja = pTItle->GetPlayer();

	if (pNinja == nullptr)
		return;

	CMotion* pBike = pTItle->GetBike();

	if (pBike == nullptr)
		return;

	if(pNinja->GetMotion() != CPlayer::MOTION_NINJA_SLASHDOWN)
	   pNinja->SetMotion(CPlayer::MOTION_NINJA_SLASHDOWN);

	// カメラ位置の設定
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
		return;

	CCamera::Camera* pInfoCamera = pCamera->GetCamera();

	D3DXVECTOR3 BikePos = pBike->GetPosition();

	// モーションが終了していたらバイクの前進させる
	if (pNinja->IsFinish())
		pTItle->ChangeBehavior(new CTitlePlayerAcceleration);
}

CTitlePlayerAcceleration::CTitlePlayerAcceleration()
{// コンストラクタ

	Camera::ChangeState(new CCameraStateFollowPlayerTitle);
}

CTitlePlayerAcceleration::~CTitlePlayerAcceleration()
{// デストラクタ

}

void CTitlePlayerAcceleration::Update(CTitle* pTItle)
{// 更新処理

	CMotion* pNinja = pTItle->GetPlayer();

	if (pNinja == nullptr)
		return;

	CMotion* pBike = pTItle->GetBike();

	if (pBike == nullptr)
		return;

	float fSpeed = pBike->GetMove().z;

	fSpeed = (fSpeed + 0.03f) * 1.1f;

	pBike->SetMove({ 0.0f, 0.0f, fSpeed });

	// プレイヤーが加速する
	pTItle->PlayerAcceleration();

	if (fSpeed >= MAX_SPEED)
		pTItle->ChangeBehavior(new CTitleMovePlayer);
}

CTitleMovePlayer::CTitleMovePlayer()
{// コンストラクタ

	Camera::ChangeState(nullptr);
}

CTitleMovePlayer::~CTitleMovePlayer()
{// デストラクタ

}

void CTitleMovePlayer::Update(CTitle* pTItle)
{// 更新処理

	CMotion* pNinja = pTItle->GetPlayer();

	if (pNinja == nullptr)
		return;

	CMotion* pBike = pTItle->GetBike();

	if (pBike == nullptr)
		return;

	// プレイヤーが加速する
	pTItle->PlayerAcceleration();

	// カメラ位置の設定
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
		return;

	D3DXVECTOR3 pos = pBike->GetMtxPos(0);

	CCamera::Camera* pInfoCamera = pCamera->GetCamera();

	pInfoCamera->rot.y += 0.04f;

	universal::LimitRot(&pInfoCamera->rot.y);

	D3DXMATRIX* pMtx = &pBike->GetMatrix();

	D3DXVECTOR3 vecAddPosR = { pMtx->_31, pMtx->_32, pMtx->_33 };

	pInfoCamera->posRDest = pos + vecAddPosR;

	pInfoCamera->posRDest.y += 50.0f;	// 一旦むりやりちょっと高くする

	pInfoCamera->posR = pInfoCamera->posRDest;

	// 目標の視点設定
	D3DXVECTOR3 vecPole = universal::PolarCoordinates(pInfoCamera->rot);
	pInfoCamera->posVDest = pos + vecPole * pInfoCamera->fLength;

	pCamera->SetPosV();

	pCamera->MoveDist(0.2f);

	float BikePosZ = pBike->GetPosition().z;

	if (BikePosZ >= REBOOST_POS_Z)
		pTItle->ChangeBehavior(new CTitleFadePlayer);

	CDebugProc::GetInstance()->Print("\nプレイヤーの位置 [%f, %f, %f]", pos.x, pos.y, pos.z);
	CDebugProc::GetInstance()->Print("\n注視点 [%f, %f, %f]", pInfoCamera->posR.x, pInfoCamera->posR.y, pInfoCamera->posR.z);
	CDebugProc::GetInstance()->Print("\n注視点目的 [%f, %f, %f]", pInfoCamera->posRDest.x, pInfoCamera->posRDest.y, pInfoCamera->posRDest.z);
}

CTitleFadePlayer::CTitleFadePlayer()
{// コンストラクタ
	
	Camera::ChangeState(nullptr);
}

CTitleFadePlayer::~CTitleFadePlayer()
{// デストラクタ

}

void CTitleFadePlayer::Update(CTitle* pTItle)
{// 更新処理
	
	CMotion* pNinja = pTItle->GetPlayer();

	if (pNinja == nullptr)
		return;

	CMotion* pBike = pTItle->GetBike();

	if (pBike == nullptr)
		return;

	float fSpeed = pBike->GetMove().z;

	fSpeed = (fSpeed + 0.03f) * 1.1f;

	pBike->SetMove({ 0.0f, 0.0f, fSpeed });

	// プレイヤーが加速する
	pTItle->PlayerAcceleration();

	if (fSpeed >= 300.0f)
		Fade();
}

void CTitleFadePlayer::Fade(void)
{// フェード処理

	CFade* pFade = CFade::GetInstance();

	if (pFade == nullptr)
		return;

	if (pFade->GetState() != CFade::FADE_NONE)
		return;

	pFade->SetFade(CScene::MODE_GAME);
}