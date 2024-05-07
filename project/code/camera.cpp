//*****************************************************
//
// �J�����̏���[camera.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "manager.h"
#include "renderer.h"
#include "main.h"
#include "camera.h"
#include "CameraState.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "debugproc.h"
#include "game.h"
#include "player.h"
#include "effect3D.h"
#include "meshfield.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float MOVE_SPEED = 3.0f;	// �ړ��X�s�[�h
const D3DXVECTOR3 INITIAL_ROT = { D3DX_PI * 0.4f,0.0f,0.0f };	// �����p�x
const float INITIAL_DIST = 300.0f;	// �����̋����i���_���璍���_�j
}
#define INITIAL_ANGLE	(45.0f)	// �����̎���p
#define HEIGHT_CAMERA (20.0f)	// �J�����̍���

//====================================================
// ����������
//====================================================
HRESULT CCamera::Init(void)
{
	ZeroMemory(&m_camera,sizeof(Camera));

	// �l�̏�����
	m_camera.rot = INITIAL_ROT;
	m_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_camera.fViewAngle = INITIAL_ANGLE;
	m_camera.fLength = INITIAL_DIST;

	// ���g�̃|�C���^���k���ɂ���
	m_pBehavior = nullptr;

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CCamera::Uninit(void)
{

}

//====================================================
// �X�V����
//====================================================
void CCamera::Update(void)
{
	if (m_pBehavior != nullptr)
	{
		m_pBehavior->Update(this);
	}
}

//====================================================
// �ڕW�Ɍ���������
//====================================================
void CCamera::MoveDist(float fFact)
{
	// ���b�V���t�B�[���h�Ƃ̓����蔻��
	CMeshField *pMesh = CMeshField::GetInstance();

	if(pMesh)
	{
		float fHeight = pMesh->GetHeight(m_camera.posVDest, nullptr);

		fHeight += HEIGHT_CAMERA;

		if (fHeight > m_camera.posVDest.y)
		{
			// �ʒu�␳
			m_camera.posVDest.y = fHeight;
		}
	}

	// �ڕW�ʒu�ɕ␳
	m_camera.posV += (m_camera.posVDest - m_camera.posV) * fFact;
	m_camera.posR += (m_camera.posRDest - m_camera.posR) * fFact;
	
	// �J�E���^�[�̕ύX
	if (m_camera.fTimeEvent > 0.0f)
	{
		float fDeltaTime = CManager::GetDeltaTime();

		m_camera.fTimeEvent -= fDeltaTime;

		if (m_camera.fTimeEvent <= 0.0f)
		{
			// �����l�ɖ߂�
			m_camera.fTimeEvent = 0.0f;

			m_camera.posVDest = D3DXVECTOR3(0.0f, 1050.0f, -590.0f);
			m_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �Q�[���𓮂���
			CGame *pGame = CGame::GetInstance();

			if (pGame != nullptr)
			{
				pGame->EnableStop(false);
			}
		}
	}
}

//====================================================
// �U������
//====================================================
void CCamera::Quake(void)
{
	//��ʐU��
	if (m_camera.nTimerQuake > 0)
	{
		//���Ԃ����炷
		m_camera.nTimerQuake--;

		//���_�����_�𓮂����ăJ������h�炷
		m_camera.posV.x += (float)(rand() % 201 - 100) * m_camera.fQuakeSizeH * sinf(m_camera.rot.y);
		m_camera.posV.y += (float)(rand() % 101 - 50) * m_camera.fQuakeSizeV;
		m_camera.posV.z += (float)(rand() % 201 - 100) * m_camera.fQuakeSizeH * cosf(m_camera.rot.y);

		m_camera.posR.x += (float)(rand() % 201 - 100) * m_camera.fQuakeSizeH * sinf(m_camera.rot.y);
		m_camera.posR.y += (float)(rand() % 101 - 50) * m_camera.fQuakeSizeV;
		m_camera.posR.z += (float)(rand() % 201 - 100) * m_camera.fQuakeSizeH * cosf(m_camera.rot.y);

		//���X�ɗh��̃T�C�Y������������
		m_camera.fQuakeSizeH += (0.0f - m_camera.fQuakeSizeH) * 0.03f;
		m_camera.fQuakeSizeV += (0.0f - m_camera.fQuakeSizeV) * 0.03f;
	}
}

//====================================================
// �U���ݒ�
//====================================================
void CCamera::SetQuake(float fQuakeSizeH, float fQuakeSizeV, int nTime)
{
	if (fQuakeSizeH > 0.0f && fQuakeSizeV > 0.0f)
	{
		//�h��鎞�ԑ��
		m_camera.nTimerQuake = nTime;

		//�h��̑傫�����
		m_camera.fQuakeSizeH = fQuakeSizeH;
		m_camera.fQuakeSizeV = fQuakeSizeV;
	}
}

//====================================================
// ���_�ݒ�
//====================================================
void CCamera::SetPosV(void)
{
	m_camera.posV =
	{
		m_camera.posR.x + sinf(m_camera.rot.x) * sinf(m_camera.rot.y + D3DX_PI) * m_camera.fLength,
		m_camera.posR.y + cosf(m_camera.rot.x) * m_camera.fLength,
		m_camera.posR.z + sinf(m_camera.rot.x) * cosf(m_camera.rot.y + D3DX_PI) * m_camera.fLength
	};
}

//====================================================
// �����_�ݒ�
//====================================================
void CCamera::SetPosR(void)
{
	m_camera.posRDest =
	{
		m_camera.posV.x - sinf(m_camera.rot.x) * sinf(m_camera.rot.y + D3DX_PI) * m_camera.fLength,
		m_camera.posV.y - cosf(m_camera.rot.x) * m_camera.fLength,
		m_camera.posV.z - sinf(m_camera.rot.x) * cosf(m_camera.rot.y + D3DX_PI) * m_camera.fLength
	};
}

//====================================================
// �ݒ菈��
//====================================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X==================================================
	//�v���W�F�N�V�����}�g���b�N�X������
	D3DXMatrixIdentity(&m_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�쐬
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection,
		D3DXToRadian(m_camera.fViewAngle),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		MIN_DRAW,
		MAX_DRAW);

	//�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,&m_camera.mtxProjection);

	//�r���[�}�g���b�N�X============================================================
	//�r���[�}�g���b�N�X������
	D3DXMatrixIdentity(&m_camera.mtxView);

	//�r���[�}�g���b�N�X�쐬
	D3DXMatrixLookAtLH(&m_camera.mtxView,
		&m_camera.posV,
		&m_camera.posR,
		&m_camera.vecU);

	//�r���[�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);

#ifdef _DEBUG
	CDebugProc::GetInstance()->Print("\n���_�̈ʒu�F[%f,%f,%f]", m_camera.posV.x, m_camera.posV.y, m_camera.posV.z);
	CDebugProc::GetInstance()->Print("\n�����_�̈ʒu�F[%f,%f,%f]", m_camera.posR.x, m_camera.posR.y, m_camera.posR.z);
	CDebugProc::GetInstance()->Print("\n�J�����̌����F[%f,%f,%f]", m_camera.rot.x, m_camera.rot.y, m_camera.rot.z);
	CDebugProc::GetInstance()->Print("\n�J���������F[%f]", m_camera.fLength);
#endif
}

//====================================================
// ���擾
//====================================================
CCamera::Camera *CCamera::GetCamera(void)
{
	return &m_camera;
}

//====================================================
// �s���̐؂�ւ�
//====================================================
void CCamera::ChangeState(CCameraState *pBehavior)
{
	if (m_pBehavior != nullptr)
	{
		delete m_pBehavior;
		m_pBehavior = nullptr;
	}

	m_pBehavior = pBehavior;
}

namespace Camera
{
// �s���̐؂�ւ�
void ChangeState(CCameraState *pBehavior)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->ChangeState(pBehavior);
	}
}
}