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
#include "inputkeyboard.h"
#include "debugproc.h"

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
	m_pSplineXZ = nullptr;
	m_pSplineXY = nullptr;
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

#ifdef _DEBUG
	EnableWire(true);
#endif // _DEBUG
	
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
	if (m_pSplineXZ != nullptr)
	{
		delete m_pSplineXZ;
		m_pSplineXZ = nullptr;
	}

	if (m_pSplineXY != nullptr)
	{
		delete m_pSplineXY;
		m_pSplineXY = nullptr;
	}

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

	if (CInputKeyboard::GetInstance() != nullptr)
	{
		if (CInputKeyboard::GetInstance()->GetTrigger(DIK_I))
		{// ������@�ύX
			m_effectNum += 1;
		}

		if (CInputKeyboard::GetInstance()->GetTrigger(DIK_K))
		{// ������@�ύX
			m_effectNum -= 1;
		}

		if (m_effectNum < 0)
			m_effectNum = 0;

		/*if (m_effectNum > NUM_EDGE_IN_ROADPOINT - 1)
			m_effectNum = NUM_EDGE_IN_ROADPOINT - 1;*/
	}
	CDebugProc::GetInstance()->Print("\n�G�t�F�N�g�ʒu[%d]", m_effectNum);

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
	D3DXVECTOR3 rot = GetRotation();

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
	m_it = m_listRoadPoint.begin();
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

	for (itRoadPoint = m_listRoadPoint.begin(); itRoadPoint != m_listRoadPoint.end(); itRoadPoint++)
	{
		if (itRoadPoint != m_listRoadPoint.begin())
		{
			SInfoRoadPoint *pInfoRoadPointOld = &*std::prev(itRoadPoint);

			// ���[�h�|�C���g�Ԃ̒��_�ݒ�
			CreateVtxBetweenRoadPoint(*itRoadPoint, pVtx, pInfoRoadPointOld);
		}

		pVtx += NUM_EDGE_IN_ROADPOINT * NUM_VTX_IN_EDGE;
	}

	// ���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}

//=====================================================
// ���[�h�|�C���g�Ԃ̒��_�ݒ�
//=====================================================
void CMeshRoad::CreateVtxBetweenRoadPoint(SInfoRoadPoint infoRoadPoint, VERTEX_3D *pVtx, SInfoRoadPoint *pInfoRoadPointOld)
{
	if (pVtx == nullptr)
		assert(("CreateVtxBetweenRoadPoint�Œ��_���null�ł�", false));

	if (m_pSplineXZ == nullptr || m_pSplineXY == nullptr)
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
			float z = (float)m_pSplineXZ->Interpolate(pos.x);
			pos.z = z;

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
			float fRate = (float)i / NUM_EDGE_IN_ROADPOINT;

			// X���W�̌���
			pos.x = pInfoRoadPointOld->pos.x + fRate * fDiff;
			
			// Y���W�̌���
			float y = (float)m_pSplineXY->Interpolate(pos.x);
			pos.y = y;

			// Z���W�̌v�Z
			float z = (float)m_pSplineXZ->Interpolate(pos.x);
			pos.z = z;

			CEffect3D::Create(pos, 50.0f, 60, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));	// ���S���W�̃G�t�F�N�g

			if (i == 0)
			{
				pVtx[0].pos = pVtx[-2].pos;
				pVtx[1].pos = pVtx[-1].pos;
			}
			else
			{
				// �ӂ̊p�x�ݒ�
				SetEdgeAngle(pVtx, pos, posEdgeOld);
			}

			posEdgeOld = GetPosEdge(pVtx[0].pos, pVtx[1].pos);	// �ӂ̈ʒu��ۑ�
		}

		// �@���̐ݒ�
		SetNormal(pVtx);

		pVtx[0].nor;
		pVtx[1].nor;

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
	pVtx[0].nor = nor;
	pVtx[1].nor = nor;
}

//=====================================================
// �X�v���C���̐���
//=====================================================
void CMeshRoad::CreateSpline(void)
{
	if (m_pSplineXZ != nullptr)
	{// �X�v���C�������ɂ�������j��
		delete m_pSplineXZ;
		m_pSplineXZ = nullptr;
	}

	if (m_pSplineXY != nullptr)
	{// �X�v���C�������ɂ�������j��
		delete m_pSplineXY;
		m_pSplineXY = nullptr;
	}

	m_pSplineXZ = new CSpline;
	m_pSplineXY = new CSpline;

	if (m_pSplineXZ != nullptr && m_pSplineXY != nullptr)
	{
		// �f�[�^�_�̃x�N�^�[�p��
		std::vector<double> x;
		std::vector<double> y;
		std::vector<double> z;

		// �x�N�^�[��K�v�ȃT�C�Y�ɒ���
		int nSize = m_listRoadPoint.size();
		x.resize(nSize);
		y.resize(nSize);
		z.resize(nSize);
		
		for (int i = 0; i < nSize; i++)
		{
			x[i] = m_listRoadPoint[i].pos.x;
			y[i] = m_listRoadPoint[i].pos.y;
			z[i] = m_listRoadPoint[i].pos.z;
		}
		
		// �X�v���C���̏�����
		m_pSplineXZ->Init(x, z);
		m_pSplineXY->Init(x, y);
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

//=====================================================
// �����蔻�菈��
//=====================================================
bool CMeshRoad::CollisionRoad(D3DXVECTOR3* pPos, D3DXVECTOR3 posOld)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	VERTEX_3D* pVtx;
	float fHeight = pPos->y;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int effectNum = 0;

#ifdef _DEBUG
	if (CInputKeyboard::GetInstance() != nullptr)
	{
		if (CInputKeyboard::GetInstance()->GetTrigger(DIK_L))
		{// ������@�ύX
			m_effectNum += 0;
		}
	}
#endif

	for (auto itRoadPoint : m_listRoadPoint)
	{
		for (int i = 0; i < NUM_EDGE_IN_ROADPOINT; i++)
		{
			/*if (pVtx[0].pos != pVtx[1].pos &&
				pVtx[0].pos != pVtx[2].pos &&
				pVtx[1].pos != pVtx[3].pos &&
				pVtx[2].pos != pVtx[3].pos && 
				D3DXVec3Length(&pVtx[0].nor) != 0.0f &&
				D3DXVec3Length(&pVtx[1].nor) != 0.0f &&
				D3DXVec3Length(&pVtx[2].nor) != 0.0f &&
				D3DXVec3Length(&pVtx[3].nor) != 0.0f)*/
			{
				if (universal::IsOnPolygon(pVtx[0].pos, pVtx[1].pos, pVtx[2].pos, pVtx[3].pos, pVtx[0].nor, pVtx[3].nor, *pPos, posOld, fHeight))
				{
					pPos->y = fHeight;

					// ���_�o�b�t�@���A�����b�N
					pVtxBuff->Unlock();

					return true;
				}
			}
			//else
			{
				/*D3DXVECTOR3 effpocCenter = pVtx[0].pos + pVtx[1].pos + pVtx[2].pos + pVtx[3].pos;
				CEffect3D::Create(effpocCenter * 0.25f, 100.0f, 5, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));*/
			}
			
#ifdef _DEBUG
			if (m_effectNum == effectNum)
			{
				CEffect3D::Create(pVtx[0].pos, 50.0f, 5, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));
				CEffect3D::Create(pVtx[1].pos, 50.0f, 5, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f));
				CEffect3D::Create(pVtx[2].pos, 50.0f, 5, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f));
				CEffect3D::Create(pVtx[3].pos, 50.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
			effectNum++;
#endif

			pVtx += NUM_VTX_IN_EDGE;
		}
	}

	// ���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();

	return false;
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