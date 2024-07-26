//*****************************************************
//
// �X�J�C�{�b�N�X�̏���[skybox.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "skybox.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CSkybox *CSkybox::m_pSkybox = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CSkybox::CSkybox(int nPriority) : CObjectX(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CSkybox::~CSkybox()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CSkybox::Init(void)
{
	// �p���N���X�̏�����
	CObjectX::Init();

	// ���f���̓Ǎ�
	int nIdx = CModel::Load("data\\MODEL\\skybox\\sky00.x");
	BindModel(nIdx);

	EnableLighting(true);
	EnableFog(false);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CSkybox::Uninit(void)
{
	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CSkybox::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();

	// �v���C���[�̒Ǐ]
	FollowPlayer();
}

//=====================================================
// �v���C���[�̒Ǐ]
//=====================================================
void CSkybox::FollowPlayer(void)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;

	SetPosition(pPlayer->GetPosition());
}

//=====================================================
// �`�揈��
//=====================================================
void CSkybox::Draw(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CRenderer::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �p���N���X�̕`��
	CObjectX::Draw();

	// ���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=====================================================
// ��������
//=====================================================
CSkybox *CSkybox::Create()
{
	CSkybox *pSkybox = nullptr;

	if (pSkybox == nullptr)
	{
		pSkybox = new CSkybox;

		if (pSkybox != nullptr)
		{
			// ������
			pSkybox->Init();
		}
	}

	return pSkybox;
}