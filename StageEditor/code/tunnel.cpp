//*****************************************************
//
// �g���l���̏���[tunnel.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "tunnel.h"
#include "texture.h"
#include "effect3D.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int MESH_U = 16;	// ���̕�����
const float MESH_HEIGHT = 50.0f;	// ���b�V���̍���
const char* TEX_PATH = "data\\TEXTURE\\MATERIAL\\concrete.jpg";	// �e�N�X�`���p�X
const int NUM_VTX_IN_EDGE = 5;	// �ӂ̒��ɂ��钸�_��
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CTunnel::CTunnel(int nPriority) : CMeshCylinder(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTunnel::~CTunnel()
{

}

//=====================================================
// ��������
//=====================================================
CTunnel *CTunnel::Create(std::vector<CMeshRoad::SInfoRoadPoint>::iterator itStart, std::vector<CMeshRoad::SInfoRoadPoint>::iterator itEnd)
{
	CTunnel *pTunnel = nullptr;

	if (pTunnel == nullptr)
	{
		pTunnel = new CTunnel;

		if (pTunnel != nullptr)
		{
			pTunnel->m_itStart = itStart;
			pTunnel->m_itEnd = itEnd;

			pTunnel->Init();
		}
	}

	return pTunnel;
}

//=====================================================
// ����������
//=====================================================
HRESULT CTunnel::Init(void)
{
	// ���_�̐���
	CreateVtx();

	// ���_�𓹂ɉ��킹��
	VtxFollowRoad();

	return S_OK;
}

//=====================================================
// ���_�̐���
//=====================================================
void CTunnel::CreateVtx(void)
{
	int nDistStart = std::distance(m_itStart, m_itEnd);

	// �������ݒ�
	int nMeshV = nDistStart * MeshRoad::NUM_EDGE_IN_ROADPOINT;

	SetNumMeshU(MESH_U);
	SetNumMeshV(nMeshV);

	// �p���N���X�̏�����
	CMeshCylinder::Init();

	// ���_�ʒu�ݒ�
	SetVtx();

	// �e�N�X�`���̓Ǎ�
	CTexture *pTexture = CTexture::GetInstance();

	if (pTexture != nullptr)
	{
		int nIdx = pTexture->Regist(TEX_PATH);
		SetIdxTexture(nIdx);
	}
}

//=====================================================
// ���_�𓹂ɉ��킹��
//=====================================================
void CTunnel::VtxFollowRoad(void)
{
	// �J�n�ƏI���܂ł̒��_�ʒu��ۑ�============================
	CMeshRoad *pMesh = CMeshRoad::GetInstance();

	std::vector<D3DXVECTOR3> vectorPosEdge;

	if (pMesh != nullptr)
	{
		// �J�n�n�_���Z�o
		std::vector<CMeshRoad::SInfoRoadPoint> *pList = pMesh->GetList();

		int nDistStart = std::distance(pList->begin(), m_itStart) + 1;

		LPDIRECT3DVERTEXBUFFER9 pVtxBuffRoad = pMesh->GetVtxBuff();

		// ���_���̃|�C���^
		VERTEX_3D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		pVtxBuffRoad->Lock(0, 0, (void**)&pVtx, 0);

		// �J�n�n�_�܂Ń|�C���^��i�߂�
		pVtx += nDistStart * MeshRoad::NUM_EDGE_IN_ROADPOINT * MeshRoad::NUM_VTX_IN_EDGE;

		// ���_���̌v�Z
		int nDistBetween = std::distance(m_itStart, m_itEnd);
		nDistBetween *= MeshRoad::NUM_EDGE_IN_ROADPOINT * MeshRoad::NUM_VTX_IN_EDGE;

		for (int i = 0; i < nDistBetween; i++)
		{
			CEffect3D::Create(pVtx[0].pos, 200.0f, 5000, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

			vectorPosEdge.push_back(pVtx[0].pos);

			pVtx++;
		}

		// ���_�o�b�t�@���A�����b�N
		pVtxBuffRoad->Unlock();
	}
	else
	{
		return;
	}

	// ���_�𓹂ɉ��킹��========================================
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_���̃|�C���^
	VERTEX_3D *pVtx;
	
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nMeshV = GetMeshCylinder()->nMeshV;

	for (int i = 0; i < nMeshV + 1; i++)
	{
		for (int j = 0; j < MESH_U + 1; j++)
		{
			CEffect3D::Create(pVtx[0].pos, 10.0f, 5000, D3DXCOLOR(1.0f, 1.0f - 0.1 * j, 0.0f, 1.0f));

			pVtx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}

//=====================================================
// �I������
//=====================================================
void CTunnel::Uninit(void)
{
	CMeshCylinder::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CTunnel::Update(void)
{
	CMeshCylinder::Update();
}

//=====================================================
// �`�揈��
//=====================================================
void CTunnel::Draw(void)
{
	CMeshCylinder::Draw();
}