//*****************************************************
//
// タイトル処理[title.cpp]
// Author:髙山桃也
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
#include "UI.h"
#include "light.h"

//*****************************************************
// マクロ定義
//*****************************************************

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const D3DXVECTOR3 TITLE_LOGO_POS = D3DXVECTOR3(0.5f, 0.3f, 0.0f);	// タイトルロゴの位置
	const float TITLE_LOGO_WIDTH = 0.2f;	// タイトルロゴの幅
	const float TITLE_LOGO_HEIGHT = 0.18f;	// タイトルロゴの高さ
	const char* TITLE_LOGO_PATH = "data\\TEXTURE\\UI\\title_logo00.png";	// タイトルロゴのパス

	const D3DXVECTOR3 TEAM_LOGO_POS = D3DXVECTOR3(0.9f, 0.9f, 0.0f);	// チームロゴの位置
	float TEAM_LOGO_WIDTH = 0.09f;         // チームロゴの幅
	const float TEAM_LOGO_HEIGHT = 0.1f;	// チームロゴの高さ
	const char* TEAM_LOGO_PATH = "data\\TEXTURE\\UI\\logoTeam.png";	// チームロゴのパス

	const D3DXVECTOR3 STATE_POS = D3DXVECTOR3(0.5f, 0.7f, 0.0f);	// スタート表示の位置
	const float START_WIDTH = 0.3f;	// スタート表示の幅
	const float START_HEIGHT = 0.14f;	// スタート表示の高さ
	const char* START_PATH = "data\\TEXTURE\\UI\\gamestart.png";	// スタート表示のパス
	const float SPEED_AFTER_EXPAND = 0.006f;	    // 残像の膨らむ速度
	const float SPEED_START_AVOID = 0.03f;	    // スタート表示の消える速度
	D3DXVECTOR2 SIZE_MENU = { 200.0f,60.0f };	//　メニューのサイズ
	const D3DXCOLOR COL_INITIAL_MENU = { 0.4f,0.4f,0.4f,1.0f };	// メニュー項目の初期色
	const D3DXCOLOR COL_CURRENT_MENU = { 1.0f,1.0f,1.0f,1.0f };	// メニュー項目の選択色
	const D3DXVECTOR3 POS_BIKE = { 0.0f, 0.0f, 600.51f };	    // バイクモデルの位置

	const float REBOOST_POS_Z = 20000.0f;    // プレイヤーが再び加速するZ座標
	const float PLAYER_MAX_SPEED = 120.0f;   // タイトルでのバイクのスピード上限
	const float FADE_PLAYER_SPEED = 300.0f;  // 画面遷移するプレイヤーの速度

	const D3DXVECTOR3 POS_RIGHT_DOOR = { 590.0f, 1000.0f, 1900.0f };  // ドアの右側の位置
	const D3DXVECTOR3 POS_LEFT_DOOR = { -590.0f, 1000.0f, 1900.0f };  // ドアの左側の位置
	const float RIGHT_DOOR_LIMIT = 1800.0f;  // ドアの右側の可動上限
	const float LEFT_DOOR_LIMIT = -1800.0f;  // ドアの左側の可動上限

	const int NUM_LIGHT = 3;	// ライトの数
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
	m_pDoorFrame = nullptr;
	m_pRightDoor = nullptr;
	m_pLeftDoor = nullptr;
	m_pGarage = nullptr;
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

	// フォグをかける
	CRenderer *pRenderer = CRenderer::GetInstance();

	if (pRenderer != nullptr)
	{
		pRenderer->EnableFog(true);
		pRenderer->SetStart(15000);
		pRenderer->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
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
	m_pTitleLogo = CUI::Create();

	if (m_pTitleLogo != nullptr)
	{
		m_pTitleLogo->SetSize(TITLE_LOGO_WIDTH, TITLE_LOGO_HEIGHT);
		m_pTitleLogo->SetPosition(TITLE_LOGO_POS);
		int nIdx = CTexture::GetInstance()->Regist(TITLE_LOGO_PATH);
		m_pTitleLogo->SetIdxTexture(nIdx);
		m_pTitleLogo->SetVtx();
	}

	// チームロゴの生成
	m_pTeamLogo = CUI::Create();

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
	pInfoCamera->posR = { POS_BIKE.x, 300.0f, POS_BIKE.z };

	Camera::ChangeState(new CCameraStateTitle);

	// 格納庫生成
	m_pGarage = CObjectX::Create();

	if (m_pGarage != nullptr)
	{
		int nIdx = CModel::Load("data\\MODEL\\block\\hangar.x");
		m_pGarage->BindModel(nIdx);
		m_pGarage->SetPosition(D3DXVECTOR3(0.0f, 1000.0f, 0.0f));
		m_pGarage->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}

	// 格納庫のドアフレーム生成
	m_pDoorFrame = CObjectX::Create();

	if (m_pDoorFrame != nullptr)
	{
		int nIdx = CModel::Load("data\\MODEL\\block\\door.x");
		m_pDoorFrame->BindModel(nIdx);
		m_pDoorFrame->SetPosition(D3DXVECTOR3(0.0f, 1000.0f, 2000.0f));
	}

	// 格納庫のドアの右生成
	m_pRightDoor = CObjectX::Create();

	if (m_pRightDoor != nullptr)
	{
		int nIdx = CModel::Load("data\\MODEL\\block\\door01.x");
		m_pRightDoor->BindModel(nIdx);
		m_pRightDoor->SetPosition(POS_RIGHT_DOOR);
	}

	// 格納庫のドアの左生成
	m_pLeftDoor = CObjectX::Create();

	if (m_pLeftDoor != nullptr)
	{
		int nIdx = CModel::Load("data\\MODEL\\block\\door02.x");
		m_pLeftDoor->BindModel(nIdx);
		m_pLeftDoor->SetPosition(POS_LEFT_DOOR);
	}

	// トンネル生成
	int nIdx = CModel::Load("data\\MODEL\\block\\tonnel.x");
	float vtxz = 0.0f;

	for (int i = 0; i < 5; i++)
	{
		CObjectX* pTonnel = CObjectX::Create();

		if (pTonnel != nullptr)
		{
			int nIdx = CModel::Load("data\\MODEL\\block\\tonnel.x");
			pTonnel->BindModel(nIdx);
			pTonnel->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 6000.0f + (i * 8000.0f)));
			pTonnel->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		}
	}

	// バイクモデルの設置
	m_pBike = CMotion::Create("data\\MOTION\\motionEnemy.txt");

	if (m_pBike != nullptr)
	{
		m_pBike->SetPosition(POS_BIKE);
		m_pBike->SetMotion(2); // 待機モーション
		m_pBike->InitPose(2);
		m_pBike->EnableShadow(true);
	}

	// テールランプ生成
	int nIdxTexture = CTexture::GetInstance()->Regist("data\\TEXTURE\\EFFECT\\orbit000.png");
	m_pOrbitLamp = COrbit::Create(m_pBike->GetMatrix(), D3DXVECTOR3(20.0f, 220.0f, -80.0f), D3DXVECTOR3(-20.0f, 220.0f, -80.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 60, nIdxTexture);

	// ライトの生成
	CreateLight();

	return S_OK;
}

//=====================================================
// ライトの生成
//=====================================================
void CTitle::CreateLight(void)
{
	D3DXVECTOR3 aDir[NUM_LIGHT] =
	{
		{ -1.4f, 0.24f, -2.21f, },
		{ 1.42f, -0.8f, 0.08f },
		{ -0.29f, -0.8f, 0.55f }
	};

	for (int i = 0; i < NUM_LIGHT; i++)
	{
		CLight *pLight = CLight::Create();

		if (pLight == nullptr)
			continue;

		D3DLIGHT9 infoLight = pLight->GetLightInfo();

		infoLight.Type = D3DLIGHT_DIRECTIONAL;
		infoLight.Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);

		D3DXVECTOR3 vecDir = aDir[i];
		D3DXVec3Normalize(&vecDir, &vecDir);		//ベクトル正規化
		infoLight.Direction = vecDir;

		pLight->SetLightInfo(infoLight);
	}
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
	D3DXMATRIX mtx = m_pBike->GetParts(19)->pParts->GetMatrix();

	D3DXVECTOR3 pos = { mtx._41, mtx._42, mtx._43 };

	float fSpeed = m_pBike->GetMove().z;

	if (fSpeed > PLAYER_MAX_SPEED * 0.4f)
		CParticle::Create(pos, CParticle::TYPE::TYPE_RUN);

	D3DXMATRIX mtxNinja = m_pBike->GetParts(0)->pParts->GetMatrix();
	mtxNinja._42 = mtxNinja._42 - 240.0f;
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
}

//=====================================================
// 格納庫のドアが開く処理
//=====================================================
void CTitle::DoorOpen(void)
{
	if (m_pRightDoor == nullptr)
		return;

	if (m_pLeftDoor == nullptr)
		return;

	// サウンドインスタンスの取得
	CSound* pSound = CSound::GetInstance();

	if (pSound == nullptr)
		return;

	D3DXVECTOR3 RightDoorPos = m_pRightDoor->GetPosition();

	if(RightDoorPos.x < RIGHT_DOOR_LIMIT)
	   RightDoorPos.x += 10.0f;

	// ドアの位置設定
	m_pRightDoor->SetPosition(RightDoorPos);

	D3DXVECTOR3 LeftDoorPos = m_pLeftDoor->GetPosition();

	if (LeftDoorPos.x > LEFT_DOOR_LIMIT)
	    LeftDoorPos.x -= 10.0f;

	// ドアの位置設定
	m_pLeftDoor->SetPosition(LeftDoorPos);

	if (RightDoorPos.x == 1600 && LeftDoorPos.x == -1600)
		pSound->Play(pSound->LABEL_SE_ENGINE_START);

	if (RightDoorPos.x == RIGHT_DOOR_LIMIT && LeftDoorPos.x == LEFT_DOOR_LIMIT)
	{// ドアの位置が一定の値に達したら

		if (m_pBike->GetMotion() != 3)
			m_pBike->SetMotion(3); // スタートモーション
	}
	
	CDebugProc::GetInstance()->Print("\nドアの右 [%f, %f, %f]", m_pRightDoor->GetPosition().x, m_pRightDoor->GetPosition().y, m_pRightDoor->GetPosition().z);
	CDebugProc::GetInstance()->Print("\nドアの左 [%f, %f, %f]", m_pLeftDoor->GetPosition().x, m_pLeftDoor->GetPosition().y, m_pLeftDoor->GetPosition().z);
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
	m_pStart = CUI::Create();

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
			// サウンドインスタンスの取得
			CSound* pSound = CSound::GetInstance();

			if (pSound != nullptr)
				pSound->Play(pSound->LABEL_SE_GAME_START);

			// 残像の生成
			m_pAfter = CUI::Create();

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
		float fWidth = m_pAfter->GetSize().x;
		float fHeight = m_pAfter->GetSize().y;

		fWidth += SPEED_AFTER_EXPAND;
		fHeight += SPEED_AFTER_EXPAND;

		CDebugProc::GetInstance()->Print("\n幅幅幅幅幅幅幅幅幅幅幅幅幅幅[%f]", fHeight);

		m_pAfter->SetSize(fWidth, fHeight);
		m_pAfter->SetVtx();

		// 色の変更
		D3DXCOLOR col = m_pAfter->GetCol();

		col.a -= SPEED_START_AVOID;

		if (col.a <= 0.0f)
		{
			col.a = 0.0f;

			pTitle->ChangeBehavior(new CTitleBehindPlayer);

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

		m_apMenu[i] = CUI::Create();

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

	if (m_IsGameStarted)
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
	{
		m_IsGameStarted = true;
	}
}

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

	CMotion* pBike = pTItle->GetBike();

	if (pBike == nullptr)
		return;

	// 格納庫のドアが開く
	pTItle->DoorOpen();

	// カメラ位置の設定
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
		return;

	CCamera::Camera* pInfoCamera = pCamera->GetCamera();

	D3DXVECTOR3 BikePos = pBike->GetPosition();

	// モーションが終了していたらバイクの前進させる
	if (pBike->IsFinish())
		pTItle->ChangeBehavior(new CTitlePlayerAcceleration);
		
}

CTitlePlayerAcceleration::CTitlePlayerAcceleration()
{// コンストラクタ

	
}

CTitlePlayerAcceleration::~CTitlePlayerAcceleration()
{// デストラクタ

}

void CTitlePlayerAcceleration::Update(CTitle* pTItle)
{// 更新処理

	CMotion* pBike = pTItle->GetBike();

	if (pBike == nullptr)
		return;

	float fSpeed = pBike->GetMove().z;

	fSpeed = (fSpeed + 0.03f) * 1.1f;

	pBike->SetMove({ 0.0f, 0.0f, fSpeed });

	// プレイヤーが加速する
	pTItle->PlayerAcceleration();

	// スピードが一定値に達したら加速をやめる
	if (fSpeed >= PLAYER_MAX_SPEED)
		pTItle->ChangeBehavior(new CTitleMovePlayer);
}

CTitleMovePlayer::CTitleMovePlayer()
{// コンストラクタ

	Camera::ChangeState(nullptr);

	// サウンドインスタンスの取得
	CSound* pSound = CSound::GetInstance();

	if (pSound == nullptr)
		return;

	pSound->Stop(pSound->LABEL_SE_ENGINE_START);
	pSound->Play(pSound->LABEL_SE_BIKE_ACCELERATION);
}

CTitleMovePlayer::~CTitleMovePlayer()
{// デストラクタ

}

void CTitleMovePlayer::Update(CTitle* pTItle)
{// 更新処理

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
		pTItle->ChangeBehavior(new CTitleFade);
		

	CDebugProc::GetInstance()->Print("\nプレイヤーの位置 [%f, %f, %f]", pos.x, pos.y, pos.z);
	CDebugProc::GetInstance()->Print("\n注視点 [%f, %f, %f]", pInfoCamera->posR.x, pInfoCamera->posR.y, pInfoCamera->posR.z);
	CDebugProc::GetInstance()->Print("\n注視点目的 [%f, %f, %f]", pInfoCamera->posRDest.x, pInfoCamera->posRDest.y, pInfoCamera->posRDest.z);
}

CTitleFade::CTitleFade()
{// コンストラクタ
	
	Camera::ChangeState(nullptr);
}

CTitleFade::~CTitleFade()
{// デストラクタ

}

void CTitleFade::Update(CTitle* pTItle)
{// 更新処理
	
	CMotion* pBike = pTItle->GetBike();

	if (pBike == nullptr)
		return;

	float fSpeed = pBike->GetMove().z;

	fSpeed = (fSpeed + 0.03f) * 1.1f;

	pBike->SetMove({ 0.0f, 0.0f, fSpeed });

	// プレイヤーが加速する
	pTItle->PlayerAcceleration();

	// サウンドインスタンスの取得
	CSound* pSound = CSound::GetInstance();

	if (pSound == nullptr)
		return;

	if (pSound != nullptr)
	{
		if (m_fVolume >= 0.0f)
		    m_fVolume -= 0.04f;

		pSound->SetVolume(pSound->LABEL_SE_BIKE_ACCELERATION, m_fVolume);
	}

	// プレイヤーの速度が一定値に達したら遷移する
	if (fSpeed >= FADE_PLAYER_SPEED)
		Fade();

	CDebugProc::GetInstance()->Print("\nSEの音量:%f", m_fVolume);
}

void CTitleFade::Fade(void)
{// フェード処理

	CFade* pFade = CFade::GetInstance();

	if (pFade == nullptr)
		return;

	if (pFade->GetState() != CFade::FADE_NONE)
		return;

	pFade->SetFade(CScene::MODE_GAME);
}