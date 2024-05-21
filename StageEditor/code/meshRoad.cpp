//*****************************************************
//
// ���b�V�����̏���[meshRoad.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "meshRoad.h"
#include "renderer.h"
#include "texture.h"
#include "effect3D.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const UINT NUMVTX_NOTDRAW = 4;	// ���̒��_�������̏ꍇ�A�`�悵�Ȃ�
const float WIDTH_DEFAULT = 200.0f;	// �f�t�H���g�̕�
const float LENGTH_DEFAULT = 200.0f;	// �f�t�H���g�̒���
const int NUM_VTX_IN_EDGE = 2;	// ��ӂɂ��钸�_��
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CMeshRoad *CMeshRoad::m_pMeshRoad = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CMeshRoad::CMeshRoad(int nPriority) : CObject3D(nPriority)
{
	m_nNumVtx = 0;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CMeshRoad::~CMeshRoad()
{

}

//=====================================================
// ��������
//=====================================================
CMeshRoad *CMeshRoad::Create(void)
{
	CMeshRoad *pMeshRoad = nullptr;

	if (pMeshRoad == nullptr)
	{
		// �C���X�^���X����
		pMeshRoad = new CMeshRoad;

		if (pMeshRoad != nullptr)
		{
			// ����������
			pMeshRoad->Init();

			m_pMeshRoad = pMeshRoad;
		}
	}

	return pMeshRoad;
}

//=====================================================
// ����������
//=====================================================
HRESULT CMeshRoad::Init(void)
{
	// ���X�g�̏�����
	m_listEdge.clear();

	m_nNumVtx = 4;

	AddEdge(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, true);
	AddEdge(D3DXVECTOR3(100.0f, 0.0f, 500.0f), 0.0f, true);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CMeshRoad::Uninit(void)
{
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CMeshRoad::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CMeshRoad::Draw(void)
{
	if (m_nNumVtx < NUMVTX_NOTDRAW)	// �`�搧��
		return;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	D3DXMATRIX *pMtx = GetMatrix();

	// ���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(pMtx);

	D3DXMATRIX mtxRot, mtxTrans;
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRot();

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxTrans);

	// ���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, pMtx);

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���ݒ�
	int nIdxTexture = GetIdxTexture();
	LPDIRECT3DTEXTURE9 pTexture = CTexture::GetInstance()->GetAddress(nIdxTexture);
	pDevice->SetTexture(0, pTexture);

	// �J�����O�𖳌���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_nNumVtx - 2);
}

//=====================================================
// �ӂ̒ǉ�
//=====================================================
void CMeshRoad::AddEdge(D3DXVECTOR3 pos, float fRot, bool bReCreateVtx)
{
	// ���X�g�ɏ���ǉ�
	SInfoEdge info;
	info.pos = pos;
	info.fRot = fRot;

	m_listEdge.push_back(info);

	if(bReCreateVtx)	// �ӂɉ��������_�̍Đ���
		CreateVtxBuffEdge();
}

//=====================================================
// �ӂɉ��������_�̐���
//=====================================================
void CMeshRoad::CreateVtxBuffEdge(void)
{
	// ���_�̐���
	m_nNumVtx = m_listEdge.size() * NUM_VTX_IN_EDGE;
	CreateVtxBuff(m_nNumVtx);

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�ʒu��ӂɍ��킹��
	int nCntEdge = 0;
	for (const auto& edge : m_listEdge)
	{
		int nIdx = nCntEdge * NUM_VTX_IN_EDGE;	// ���_�̔ԍ��v�Z

		// ���_�ʒu�̌v�Z
		D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, edge.fRot, 0.0f));
		CEffect3D::Create(edge.pos + vecPole * WIDTH_DEFAULT, 50.0f, 50000, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		CEffect3D::Create(edge.pos - vecPole * WIDTH_DEFAULT, 50.0f, 50000, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		pVtx[nIdx].pos = edge.pos + vecPole * WIDTH_DEFAULT;
		pVtx[nIdx + 1].pos = edge.pos - vecPole * WIDTH_DEFAULT;

		nCntEdge++;
	}

	// ���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}