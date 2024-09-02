//*****************************************************
//
// ���U���g����[result.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
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

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const D3DXVECTOR3 POS_DISP_TIME = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.4f, 0.0f };	// �^�C���̕\���ʒu
const string PATH_SAVE = "data\\BYNARY\\gametime.bin";	// �Q�[���̋L�^���Ԃ̕ۑ�
const D3DXCOLOR COL_BACK = { 0.0f ,0.0f,0.0f,0.6f };	// �w�i�|���S���̐F
const float SPEED_BACK_COLOR = 0.2f;	// �w�i�̏o�Ă���X�s�[�h
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CResult::CResult() : CObject(1), m_pState(nullptr)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CResult::~CResult()
{

}

//=====================================================
// ��������
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
// ����������
//=====================================================
HRESULT CResult::Init(void)
{
	// �v���C���[�̐ݒ�
	SetPlayer();

	// �J�����ʒu�̐ݒ�
	SetCamera();

	// �^�C���̕ۑ�
	SaveTime();

	// �w�i�̗L����
	EnableBack();

	// �X�e�C�g�̕ύX
	ChangeState(new CStateResultDispTime);
	
	// �Q�[���^�C�}�[�̍폜
	CGame *pGame = CGame::GetInstance();

	if (pGame == nullptr)
		return E_FAIL;

	pGame->ReleaseGameTimer();

	return S_OK;
}

//=====================================================
// �v���C���[�ݒ�
//=====================================================
void CResult::SetPlayer(void)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;
	
	// �v���C���[�𑀍�ł��Ȃ��悤�ɂ���
	pPlayer->SetEnableInput(false);
}

//=====================================================
// �J�����ݒ�
//=====================================================
void CResult::SetCamera(void)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
		return;
	
	pCamera->ChangeState(new CCameraStateResult);
}

//=====================================================
// �^�C���̕ۑ�
//=====================================================
void CResult::SaveTime(void)
{
	CGame *pGame = CGame::GetInstance();

	if (pGame == nullptr)
		return;

	CTimer *pTimer = pGame->GetGameTimer();

	if (pTimer == nullptr)
		return;

	// �^�C���̎擾
	float fSecond = pTimer->GetSecond();

	// �t�@�C���ɕۑ�
	std::ofstream outputFile(PATH_SAVE, std::ios::binary);

	if (!outputFile.is_open())
		assert(("�^�C���̃t�@�C�����J���܂���ł���", false));

	outputFile.write(reinterpret_cast<const char*>(&fSecond), sizeof(float));
}

//=====================================================
// �I������
//=====================================================
void CResult::Uninit(void)
{
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CResult::Update(void)
{
	if (m_pState != nullptr)
	{
		m_pState->Update(this);
	}

	// �w�i�|���S���̐F�̕␳
	UpdateBack();
}

//=====================================================
// �`�揈��
//=====================================================
void CResult::Draw(void)
{

}

//=====================================================
// �w�i�|���S���̍X�V
//=====================================================
void CResult::UpdateBack(void)
{
	if (m_pBack == nullptr)
		return;

	// �F��ڕW�̐F�Ɍ������ĕ␳����
	D3DXCOLOR col = m_pBack->GetCol();

	col += (COL_BACK - col) * SPEED_BACK_COLOR;

	m_pBack->SetCol(col);

	CDebugProc::GetInstance()->Print("\n�F[%f,%f,%f,%f]", col.r, col.g, col.b, col.a);
}

//=====================================================
// �X�e�C�g�̕ύX
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
// �t�F�[�h���n�߂鏈��
//=====================================================
void CResult::StartFade(void)
{
	CGame *pGame = CGame::GetInstance();

	if (pGame == nullptr)
		return;

	pGame->SetState(CGame::STATE::STATE_END);
}

//=====================================================
// �w�i�̗L����
//=====================================================
void CResult::EnableBack(void)
{
	if (m_pBack != nullptr)
		return;

	// �w�i�|���S���̐���
	m_pBack = CPolygon2D::Create(6);

	if (m_pBack == nullptr)
		return;

	m_pBack->SetPosition(SCRN_MID);
	m_pBack->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pBack->SetVtx();
	m_pBack->EnableBlur(false);
	m_pBack->EnableAdd(true);

	// ���S�ɓ����ɐݒ�
	m_pBack->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
}

//=====================================================
// �X�e�C�g�̏I��
//=====================================================
void CStateResult::Uninit(CResult *pResult)
{

}

//********************************************************************************
// �^�C���\��
//********************************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CStateResultDispTime::CStateResultDispTime() : m_pTimeOwn(nullptr)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CStateResultDispTime::~CStateResultDispTime()
{

}

//=====================================================
// ������
//=====================================================
void CStateResultDispTime::Init(CResult *pResult)
{
	// �����̐ݒ�
	SetNumber();
}

//=====================================================
// �����̐ݒ�
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

	// ���g�̃^�C�}�[����
	m_pTimeOwn = CTimer::Create();

	if (m_pTimeOwn == nullptr)
		return;

	// �Q�[���^�C�}�[�̃^�C�����R�s�[
	float fTime = pGameTimer->GetSecond();
	m_pTimeOwn->SetSecond(fTime);
	m_pTimeOwn->SetColor(CTimer::E_Number::NUMBER_MAX, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
}

//=====================================================
// �I��
//=====================================================
void CStateResultDispTime::Uninit(CResult *pResult)
{
	CStateResult::Uninit(pResult);
}

//=====================================================
// �X�V
//=====================================================
void CStateResultDispTime::Update(CResult *pResult)
{
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager == nullptr)
		return;

	// �����̍X�V
	UpdateNumber();

	// �t�F�[�h���n�߂�
	if (pInputManager->GetTrigger(CInputManager::BUTTON_ENTER))
		pResult->StartFade();
}

//=====================================================
// �����̍X�V
//=====================================================
void CStateResultDispTime::UpdateNumber(void)
{

}