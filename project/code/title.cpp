//*****************************************************
//
// �^�C�g������[title.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
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
// �}�N����`
//*****************************************************

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const D3DXVECTOR3 TITLE_LOGO_POS = D3DXVECTOR3(0.5f, 0.3f, 0.0f);	// �^�C�g�����S�̈ʒu
	const float TITLE_LOGO_WIDTH = 0.2f;	// �^�C�g�����S�̕�
	const float TITLE_LOGO_HEIGHT = 0.18f;	// �^�C�g�����S�̍���
	const char* TITLE_LOGO_PATH = "data\\TEXTURE\\UI\\title_logo00.png";	// �^�C�g�����S�̃p�X

	const D3DXVECTOR3 TEAM_LOGO_POS = D3DXVECTOR3(0.9f, 0.9f, 0.0f);	// �`�[�����S�̈ʒu
	float TEAM_LOGO_WIDTH = 0.09f;         // �`�[�����S�̕�
	const float TEAM_LOGO_HEIGHT = 0.1f;	// �`�[�����S�̍���
	const char* TEAM_LOGO_PATH = "data\\TEXTURE\\UI\\logoTeam.png";	// �`�[�����S�̃p�X

	const D3DXVECTOR3 STATE_POS = D3DXVECTOR3(0.5f, 0.7f, 0.0f);	// �X�^�[�g�\���̈ʒu
	const float START_WIDTH = 0.3f;	// �X�^�[�g�\���̕�
	const float START_HEIGHT = 0.14f;	// �X�^�[�g�\���̍���
	const char* START_PATH = "data\\TEXTURE\\UI\\gamestart.png";	// �X�^�[�g�\���̃p�X
	const float SPEED_AFTER_EXPAND = 0.006f;	    // �c���̖c��ޑ��x
	const float SPEED_START_AVOID = 0.03f;	    // �X�^�[�g�\���̏����鑬�x
	D3DXVECTOR2 SIZE_MENU = { 200.0f,60.0f };	//�@���j���[�̃T�C�Y
	const D3DXCOLOR COL_INITIAL_MENU = { 0.4f,0.4f,0.4f,1.0f };	// ���j���[���ڂ̏����F
	const D3DXCOLOR COL_CURRENT_MENU = { 1.0f,1.0f,1.0f,1.0f };	// ���j���[���ڂ̑I��F
	const D3DXVECTOR3 POS_BIKE = { 0.0f, 0.0f, 600.51f };	    // �o�C�N���f���̈ʒu

	const float REBOOST_POS_Z = 20000.0f;    // �v���C���[���Ăщ�������Z���W
	const float PLAYER_MAX_SPEED = 120.0f;   // �^�C�g���ł̃o�C�N�̃X�s�[�h���
	const float FADE_PLAYER_SPEED = 300.0f;  // ��ʑJ�ڂ���v���C���[�̑��x

	const D3DXVECTOR3 POS_RIGHT_DOOR = { 590.0f, 1000.0f, 1900.0f };  // �h�A�̉E���̈ʒu
	const D3DXVECTOR3 POS_LEFT_DOOR = { -590.0f, 1000.0f, 1900.0f };  // �h�A�̍����̈ʒu
	const float RIGHT_DOOR_LIMIT = 1800.0f;  // �h�A�̉E���̉����
	const float LEFT_DOOR_LIMIT = -1800.0f;  // �h�A�̍����̉����

	const int NUM_LIGHT = 3;	// ���C�g�̐�
}

//*****************************************************
// �ÓI�����o�ϐ�
//*****************************************************
CMotion* CTitle::m_pBike = nullptr;
CMotion* CTitle::m_pPlayer = nullptr;

//=====================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//=====================================================
CTitle::~CTitle()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CTitle::Init(void)
{
	ChangeBehavior(new CTitleStart);

	// �t�H�O��������
	CRenderer *pRenderer = CRenderer::GetInstance();

	if (pRenderer != nullptr)
	{
		pRenderer->EnableFog(true);
		pRenderer->SetStart(15000);
		pRenderer->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}

	// �T�E���h�C���X�^���X�̎擾
	CSound* pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		// BGM�̍Đ�
		pSound->Play(pSound->LABEL_BGM_TITLE);
	}
	else if (pSound == nullptr)
	{
		return E_FAIL;
	}

	// �^�C�g�����S�̐���
	m_pTitleLogo = CUI::Create();

	if (m_pTitleLogo != nullptr)
	{
		m_pTitleLogo->SetSize(TITLE_LOGO_WIDTH, TITLE_LOGO_HEIGHT);
		m_pTitleLogo->SetPosition(TITLE_LOGO_POS);
		int nIdx = CTexture::GetInstance()->Regist(TITLE_LOGO_PATH);
		m_pTitleLogo->SetIdxTexture(nIdx);
		m_pTitleLogo->SetVtx();
	}

	// �`�[�����S�̐���
	m_pTeamLogo = CUI::Create();

	if (m_pTeamLogo != nullptr)
	{
		m_pTeamLogo->SetSize(TEAM_LOGO_WIDTH, TEAM_LOGO_HEIGHT);
		m_pTeamLogo->SetPosition(TEAM_LOGO_POS);
		int nIdx = CTexture::GetInstance()->Regist(TEAM_LOGO_PATH);
		m_pTeamLogo->SetIdxTexture(nIdx);
		m_pTeamLogo->SetVtx();
	}

	// �J�����ʒu�̐ݒ�
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
		return E_FAIL;

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();

	pInfoCamera->posV = { 45.38f, 500.0f, 270.10f };
	pInfoCamera->posR = { POS_BIKE.x, 300.0f, POS_BIKE.z };

	Camera::ChangeState(new CCameraStateTitle);

	// �i�[�ɐ���
	m_pGarage = CObjectX::Create();

	if (m_pGarage != nullptr)
	{
		int nIdx = CModel::Load("data\\MODEL\\block\\hangar.x");
		m_pGarage->BindModel(nIdx);
		m_pGarage->SetPosition(D3DXVECTOR3(0.0f, 1000.0f, 0.0f));
		m_pGarage->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}

	// �i�[�ɂ̃h�A�t���[������
	m_pDoorFrame = CObjectX::Create();

	if (m_pDoorFrame != nullptr)
	{
		int nIdx = CModel::Load("data\\MODEL\\block\\door.x");
		m_pDoorFrame->BindModel(nIdx);
		m_pDoorFrame->SetPosition(D3DXVECTOR3(0.0f, 1000.0f, 2000.0f));
	}

	// �i�[�ɂ̃h�A�̉E����
	m_pRightDoor = CObjectX::Create();

	if (m_pRightDoor != nullptr)
	{
		int nIdx = CModel::Load("data\\MODEL\\block\\door01.x");
		m_pRightDoor->BindModel(nIdx);
		m_pRightDoor->SetPosition(POS_RIGHT_DOOR);
	}

	// �i�[�ɂ̃h�A�̍�����
	m_pLeftDoor = CObjectX::Create();

	if (m_pLeftDoor != nullptr)
	{
		int nIdx = CModel::Load("data\\MODEL\\block\\door02.x");
		m_pLeftDoor->BindModel(nIdx);
		m_pLeftDoor->SetPosition(POS_LEFT_DOOR);
	}

	// �g���l������
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

	// �o�C�N���f���̐ݒu
	m_pBike = CMotion::Create("data\\MOTION\\motionEnemy.txt");

	if (m_pBike != nullptr)
	{
		m_pBike->SetPosition(POS_BIKE);
		m_pBike->SetMotion(2); // �ҋ@���[�V����
		m_pBike->InitPose(2);
		m_pBike->EnableShadow(true);
	}

	// �e�[�������v����
	int nIdxTexture = CTexture::GetInstance()->Regist("data\\TEXTURE\\EFFECT\\orbit000.png");
	m_pOrbitLamp = COrbit::Create(m_pBike->GetMatrix(), D3DXVECTOR3(20.0f, 220.0f, -80.0f), D3DXVECTOR3(-20.0f, 220.0f, -80.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 60, nIdxTexture);

	// ���C�g�̐���
	CreateLight();

	return S_OK;
}

//=====================================================
// ���C�g�̐���
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
		D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g�����K��
		infoLight.Direction = vecDir;

		pLight->SetLightInfo(infoLight);
	}
}

//=====================================================
// �I������
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

	// �I�u�W�F�N�g�S�j��
	CObject::ReleaseAll();
}

//=====================================================
// �X�V����
//=====================================================
void CTitle::Update(void)
{
	// �V�[���̍X�V
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

	// �J�����̍X�V
	pCamera->Update();
}

//=====================================================
// �`�揈��
//=====================================================
void CTitle::Draw(void)
{
	
}

//=====================================================
// �r�w�C�r�A�̕ύX
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
// �v���C���[���������鏈��
//=====================================================
void CTitle::PlayerAcceleration(void)
{
	D3DXVECTOR3 BikePos = m_pBike->GetPosition();

	float fSpeed = m_pBike->GetMove().z;

	BikePos.z += fSpeed;

	// �o�C�N�̈ʒu�ݒ�
	m_pBike->SetPosition(BikePos);
}

//=====================================================
// �i�[�ɂ̃h�A���J������
//=====================================================
void CTitle::DoorOpen(void)
{
	if (m_pRightDoor == nullptr)
		return;

	if (m_pLeftDoor == nullptr)
		return;

	// �T�E���h�C���X�^���X�̎擾
	CSound* pSound = CSound::GetInstance();

	if (pSound == nullptr)
		return;

	D3DXVECTOR3 RightDoorPos = m_pRightDoor->GetPosition();

	if(RightDoorPos.x < RIGHT_DOOR_LIMIT)
	   RightDoorPos.x += 10.0f;

	// �h�A�̈ʒu�ݒ�
	m_pRightDoor->SetPosition(RightDoorPos);

	D3DXVECTOR3 LeftDoorPos = m_pLeftDoor->GetPosition();

	if (LeftDoorPos.x > LEFT_DOOR_LIMIT)
	    LeftDoorPos.x -= 10.0f;

	// �h�A�̈ʒu�ݒ�
	m_pLeftDoor->SetPosition(LeftDoorPos);

	if (RightDoorPos.x == 1600 && LeftDoorPos.x == -1600)
		pSound->Play(pSound->LABEL_SE_ENGINE_START);

	if (RightDoorPos.x == RIGHT_DOOR_LIMIT && LeftDoorPos.x == LEFT_DOOR_LIMIT)
	{// �h�A�̈ʒu�����̒l�ɒB������

		if (m_pBike->GetMotion() != 3)
			m_pBike->SetMotion(3); // �X�^�[�g���[�V����
	}
	
	CDebugProc::GetInstance()->Print("\n�h�A�̉E [%f, %f, %f]", m_pRightDoor->GetPosition().x, m_pRightDoor->GetPosition().y, m_pRightDoor->GetPosition().z);
	CDebugProc::GetInstance()->Print("\n�h�A�̍� [%f, %f, %f]", m_pLeftDoor->GetPosition().x, m_pLeftDoor->GetPosition().y, m_pLeftDoor->GetPosition().z);
}

//=====================================================================
// Behavior
//=====================================================================
//=====================================================
// ���Behavior
//=====================================================
CTitleBehavior::CTitleBehavior()
{// �R���X�g���N�^

}

CTitleBehavior::~CTitleBehavior()
{// �f�X�g���N�^

}

//=====================================================
// �X�^�[�g�\�����
//=====================================================
CTitleStart::CTitleStart()
{// �R���X�g���N�^
	m_pStart = nullptr;
	m_pAfter = nullptr;

	// �X�^�[�g�\���̐���
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
{// �f�X�g���N�^
	Object::DeleteObject((CObject**)&m_pStart);
	Object::DeleteObject((CObject**)&m_pAfter);
}

void CTitleStart::Update(CTitle *pTitle)
{// �X�V
	if (m_pAfter == nullptr)
	{
		CInputManager *pInput = CInputManager::GetInstance();

		if (pInput == nullptr)
			return;

		if (pInput->GetTrigger(CInputManager::BUTTON_ENTER))
		{
			// �T�E���h�C���X�^���X�̎擾
			CSound* pSound = CSound::GetInstance();

			if (pSound != nullptr)
				pSound->Play(pSound->LABEL_SE_GAME_START);

			// �c���̐���
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
		// �T�C�Y�̕ύX
		float fWidth = m_pAfter->GetSize().x;
		float fHeight = m_pAfter->GetSize().y;

		fWidth += SPEED_AFTER_EXPAND;
		fHeight += SPEED_AFTER_EXPAND;

		CDebugProc::GetInstance()->Print("\n����������������������������[%f]", fHeight);

		m_pAfter->SetSize(fWidth, fHeight);
		m_pAfter->SetVtx();

		// �F�̕ύX
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
// �X�^�[�g�\�����
//=====================================================
CTitleMenu::CTitleMenu()
{// �R���X�g���N�^
	const char* aPath[MENU_MAX] =
	{// ���j���[�̃e�N�X�`���p�X
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
{// �f�X�g���N�^
	Object::DeleteObject((CObject**)&m_apMenu, MENU_MAX);
}

void CTitleMenu::Update(CTitle *pTitle)
{// �X�V
	// ����
	Input();

	// �J�[�\���̐���
	ManageCursor();

	// �F�̊Ǘ�
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
{// ����
	CInputManager *pInput = CInputManager::GetInstance();

	if (pInput == nullptr)
		return;

	// ���ڑI��
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
{// �J�[�\���̐���
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
{// �R���X�g���N�^

	Camera::ChangeState(new CCameraStateFollowPlayerTitle);
}

CTitleBehindPlayer::~CTitleBehindPlayer()
{// �f�X�g���N�^

}

void CTitleBehindPlayer::Update(CTitle* pTItle)
{// �X�V����

	CMotion* pBike = pTItle->GetBike();

	if (pBike == nullptr)
		return;

	// �i�[�ɂ̃h�A���J��
	pTItle->DoorOpen();

	// �J�����ʒu�̐ݒ�
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
		return;

	CCamera::Camera* pInfoCamera = pCamera->GetCamera();

	D3DXVECTOR3 BikePos = pBike->GetPosition();

	// ���[�V�������I�����Ă�����o�C�N�̑O�i������
	if (pBike->IsFinish())
		pTItle->ChangeBehavior(new CTitlePlayerAcceleration);
		
}

CTitlePlayerAcceleration::CTitlePlayerAcceleration()
{// �R���X�g���N�^

	
}

CTitlePlayerAcceleration::~CTitlePlayerAcceleration()
{// �f�X�g���N�^

}

void CTitlePlayerAcceleration::Update(CTitle* pTItle)
{// �X�V����

	CMotion* pBike = pTItle->GetBike();

	if (pBike == nullptr)
		return;

	float fSpeed = pBike->GetMove().z;

	fSpeed = (fSpeed + 0.03f) * 1.1f;

	pBike->SetMove({ 0.0f, 0.0f, fSpeed });

	// �v���C���[����������
	pTItle->PlayerAcceleration();

	// �X�s�[�h�����l�ɒB�������������߂�
	if (fSpeed >= PLAYER_MAX_SPEED)
		pTItle->ChangeBehavior(new CTitleMovePlayer);
}

CTitleMovePlayer::CTitleMovePlayer()
{// �R���X�g���N�^

	Camera::ChangeState(nullptr);

	// �T�E���h�C���X�^���X�̎擾
	CSound* pSound = CSound::GetInstance();

	if (pSound == nullptr)
		return;

	pSound->Stop(pSound->LABEL_SE_ENGINE_START);
	pSound->Play(pSound->LABEL_SE_BIKE_ACCELERATION);
}

CTitleMovePlayer::~CTitleMovePlayer()
{// �f�X�g���N�^

}

void CTitleMovePlayer::Update(CTitle* pTItle)
{// �X�V����

	CMotion* pBike = pTItle->GetBike();

	if (pBike == nullptr)
		return;

	// �v���C���[����������
	pTItle->PlayerAcceleration();

	// �J�����ʒu�̐ݒ�
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

	pInfoCamera->posRDest.y += 50.0f;	// ��U�ނ��肿����ƍ�������

	pInfoCamera->posR = pInfoCamera->posRDest;

	// �ڕW�̎��_�ݒ�
	D3DXVECTOR3 vecPole = universal::PolarCoordinates(pInfoCamera->rot);
	pInfoCamera->posVDest = pos + vecPole * pInfoCamera->fLength;

	pCamera->SetPosV();

	pCamera->MoveDist(0.2f);

	float BikePosZ = pBike->GetPosition().z;

	if (BikePosZ >= REBOOST_POS_Z)
		pTItle->ChangeBehavior(new CTitleFade);
		

	CDebugProc::GetInstance()->Print("\n�v���C���[�̈ʒu [%f, %f, %f]", pos.x, pos.y, pos.z);
	CDebugProc::GetInstance()->Print("\n�����_ [%f, %f, %f]", pInfoCamera->posR.x, pInfoCamera->posR.y, pInfoCamera->posR.z);
	CDebugProc::GetInstance()->Print("\n�����_�ړI [%f, %f, %f]", pInfoCamera->posRDest.x, pInfoCamera->posRDest.y, pInfoCamera->posRDest.z);
}

CTitleFade::CTitleFade()
{// �R���X�g���N�^
	
	Camera::ChangeState(nullptr);
}

CTitleFade::~CTitleFade()
{// �f�X�g���N�^

}

void CTitleFade::Update(CTitle* pTItle)
{// �X�V����
	
	CMotion* pBike = pTItle->GetBike();

	if (pBike == nullptr)
		return;

	float fSpeed = pBike->GetMove().z;

	fSpeed = (fSpeed + 0.03f) * 1.1f;

	pBike->SetMove({ 0.0f, 0.0f, fSpeed });

	// �v���C���[����������
	pTItle->PlayerAcceleration();

	// �T�E���h�C���X�^���X�̎擾
	CSound* pSound = CSound::GetInstance();

	if (pSound == nullptr)
		return;

	if (pSound != nullptr)
	{
		if (m_fVolume >= 0.0f)
		    m_fVolume -= 0.04f;

		pSound->SetVolume(pSound->LABEL_SE_BIKE_ACCELERATION, m_fVolume);
	}

	// �v���C���[�̑��x�����l�ɒB������J�ڂ���
	if (fSpeed >= FADE_PLAYER_SPEED)
		Fade();

	CDebugProc::GetInstance()->Print("\nSE�̉���:%f", m_fVolume);
}

void CTitleFade::Fade(void)
{// �t�F�[�h����

	CFade* pFade = CFade::GetInstance();

	if (pFade == nullptr)
		return;

	if (pFade->GetState() != CFade::FADE_NONE)
		return;

	pFade->SetFade(CScene::MODE_GAME);
}