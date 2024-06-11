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
#include "myLib.h"
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
const int NUM_EDGE_IN_ROADPOINT = 10;	// ���[�h�|�C���g��ɂ��A����ӂ̐�
const char PATH_SAVE[] = "data\\MAP\\road00.bin";	// �ۑ��t�@�C���̃p�X
const char* PATH_TEXTURE = "data\\TEXTURE\\MATERIAL\\road.jpg";	// �e�N�X�`���p�X
const float DIST_DEFAULT = 200.0f;	// �f�t�H���g�̕ӊԂ̋���
const float WIDTH_ROAD = 600.0f;	// ���̕�
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
	m_pSpline = nullptr;
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
	m_listRoadPoint.clear();

	// �e�N�X�`���ǂݍ���
	int nIdx = Texture::GetIdx(PATH_TEXTURE);
	SetIdxTexture(nIdx);

	// �ǂݍ��ݏ���
	Load();

	m_it = m_listRoadPoint.begin();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CMeshRoad::Uninit(void)
{
	if (m_pSpline != nullptr)
	{
		delete m_pSpline;
		m_pSpline = nullptr;
	}

	/*if (m_pSplineXZ != nullptr)
	{
		delete m_pSplineXZ;
		m_pSplineXZ = nullptr;
	}

	if (m_pSplineXY != nullptr)
	{
		delete m_pSplineXY;
		m_pSplineXY = nullptr;
	}*/

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CMeshRoad::Update(void)
{
#ifdef _DEBUG
	for (SInfoRoadPoint info : m_listRoadPoint)
		CEffect3D::Create(info.pos, 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
#endif // _DEBUG
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

	// �J�����O�𖳌���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_nNumVtx - 2);

	// �J�����O��L����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	ImGui::Text("%d", m_nNumVtx);
}

//=====================================================
// ���[�h�|�C���g�̑I��
//=====================================================
std::vector<CMeshRoad::SInfoRoadPoint>::iterator CMeshRoad::SelectRoadPoint(void)
{
	if (ImGui::Button("NextEdge", ImVec2(70, 30)))
	{
		if(m_it != m_listRoadPoint.end() && std::next(m_it) != m_listRoadPoint.end())
			std::advance(m_it, 1);
	}
	if (ImGui::Button("PrevEdge", ImVec2(70, 30)))
	{
		if (m_it != m_listRoadPoint.begin())
			std::advance(m_it, -1);
	}

	CEffect3D::Create(m_it->pos, 100.0f, 3, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	return m_it;
}

//=====================================================
// ���[�h�|�C���g�̍폜
//=====================================================
void CMeshRoad::DeleteEdge(std::vector<CMeshRoad::SInfoRoadPoint>::iterator it)
{
	m_listRoadPoint.erase(it);

	CreateVtxBuffEdge();

	m_it = m_listRoadPoint.begin();
}

//=====================================================
// �C�e���[�^�[�̃��Z�b�g
//=====================================================
void CMeshRoad::ResetIterator(void)
{
	m_it = m_listRoadPoint.end() - 1;
}

//=====================================================
// ���[�h�|�C���g�̒ǉ�
//=====================================================
void CMeshRoad::AddRoadPoint(D3DXVECTOR3 pos, bool bReCreateVtx)
{
	// ���X�g�ɏ���ǉ�
	SInfoRoadPoint info;
	info.pos = pos;

	m_listRoadPoint.push_back(info);

	if(bReCreateVtx)	// ���[�h�|�C���g�ɉ��������_�̍Đ���
		CreateVtxBuffEdge();
}

//=====================================================
// ���[�h�|�C���g�ɉ��������_�̐���
//=====================================================
void CMeshRoad::CreateVtxBuffEdge(void)
{
	// �X�v���C���̍Đ���
	CreateSpline();

	// ���_�̐���
	m_nNumVtx = m_listRoadPoint.size() * NUM_VTX_IN_EDGE * NUM_EDGE_IN_ROADPOINT;
	CreateVtxBuff(m_nNumVtx);

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	std::vector<SInfoRoadPoint>::iterator itRoadPoint;
	int nIdx = 0;

	for (itRoadPoint = m_listRoadPoint.begin(); itRoadPoint != m_listRoadPoint.end(); itRoadPoint++)
	{
		if (itRoadPoint != m_listRoadPoint.begin())
		{
			SInfoRoadPoint *pInfoRoadPointOld = &*std::prev(itRoadPoint);

			// ���[�h�|�C���g�Ԃ̒��_�ݒ�
			CreateVtxBetweenRoadPoint(*itRoadPoint, pVtx, pInfoRoadPointOld, nIdx);
		}

		pVtx += NUM_EDGE_IN_ROADPOINT * NUM_VTX_IN_EDGE;

		nIdx++;
	}

	// ���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}

//=====================================================
// ���[�h�|�C���g�Ԃ̒��_�ݒ�
//=====================================================
void CMeshRoad::CreateVtxBetweenRoadPoint(SInfoRoadPoint infoRoadPoint, VERTEX_3D *pVtx, SInfoRoadPoint *pInfoRoadPointOld,int nIdx)
{
	if (pVtx == nullptr)
		assert(("CreateVtxBetweenRoadPoint�Œ��_���null�ł�", false));

	if (m_pSpline == nullptr)
		assert(("CreateVtxBetweenRoadPoint�ŃX�v���C����null�ł�", false));

	D3DXVECTOR3 posEdgeOld = {};	// �O��̕ӂ̈ʒu

	if (pInfoRoadPointOld != nullptr)
	{
		posEdgeOld = pInfoRoadPointOld->pos;
	}

	// ���[�h�|�C���g�ԂŕK�v�ȕ�
	for (int i = 0; i < NUM_EDGE_IN_ROADPOINT; i++)
	{
		D3DXVECTOR3 pos = infoRoadPoint.pos;

		if (pInfoRoadPointOld == nullptr)
		{// �O��̃��[�h�|�C���g���Ȃ��ꍇ�A�����͎�������
			pos = m_pSpline->Interpolate(pos.x,0);

			// �O��̕ӂƔ�ׂȂ����_�ʒu�ݒ�
			pVtx[0].pos = pos;
			pVtx[1].pos = pos;

			pVtx[0].pos.z -= WIDTH_ROAD;
			pVtx[1].pos.z += WIDTH_ROAD;

			posEdgeOld = GetPosEdge(pVtx[0].pos, pVtx[1].pos);	// �ӂ̈ʒu��ۑ�
		}
		else
		{
			float fDiff = infoRoadPoint.pos.x - pInfoRoadPointOld->pos.x;
			float fRate = ((float)i + 1.0f) / NUM_EDGE_IN_ROADPOINT;

			// ���W�̌���
			pos = m_pSpline->Interpolate(fRate, nIdx);

			if (i == 0)
			{
				pVtx[0].pos = pVtx[-2].pos;
				pVtx[1].pos = pVtx[-1].pos;

				pVtx[0].nor = pVtx[-2].nor;
				pVtx[1].nor = pVtx[-1].nor;
			}
			else
			{
				// �ӂ̊p�x�ݒ�
				SetEdgeAngle(pVtx, pos, posEdgeOld);
			}

			posEdgeOld =  GetPosEdge(pVtx[0].pos, pVtx[1].pos);	// �ӂ̈ʒu��ۑ�
		}

		// �@���̐ݒ�
		SetNormal(pVtx);

		// �e�N�X�`�����W�̐ݒ�
		if (i % 2 == 0)
		{
			pVtx[0].tex = { 0.0f,0.0f };
			pVtx[1].tex = { 1.0f,0.0f };
		}
		else
		{
			pVtx[0].tex = { 0.0f,1.0f };
			pVtx[1].tex = { 1.0f,1.0f };
		}

		pVtx += NUM_VTX_IN_EDGE;	// �ӂɂ��钸�_�����|�C���^��i�߂�
	}
}

//=====================================================
// �ӂ̊p�x��ݒ�
//=====================================================
void CMeshRoad::SetEdgeAngle(VERTEX_3D *pVtx, D3DXVECTOR3 posEdge, D3DXVECTOR3 posEdgeOld)
{
	if (pVtx == nullptr)
		return;

	// �����x�N�g������p�x���擾
	D3DXVECTOR3 vecDiff = posEdge - posEdgeOld;
	float fAngle = atan2f(vecDiff.x, vecDiff.z);
	
	fAngle += D3DX_PI * 0.5f;	// �p�x��90�x�X����
	universal::LimitRot(&fAngle);

	// �p�x����ɍ��W�Œ��_�ʒu������
	D3DXVECTOR3 vecPole = universal::PolarCoordinates(D3DXVECTOR3(D3DX_PI * 0.5f, fAngle, 0.0f));

	pVtx[0].pos = posEdge + vecPole * WIDTH_ROAD;
	pVtx[1].pos = posEdge - vecPole * WIDTH_ROAD;
}

//=====================================================
// �ӂ̈ʒu���擾
//=====================================================
D3DXVECTOR3 CMeshRoad::GetPosEdge(D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2)
{
	D3DXVECTOR3 vecDiff = vtx2 - vtx1;

	D3DXVECTOR3 posEdge = vtx1 + vecDiff * 0.5f;

	return posEdge;
}

//=====================================================
// �@���̐ݒ�
//=====================================================
void CMeshRoad::SetNormal(VERTEX_3D *pVtx)
{
	if (pVtx == nullptr)
		return;

	// ���_�ʒu
	D3DXVECTOR3 vtxLu = pVtx[-NUM_VTX_IN_EDGE].pos;
	D3DXVECTOR3 vtxRu = pVtx[0].pos;
	D3DXVECTOR3 vtxRd = pVtx[1].pos;

	// ���_�ǂ����̍����x�N�g������ӂ��Z�o
	D3DXVECTOR3 edge1 = vtxLu - vtxRu;
	D3DXVECTOR3 edge2 = vtxRd - vtxRu;

	// ��ӂ̊O�ς���@�����Z�o
	D3DXVECTOR3 nor;
	D3DXVec3Cross(&nor, &edge1, &edge2);

	D3DXVec3Normalize(&nor, &nor);	// �@���𐳋K��

	// �@����K�p
	pVtx[0].nor = { 0.0f,1.0f,0.0f };
	pVtx[1].nor = { 0.0f,1.0f,0.0f };
}

//=====================================================
// �X�v���C���̐���
//=====================================================
void CMeshRoad::CreateSpline(void)
{
	if (m_pSpline != nullptr)
	{// �X�v���C�������ɂ�������j��
		delete m_pSpline;
		m_pSpline = nullptr;
	}

	m_pSpline = new CCutMullSpline;

	if (m_pSpline != nullptr)
	{
		// �f�[�^�_�̃x�N�^�[�p��
		std::vector<D3DXVECTOR3> vPos;

		// �x�N�^�[��K�v�ȃT�C�Y�ɒ���
		int nSize = m_listRoadPoint.size();
		vPos.resize(nSize);
		
		for (int i = 0; i < nSize; i++)
		{
			vPos[i] = m_listRoadPoint[i].pos;
		}
		
		// �X�v���C���̏�����
		m_pSpline->Init(vPos);
	}
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
	size_t size = m_listRoadPoint.size();
	outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

	// ���X�g�̏��ۑ�
	outputFile.write(reinterpret_cast<const char*>(m_listRoadPoint.data()), sizeof(SInfoRoadPoint) * size);

	outputFile.close();
}

//=====================================================
// �ǂݍ��ݏ���
//=====================================================
void CMeshRoad::Load(void)
{
	m_listRoadPoint.clear();

	// �t�@�C�����J��
	std::ifstream inputFile(PATH_SAVE, std::ios::binary);

	if (!inputFile.is_open())
		assert(("���b�V�����[�h�̃t�@�C�����J���܂���ł���", false));

	// �f�[�^���ǂݍ���
	size_t size;
	inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
	m_listRoadPoint.resize(size);

	// �Ӄf�[�^�ǂݍ���
	inputFile.read(reinterpret_cast<char*>(m_listRoadPoint.data()), sizeof(SInfoRoadPoint) * size);

	inputFile.close();

	CreateVtxBuffEdge();
}

namespace MeshRoad
{
CMeshRoad *GetInstance(void)
{
	CMeshRoad *pMeshRoad = CMeshRoad::GetInstance();

	if (pMeshRoad == nullptr)
		assert(("meshroad���Ȃ���`�`", false));

	return pMeshRoad;
}
}