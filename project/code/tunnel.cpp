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
#include "player.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int MESH_U = 32;	// ���̕�����
const float MESH_HEIGHT = 50.0f;	// ���b�V���̍���
const char* TEX_PATH = "data\\TEXTURE\\MATERIAL\\concrete.jpg";	// �e�N�X�`���p�X
const int NUM_VTX_IN_EDGE = 5;	// �ӂ̒��ɂ��钸�_��
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CTunnel::CTunnel(int nPriority) : CMeshCylinder(nPriority),m_bInPlayer(false)
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

	pTunnel = new CTunnel;

	if (pTunnel != nullptr)
	{
		pTunnel->m_itStart = itStart;
		pTunnel->m_itEnd = itEnd;

		pTunnel->Init();
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
		std::vector<CMeshRoad::SInfoRoadPoint> *pList = pMesh->GetArrayRP();

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
		int nIdx = i * 2;

		D3DXVECTOR3 pos1;
		D3DXVECTOR3 pos2;

		if (i == nMeshV)
		{
			pos1 = vectorPosEdge[nMeshV * 2 - 2];
			pos2 = vectorPosEdge[nMeshV * 2 - 1];
		}
		else
		{
			pos1 = vectorPosEdge[nIdx];
			pos2 = vectorPosEdge[nIdx + 1];
		}

		D3DXVECTOR3 vecDiff = pos2 - pos1;

		float fWidthRoad = sqrtf(vecDiff.x * vecDiff.x + vecDiff.z * vecDiff.z) * 0.5f;

		for (int j = 0; j <= MESH_U / 2; j++)
		{
			float fRate = (float)j / (MESH_U / 2);
			
			pVtx[j].pos = pos1 + vecDiff * 0.5f * cosf(D3DX_PI * fRate) + vecDiff * 0.5f;

			float fHeight = sinf(D3DX_PI * fRate) * fWidthRoad;
			pVtx[j].pos.y += fHeight;

			pVtx[MESH_U - j].pos = pVtx[j].pos;
			pVtx[MESH_U - j].pos.y -= fHeight * 2;
		}

		pVtx += MESH_U + 1;
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
	// �v���C���[�̌��m
	DetectionPlayer();

	CMeshCylinder::Update();
}

//=====================================================
// �v���C���[�̌��m
//=====================================================
void CTunnel::DetectionPlayer(void)
{
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
		return;

	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	if (m_bInPlayer)
	{
		// �v���C���[�������Ă�������
	}
	else
	{
		// �v���C���[���o�Ă���������
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CTunnel::Draw(void)
{
	CMeshCylinder::Draw();
}