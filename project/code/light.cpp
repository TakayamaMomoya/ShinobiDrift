//*****************************************************
//
// ���C�g�̏���[light.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "light.h"
#include "manager.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "debugproc.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float SPEED_CHANGE_COL = 0.1f;	// �F��ς��鑬�x
const D3DXCOLOR INTIIAL_COLOR[MAX_LIGHT] =
{// �����̐F
	D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f),
	D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f),
	D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f)
};
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CLight::s_nNumAll = 0;	// ����
vector<CLight*> CLight::s_aLight;	// ���C�g�̊i�[�p�z��

//====================================================
// �R���X�g���N
//====================================================
CLight::CLight()
{
	m_nID = s_nNumAll;
	s_nNumAll++;
	s_aLight.push_back(this);
}

//====================================================
// �f�X�g���N
//====================================================
CLight::~CLight()
{
	s_nNumAll--;
}

//====================================================
// ����
//====================================================
CLight *CLight::Create(void)
{
	CLight *pLight = nullptr;

	pLight = new CLight;

	if (pLight == nullptr)
		return nullptr;

	pLight->Init();

	return pLight;
}

//====================================================
// ����������
//====================================================
HRESULT CLight::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//���C�g�̎�ސݒ�
	m_light.Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U���̐ݒ�
	m_light.Diffuse = INTIIAL_COLOR[0];

	//���C�g�̕����ݒ�
	D3DXVECTOR3 vecDir = D3DXVECTOR3(-1.4f, 0.24f, -2.21f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g�����K��
	m_light.Direction = vecDir;

	//���C�g�ݒ�
	pDevice->SetLight(m_nID, &m_light);

	//���C�g�L����
	pDevice->LightEnable(m_nID, TRUE);
	return S_OK;
}

//====================================================
// �I������
//====================================================
void CLight::Uninit(void)
{
	Release();
}

//====================================================
// �X�V����
//====================================================
void CLight::Update(void)
{

}

//====================================================
// ���C�g���ݒ�
//====================================================
void CLight::SetLightInfo(D3DLIGHT9 light)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	m_light = light;

	pDevice->SetLight(m_nID, &m_light);
}

//====================================================
// ���C�g�̗L�����؂�ւ�
//====================================================
void CLight::EnableLight(bool bFrag)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//���C�g�L����
	pDevice->LightEnable(m_nID, bFrag);
}

//====================================================
// �S���C�g�̉��
//====================================================
void CLight::ReleaseAll(void)
{
	for (auto it : s_aLight)
	{
		it->Uninit();
	}

	s_aLight.clear();
}