//*****************************************************
//
// �g���l���̏���[tunnel.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "guardRail.h"
#include "texture.h"
#include "effect3D.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const char* TEX_PATH = "data\\TEXTURE\\MATERIAL\\concrete.jpg";	// �e�N�X�`���p�X
const int NUM_VTX_ON_POINT = 2;	// ���b�V�����[�h�̒��_��ɂ��钸�_��
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CGuardRail::CGuardRail(int nPriority) : CObject3D(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CGuardRail::~CGuardRail()
{

}

//=====================================================
// ��������
//=====================================================
CGuardRail *CGuardRail::Create(std::vector<CMeshRoad::SInfoRoadPoint>::iterator itStart, std::vector<CMeshRoad::SInfoRoadPoint>::iterator itEnd)
{
	CGuardRail *pGuardRail = nullptr;

	pGuardRail = new CGuardRail;

	if (pGuardRail != nullptr)
	{
		pGuardRail->m_itStart = itStart;
		pGuardRail->m_itEnd = itEnd;

		pGuardRail->Init();
	}

	return pGuardRail;
}

//=====================================================
// ����������
//=====================================================
HRESULT CGuardRail::Init(void)
{
	// ���_����
	CreateVtx();

	// ���_�𓹂ɉ��킹��
	VtxFollowRoad();

	return S_OK;
}

//=====================================================
// ���_�̐���
//=====================================================
void CGuardRail::CreateVtx(void)
{
	int nDistIt = std::distance(m_itStart, m_itEnd);
	int nNumVtx = nDistIt * NUM_VTX_ON_POINT;

	// ���_����
	CreateVtxBuff(nNumVtx);

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
void CGuardRail::VtxFollowRoad(void)
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
		nDistBetween *= MeshRoad::NUM_EDGE_IN_ROADPOINT;

		for (int i = 0; i < nDistBetween; i++)
		{
			CEffect3D::Create(pVtx[0].pos, 20.0f, 3, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

			vectorPosEdge.push_back(pVtx[0].pos);

			pVtx += 2;
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



	// ���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}

//=====================================================
// �I������
//=====================================================
void CGuardRail::Uninit(void)
{
	CObject3D::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CGuardRail::Update(void)
{
	CObject3D::Update();
}

//=====================================================
// �`�揈��
//=====================================================
void CGuardRail::Draw(void)
{
	CObject3D::Draw();
}