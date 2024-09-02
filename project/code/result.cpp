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
#include "UIManager.h"
#include "UI.h"
#include "texture.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const D3DXVECTOR3 POS_DISP_TIME = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.4f, 0.0f };	// �^�C���̕\���ʒu
const string PATH_SAVE = "data\\BYNARY\\gametime.bin";	// �Q�[���̋L�^���Ԃ̕ۑ�
const D3DXCOLOR COL_BACK = { 0.0f ,0.0f,0.0f,0.6f };	// �w�i�|���S���̐F
const float SPEED_BACK_COLOR = 0.2f;	// �w�i�̏o�Ă���X�s�[�h
const D3DXCOLOR COL_DEST_NUMBER = { 1.0f ,1.0f,1.0f,1.0f };	// �����|���S���̖ڕW�F
const float SPEED_APPER_TIME = 0.1f;	// �^�C�}�[�̏o���X�s�[�h
const D3DXVECTOR3 POS_TIMER = { 0.4f,0.55f,0.0f };	// �^�C�}�[�̏����ʒu
const D3DXVECTOR2 SIZE_CAPTION = { 0.3f, 0.05f };	// �L���v�V�����̃T�C�Y
const string PATH_TEX_CAPTION = "data\\TEXTURE\\UI\\resultCaption00.png";	// �L���v�V�����̃e�N�X�`���p�X
const D3DXVECTOR3 POS_CAPTION_INITIAL = { 1.0f + SIZE_CAPTION.x,0.4f,0.0f };	// �L���v�V�����̏����ʒu
const D3DXVECTOR3 POS_CAPTION_DEST = { 0.5f,0.4f,0.0f };	// �L���v�V�����̖ڕW�ʒu
const float SPEED_CAPTION = 0.05f;	// �L���v�V�����̃X�s�[�h
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

	// �Q�[��UI�̍폜
	CUIManager *pUIManager = CUIManager::GetInstance();

	if (pUIManager != nullptr)
		pUIManager->ReleaseGameUI();

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
CStateResultDispTime::CStateResultDispTime() : m_pTimeOwn(nullptr), m_pCaption(nullptr), m_fCntAnim(0.0f)
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

	// ���ڂ̌��o������
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

	// ���j���[���ڂ̐���
	
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
	m_pTimeOwn->SetPosition(POS_TIMER);
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

	// ���o���̍X�V
	UpdateCaption();

	// �t�F�[�h���n�߂�
	if (pInputManager->GetTrigger(CInputManager::BUTTON_ENTER))
		pResult->StartFade();
}

//=====================================================
// �����̍X�V
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
// ���o���̍X�V
//=====================================================
void CStateResultDispTime::UpdateCaption(void)
{
	if (m_pCaption == nullptr)
		return;

	m_fCntAnim += SPEED_CAPTION;

	universal::LimitValuefloat(&m_fCntAnim, 1.0f, 0.0f);

	float fRate = universal::EaseOutBack(m_fCntAnim);

	// �L���v�V�����̈ʒu��ݒ�
	D3DXVECTOR3 vecDiff = POS_CAPTION_DEST - POS_CAPTION_INITIAL;
	D3DXVECTOR3 pos = POS_CAPTION_INITIAL + vecDiff * fRate;

	CDebugProc::GetInstance()->Print("\n�L���v�V�����ʒu[%f,%f]", m_pCaption->GetPosition().x, m_pCaption->GetPosition().y);

	m_pCaption->SetPosition(pos);
	m_pCaption->SetVtx();
}