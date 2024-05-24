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
#include <fstream>

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const UINT NUMVTX_NOTDRAW = 4;	// ���̒��_�������̏ꍇ�A�`�悵�Ȃ�
const float WIDTH_DEFAULT = 200.0f;	// �f�t�H���g�̕�
const float LENGTH_DEFAULT = 200.0f;	// �f�t�H���g�̒���
const int NUM_VTX_IN_EDGE = 2;	// ��ӂɂ��钸�_��
const char PATH_SAVE[] = "data\\MAP\\road00.bin";	// �ۑ��t�@�C���̃p�X
const char* PATH_TEXTURE = "data\\TEXTURE\\MATERIAL\\road.jpg";	// �e�N�X�`���p�X
const float DIST_DEFAULT = 200.0f;	// �f�t�H���g�̕ӊԂ̋���
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

	// �e�N�X�`���ǂݍ���
	int nIdx = Texture::GetIdx(PATH_TEXTURE);
	SetIdxTexture(nIdx);

	// �ǂݍ��ݏ���
	Load();

	m_it = m_listEdge.begin();

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
	LPDIRECT3DTEXTURE9 pTexture = Texture::GetTexture(nIdxTexture);
	pDevice->SetTexture(0, pTexture);

	// �`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_nNumVtx - 2);
}

//=====================================================
// �ӂ̑I��
//=====================================================
std::vector<CMeshRoad::SInfoEdge>::iterator CMeshRoad::SelectEdge(void)
{
	if (ImGui::Button("NextEdge", ImVec2(70, 30)))
	{
		if(m_it != m_listEdge.end() && std::next(m_it) != m_listEdge.end())
			std::advance(m_it, 1);
	}
	if (ImGui::Button("PrevEdge", ImVec2(70, 30)))
	{
		if (m_it != m_listEdge.begin())
			std::advance(m_it, -1);
	}

	return m_it;
}

//=====================================================
// �ӂ̍폜
//=====================================================
void CMeshRoad::DeleteEdge(std::vector<CMeshRoad::SInfoEdge>::iterator it)
{
	m_listEdge.erase(it);

	CreateVtxBuffEdge();

	m_it = m_listEdge.begin();
}

//=====================================================
// �C�e���[�^�[�̃��Z�b�g
//=====================================================
void CMeshRoad::ResetIterator(void)
{
	m_it = m_listEdge.begin();
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

	// �ŏ��̃e�N�X�`�����W�ݒ�
	pVtx[0].tex = { 0.0f,0.0f };
	pVtx[1].tex = { 1.0f,0.0f };

	float fRateUp = 0.0f;
	float fRateDown = 0.0f;

	// ���_�ʒu��ӂɍ��킹��
	int nCntEdge = 0;
	for (const auto& edge : m_listEdge)
	{
		int nIdx = nCntEdge * NUM_VTX_IN_EDGE;	// ���_�̔ԍ��v�Z

		// ���_�ʒu�̌v�Z
		D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, edge.fRot, 0.0f));

		pVtx[nIdx].pos = edge.pos + vecPole * WIDTH_DEFAULT;
		pVtx[nIdx + 1].pos = edge.pos - vecPole * WIDTH_DEFAULT;

		// �@���̌v�Z
		if (nCntEdge != 0)
		{// �ŏ��̕ӈȊO��ݒ肷��
			SetNormal(pVtx, nIdx);
		}

		// �e�N�X�`�����W�̐ݒ�
		if (nCntEdge > 0)
		{// �ŏ��̕ӈȊO�̓e�N�X�`�����W�𑫂��Ă���
			// �f�t�H���g�̋��������ƂɑO��̕ӂ���ǂ̂��炢����Ă��邩�v�Z
			int nIdxOld = nIdx - NUM_VTX_IN_EDGE;	// �ЂƂO�̕ӂ̒��_�ԍ�

			// ���_�ʒu
			D3DXVECTOR3 vtxLu = pVtx[nIdxOld].pos;
			D3DXVECTOR3 vtxLd = pVtx[nIdxOld + 1].pos;
			D3DXVECTOR3 vtxRu = pVtx[nIdx].pos;
			D3DXVECTOR3 vtxRd = pVtx[nIdx + 1].pos;

			// �㉺�̕ӂ̒������v�Z
			D3DXVECTOR3 vecDiffUp = vtxLu - vtxRu;
			D3DXVECTOR3 vecDiffDown = vtxLd - vtxRd;
			float fDistUp = D3DXVec3Length(&vecDiffUp);
			float fDistDown = D3DXVec3Length(&vecDiffDown);

			fRateUp += fDistUp / DIST_DEFAULT;
			fRateDown += fDistDown / DIST_DEFAULT;

			pVtx[nIdx].tex = { 0.0f,fRateUp };
			pVtx[nIdx + 1].tex = { 1.0f,fRateDown };
		}
		else
		{// ��̎�
		}

		nCntEdge++;
	}

	// �ŏ��̕ӂƓ�Ԗڂ̕ӂ̖@�������킹��
	pVtx[0].nor = pVtx[NUM_VTX_IN_EDGE].nor;
	pVtx[1].nor = pVtx[NUM_VTX_IN_EDGE + 1].nor;

	// ���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}

//=====================================================
// �@���̐ݒ�
//=====================================================
void CMeshRoad::SetNormal(VERTEX_3D *pVtx, int nIdx)
{
	if (pVtx == nullptr)
		return;

	int nIdxOld = nIdx - NUM_VTX_IN_EDGE;	// �ЂƂO�̕ӂ̒��_�ԍ�

	// ���_�ʒu
	D3DXVECTOR3 vtxLu = pVtx[nIdxOld].pos;
	D3DXVECTOR3 vtxRu = pVtx[nIdx].pos;
	D3DXVECTOR3 vtxRd = pVtx[nIdx + 1].pos;

	// ���_�ǂ����̍����x�N�g������ӂ��Z�o
	D3DXVECTOR3 edge1 = vtxLu - vtxRu;
	D3DXVECTOR3 edge2 = vtxRd - vtxRu;

	// ��ӂ̊O�ς���@�����Z�o
	D3DXVECTOR3 nor;
	D3DXVec3Cross(&nor, &edge1, &edge2);

	D3DXVec3Normalize(&nor, &nor);	// �@���𐳋K��

	// �@����K�p
	pVtx[nIdx].nor = nor;
	pVtx[nIdx + 1].nor = nor;
}

//=====================================================
// �ۑ�����
//=====================================================
void CMeshRoad::Save(void)
{
	// �t�@�C�����J��
	std::ofstream outputFile(PATH_SAVE, std::ios::binary);

	if (!outputFile.is_open())
		assert(("���b�V�����[�h�̃t�@�C�����J���܂���ł���", false));
	
	// ��񐔕ۑ�
	size_t size = m_listEdge.size();
	outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

	// ���X�g�̏��ۑ�
	outputFile.write(reinterpret_cast<const char*>(m_listEdge.data()), sizeof(SInfoEdge) * size);

	outputFile.close();
}

//=====================================================
// �ǂݍ��ݏ���
//=====================================================
void CMeshRoad::Load(void)
{
	m_listEdge.clear();

	// �t�@�C�����J��
	std::ifstream inputFile(PATH_SAVE, std::ios::binary);

	if (!inputFile.is_open())
		assert(("���b�V�����[�h�̃t�@�C�����J���܂���ł���", false));

	// �f�[�^���ǂݍ���
	size_t size;
	inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
	m_listEdge.resize(size);

	// �Ӄf�[�^�ǂݍ���
	inputFile.read(reinterpret_cast<char*>(m_listEdge.data()), sizeof(SInfoEdge) * size);

	inputFile.close();

	CreateVtxBuffEdge();
}

namespace MeshRoad
{
CMeshRoad *GetInstance(void)
{
	CMeshRoad *pMeshRoad = CMeshRoad::GetInstance();

	if (pMeshRoad == nullptr)
		assert("meshroad���Ȃ���`�`", false);

	return pMeshRoad;
}
}