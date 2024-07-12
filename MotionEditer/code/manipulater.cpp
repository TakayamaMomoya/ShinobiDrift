//*****************************************************
//
// �}�j�s�����[�^�[[manipulater.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "manipulater.h"
#include "motion.h"
#include "inputmouse.h"
#include "manager.h"
#include "effect3D.h"
#include "debugProc.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float LENGTH_TRANSLATE_MANIPULATER = 30.0f;  // �g���X���[�g�}�j�s�����[�^�[�̒���
const float RADIUS_TRANSLATE_MANIPULATER = 10.0f;  // �g���X���[�g�}�j�s�����[�^�[�̔��a
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CManipulater::CManipulater(int nPriority)
{
    m_nIdxPart = 0;
    m_pState = nullptr;
    m_pMotion = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CManipulater::~CManipulater()
{

}

//=====================================================
// ��������
//=====================================================
CManipulater* CManipulater::Create(int nIdxPart, CMotion *pMotion)
{
    CManipulater *pManipulater = nullptr;

	if (pManipulater == nullptr)
	{
        pManipulater = new CManipulater;

		if (pManipulater != nullptr)
		{
			// ������
            pManipulater->Init();

            pManipulater->m_nIdxPart = nIdxPart;
            pManipulater->m_pMotion = pMotion;
		}
	}

	return pManipulater;
}

//=====================================================
// ����������
//=====================================================
HRESULT CManipulater::Init(void)
{
    ChangeState(new CStateManipulaterTranslate);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CManipulater::Uninit(void)
{
    if (m_pState != nullptr)
    {
        m_pState->Uninit(this);
        m_pState = nullptr;
    }

    Release();
}

//=====================================================
// �X�V����
//=====================================================
void CManipulater::Update(void)
{
    // �p�[�c�̈ʒu�̎擾
    D3DXVECTOR3 posPart = m_pMotion->GetMtxPos(m_nIdxPart);
    D3DXVECTOR3 rotPart = universal::ExtractEulerAngles(*m_pMotion->GetParts(m_nIdxPart)->pParts->GetMatrix());
    int nIdxPartParent = m_pMotion->GetParts(m_nIdxPart)->nIdxParent;

    if (nIdxPartParent != -1)
    {// �e������ꍇ�͐e�̃}�g���b�N�X����������擾
        rotPart = universal::ExtractEulerAngles(*m_pMotion->GetParts(nIdxPartParent)->pParts->GetMatrix());
    }
    else
    {// �e�����Ȃ���������Z�b�g
        rotPart = { 0.0f,0.0f,0.0f };
    }

    SetPosition(posPart);
    SetRotation(rotPart);

    if (m_pState != nullptr)
    {
        m_pState->Update(this);
    }
}

//=====================================================
// �`�揈��
//=====================================================
void CManipulater::Draw(void)
{

}

//=====================================================
// �X�e�C�g�̕ύX
//=====================================================
void CManipulater::ChangeState(CStateManipulater *pState)
{
    if (m_pState != nullptr)
    {
        m_pState->Uninit(this);
        m_pState = nullptr;
    }

    m_pState = pState;

    if (m_pState != nullptr)
    {
        m_pState->Init(this);
    }
}

//********************************************************************************
// �ړ��̃X�e�C�g
//********************************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CStateManipulaterTranslate::CStateManipulaterTranslate()
{
    m_pManipulater = nullptr;
    m_mode = E_MODE::MODE_NONE;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CStateManipulaterTranslate::~CStateManipulaterTranslate()
{

}

//=====================================================
// ������
//=====================================================
void CStateManipulaterTranslate::Init(CManipulater *pManipulater)
{
    m_pManipulater = CObjectX::Create();

    int nIdx = CModel::Load("data\\MODEL\\manipulator.x");
    m_pManipulater->BindModel(nIdx);
    m_pManipulater->EnableZtest(true);
}

//=====================================================
// �I��
//=====================================================
void CStateManipulaterTranslate::Uninit(CManipulater *pManipulater)
{

}

//=====================================================
// �X�V
//=====================================================
void CStateManipulaterTranslate::Update(CManipulater *pManipulater)
{
    // ����
    Input(pManipulater);

    // ���f���̒Ǐ]
    FollowModel(pManipulater);

    // ���[�h���Ƃ̓���
    ModeMove(pManipulater);
}

//=====================================================
// ���͏���
//=====================================================
void CStateManipulaterTranslate::Input(CManipulater *pManipulater)
{
    CInputMouse *pMouse = CManager::GetMouse();

    if (pMouse == nullptr)
        return;

    D3DXVECTOR3 posNear;
    D3DXVECTOR3 posFar;
    D3DXVECTOR3 vecDiff;

    universal::ConvertScreenPosTo3D(&posNear, &posFar, &vecDiff);

    D3DXVECTOR3 posManipulater = pManipulater->GetPosition();
    D3DXVECTOR3 rotManipulater = pManipulater->GetRotation();

    D3DXVECTOR3 posEnter;
    D3DXVECTOR3 posExit;

    // Y���̉~���̐���
    D3DXVECTOR3 vecCylinderY = posManipulater + universal::PolarCoordinates(rotManipulater) * LENGTH_TRANSLATE_MANIPULATER;

    bool bHit = universal::RayCollideCylinder(posNear, posFar, posManipulater, vecCylinderY, RADIUS_TRANSLATE_MANIPULATER,
        &posEnter, &posExit, false);

    if (bHit)
    {
        CEffect3D::Create(posEnter, 10.0f, 3, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

        if (pMouse->GetTrigger(CInputMouse::BUTTON::BUTTON_LMB))
        {
            m_mode = E_MODE::MODE_Y;
        }
    }

    if(pMouse->GetRelease(CInputMouse::BUTTON::BUTTON_LMB))
        m_mode = E_MODE::MODE_NONE;

    CEffect3D::Create(posManipulater, 10.0f, 3, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
    CEffect3D::Create(vecCylinderY, 10.0f, 3, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
}

//=====================================================
// ���f���̒Ǐ]
//=====================================================
void CStateManipulaterTranslate::FollowModel(CManipulater *pManipulater)
{
    // ���f���̒Ǐ]
    D3DXVECTOR3 posManipulater = pManipulater->GetPosition();
    D3DXVECTOR3 rotManipulater = pManipulater->GetRotation();

    m_pManipulater->SetPosition(posManipulater);
    m_pManipulater->SetRot(rotManipulater);
}

//=====================================================
// ���[�h���Ƃ̓���
//=====================================================
void CStateManipulaterTranslate::ModeMove(CManipulater *pManipulater)
{
    D3DXVECTOR3 posNear;
    D3DXVECTOR3 posFar;
    D3DXVECTOR3 vecDiffCast;

    universal::ConvertScreenPosTo3D(&posNear, &posFar, &vecDiffCast);

    D3DXVECTOR3 vecAxis = {};
    D3DXVECTOR3 vecAxis2 = {};
    D3DXVECTOR3 vecDiff = {};
    D3DXVECTOR3 posHit = {};
    D3DXVECTOR3 posManipulater = pManipulater->GetPosition();
    D3DXVECTOR3 rotManipulater = pManipulater->GetRotation();
    float fLengthAxis = 0.0f;
    float fLengthDiff = 0.0f;
    float fDot = 0.0f;
    float fLength = 0.0f;
    float fAngle = 0.0f;

    switch (m_mode)
    {
    case E_MODE::MODE_X:
        CDebugProc::GetInstance()->Print("\nX�����[�h");

        break;
    case E_MODE::MODE_Y:
        CDebugProc::GetInstance()->Print("\nY�����[�h");
        // XY���ʂŃ}�E�X�̃��C�L���X�g���s��
        // Y���x�N�g���̍쐬
        vecAxis = universal::PolarCoordinates(rotManipulater) * LENGTH_TRANSLATE_MANIPULATER;

        // �^���̃x�N�g�����쐬����
        //rotManipulater.x += D3DX_PI * 0.5f; // �ɍ��W�̂��߂Ƀ��[��������
        //rotManipulater.y += D3DX_PI * 0.5f; // �ɍ��W�̂��߂Ƀ��[��������
        vecAxis2 = universal::PolarCoordinates(rotManipulater) * LENGTH_TRANSLATE_MANIPULATER;
        //D3DXVec3Normalize(&vecAxis2, &vecAxis2);

        universal::CalcRayFlat(posManipulater, vecAxis2, posNear, posFar, &posHit);

        CEffect3D::Create(posHit, 10.0f, 3, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
        CEffect3D::Create(vecAxis2 * 50.0f, 10.0f, 3, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

        break;
    case E_MODE::MODE_Z:
        CDebugProc::GetInstance()->Print("\nZ�����[�h");

        break;
    }

    CDebugProc::GetInstance()->Print("\nfLength[%f]", fLength);
}
