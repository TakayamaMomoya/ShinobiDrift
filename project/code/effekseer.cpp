//===========================================================
//
// ���̃G�t�F�N�V�A[effekseer.cpp]
// Author �匴�叫
//
//===========================================================

#include <iostream>
#include <string>

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "effekseer.h"
#include "camera.h"
#include "debugproc.h"

// �G�t�F�N�g�̖��O
const char* CEffekseer::m_apEfkName[CEffekseer::TYPE_MAX] =
{
	"",                               // �Ȃ���Ȃ�
	"data\\EFFEKSEER\\Effect\\drift.efkefc",  // �h���t�g���̉ΉԂƉ�
	"data\\EFFEKSEER\\Effect\\spark.efkefc",  // �ǏՓˎ��̉Ή�
	"data\\EFFEKSEER\\Effect\\bikefire.efkefc",  // �r�C���̉�
	"data\\EFFEKSEER\\Effect\\slash00.efkefc",  // �a��
};

//===========================================================
// �R���X�g���N�^
//===========================================================
CEffekseer::CEffekseer()
{
	// �l��������
	for (int i = 0; i < MAX_EFK; i++)
	{
		m_Info[i].pos = {};
		m_Info[i].rot = {};
		m_Info[i].effect = nullptr;
		m_Info[i].efkHandle = NULL;
		m_Info[i].EfkName = {};
		m_Info[i].time = 0;
	}

	m_nNum = 0;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CEffekseer::~CEffekseer()
{

}

//===========================================================
// ����������
//===========================================================
void CEffekseer::Init(void)
{
	// �G�t�F�N�g�̃}�l�[�W���[�̍쐬
	m_efkManager = ::Effekseer::Manager::Create(8000);

	// Specify a position of view
	// ���_�ʒu���m��
	viewerPosition = ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f);

	// ���W�n��ݒ肷��B�A�v���P�[�V�����ƈ�v������K�v������B
	m_efkManager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

	// Setup effekseer modules
	// Effekseer�̃��W���[�����Z�b�g�A�b�v����
	SetupEffekseerModules(m_efkManager);

	// Specify a projection matrix
	// ���e�s���ݒ�
	projectionMatrix.PerspectiveFovLH(90.0f / 180.0f * 3.14f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 1.0f, 500.0f);

	// Specify a camera matrix
		// �J�����s���ݒ�
	cameraMatrix.LookAtLH(viewerPosition, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f));
}

//===========================================================
// �I������
//===========================================================
void CEffekseer::Uninit(void)
{
	for (int i = 0; i < MAX_EFK; i++)
	{
		m_Info[i].pos = {};
		m_Info[i].rot = {};
		m_Info[i].effect = nullptr;
		m_Info[i].efkHandle = NULL;
		m_Info[i].EfkName = {};
		m_Info[i].time = 0;
	}

	m_nNum = 0;
}

//===========================================================
// �X�V����
//===========================================================
void CEffekseer::Update(void)
{
	for (int i = 0; i < MAX_EFK; i++)
	{
		if (m_Info[i].effect != nullptr)
		{
			// Move the effect
			// �G�t�F�N�g�̈ړ�
			m_efkManager->AddLocation(m_Info[i].efkHandle, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f));

			// Set layer parameters
			// ���C���[�p�����[�^�̐ݒ�
			Effekseer::Manager::LayerParameter layerParameter;
			layerParameter.ViewerPosition = viewerPosition;
			m_efkManager->SetLayerParameter(0, layerParameter);

			// Update the manager
			// �}�l�[�W���[�̍X�V
			Effekseer::Manager::UpdateParameter updateParameter;
			m_efkManager->Update(updateParameter);

			// Update a time
			// ���Ԃ��X�V����
			m_efkRenderer->SetTime(m_Info[i].time / 60.0f);
			m_Info[i].time++;

			// ���t���[���A�G�t�F�N�g���Đ��I�����Ă��邩�m�F����
			if (m_efkManager->Exists(m_Info[i].efkHandle) == false)
			{
				// �V���ɃG�t�F�N�g���Đ��������B���W�̓G�t�F�N�g��\���������ꏊ��ݒ肷��
				// (�ʒu���]�A�g��k�����ݒ肵�Ȃ����K�v������)
				m_efkManager->StopEffect(m_Info[i].efkHandle);
				Release(i);
			}
		}
	}
}

//===========================================================
// �`�揈��
//===========================================================
void CEffekseer::Draw(void)
{
	if (m_efkRenderer != nullptr)
	{
		// Specify a projection matrix
		// ���e�s���ݒ�
		m_efkRenderer->SetProjectionMatrix(projectionMatrix);

		// �J�����̏��擾
		CCamera* pCamera = CManager::GetCamera();

		// �r���[�}�g���b�N�X
		auto ViewMatrix = pCamera->GetCamera()->mtxView;

		// �v���W�F�N�V�����}�g���b�N�X
		auto Projection = pCamera->GetCamera()->mtxProjection;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				projectionMatrix.Values[i][j] = Projection.m[i][j];
				cameraMatrix.Values[i][j] = ViewMatrix.m[i][j];
			}
		}

		// Specify a camera matrix
		// �J�����s���ݒ�
		m_efkRenderer->SetCameraMatrix(cameraMatrix);

		// Begin to rendering effects
		// �G�t�F�N�g�̕`��J�n�������s���B
		m_efkRenderer->BeginRendering();

		// Render effects
		// �G�t�F�N�g�̕`����s���B
		Effekseer::Manager::DrawParameter drawParameter;
		drawParameter.ZNear = 0.0f;
		drawParameter.ZFar = 1.0f;
		drawParameter.ViewProjectionMatrix = m_efkRenderer->GetCameraProjectionMatrix();
		m_efkManager->Draw(drawParameter);

		// Finish to rendering effects
		// �G�t�F�N�g�̕`��I���������s���B
		m_efkRenderer->EndRendering();
	}
}

//===========================================================
// �ݒ�
//===========================================================
void CEffekseer::Set(const char *FileName, ::Effekseer::Vector3D pos, ::Effekseer::Vector3D rot, ::Effekseer::Vector3D scale)
{
	for (int i = 0; i < MAX_EFK; i++)
	{
		if (m_Info[i].effect == nullptr)
		{
			// char16_t�ɕϊ�
			std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
			std::u16string string16t = converter.from_bytes(FileName);

			m_Info[i].pos = pos;
 			m_Info[i].rot = rot;
			m_Info[i].scale = scale;
			m_Info[i].time = 0;

			//std::char_16
			// Load an effect
			// �G�t�F�N�g�̓Ǎ�
			m_Info[i].effect = Effekseer::Effect::Create(m_efkManager, string16t.c_str());

			// Play an effect
			// �G�t�F�N�g�̍Đ�
			m_Info[i].efkHandle = m_efkManager->Play(m_Info[i].effect, 0, 0, 0);

			// �ʒu�A�����A�傫���ݒ�
			m_efkManager->SetLocation(m_Info[i].efkHandle, m_Info[i].pos);
			m_efkManager->SetRotation(m_Info[i].efkHandle, {0.0f, 1.0f, 0.0f}, rot.Y);
			m_efkManager->SetScale(m_Info[i].efkHandle, m_Info[i].scale.X, m_Info[i].scale.Y, m_Info[i].scale.Z);
			
			break;
		}
	}
}

//===========================================================
// ���W���[���ݒ�
//===========================================================
void CEffekseer::SetupEffekseerModules(::Effekseer::ManagerRef efkManager)
{
		// Create a  graphics device
	// �`��f�o�C�X�̍쐬
	::Effekseer::Backend::GraphicsDeviceRef graphicsDevice;
	graphicsDevice = ::EffekseerRendererDX9::CreateGraphicsDevice(CRenderer::GetInstance()->GetDevice());

	// Create a renderer of effects
	// �G�t�F�N�g�̃����_���[�̍쐬
	m_efkRenderer = ::EffekseerRendererDX9::Renderer::Create(graphicsDevice, 8000);

	// Sprcify rendering modules
	// �`�惂�W���[���̐ݒ�
	efkManager->SetSpriteRenderer(m_efkRenderer->CreateSpriteRenderer());
	efkManager->SetRibbonRenderer(m_efkRenderer->CreateRibbonRenderer());
	efkManager->SetRingRenderer(m_efkRenderer->CreateRingRenderer());
	efkManager->SetTrackRenderer(m_efkRenderer->CreateTrackRenderer());
	efkManager->SetModelRenderer(m_efkRenderer->CreateModelRenderer());

	// Specify a texture, model, curve and material loader
	// It can be extended by yourself. It is loaded from a file on now.
	// �e�N�X�`���A���f���A�J�[�u�A�}�e���A�����[�_�[�̐ݒ肷��B
	// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
	efkManager->SetTextureLoader(m_efkRenderer->CreateTextureLoader());
	efkManager->SetModelLoader(m_efkRenderer->CreateModelLoader());
	efkManager->SetMaterialLoader(m_efkRenderer->CreateMaterialLoader());
	efkManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
}

void CEffekseer::Release(int idx)
{
	// �l��������
	m_Info[idx].pos = {};
	m_Info[idx].rot = {};
	m_Info[idx].scale = {};
	m_Info[idx].effect = nullptr;
	m_Info[idx].efkHandle = NULL;
	m_Info[idx].EfkName = {};
	m_Info[idx].time = 0;
}