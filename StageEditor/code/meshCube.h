//*****************************************************
//
// ���b�V���L���[�u[meshCube.h]
// Author:���R����
//
//*****************************************************
#ifndef _MESHCUBE_H_
#define _MESHCUBE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************

//*****************************************************
// �O����`
//*****************************************************
class CObject3D;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CMeshRoad : public CObject
{
public:
	struct SInfoRoadPoint
	{// ���[�h�|�C���g�ɕK�v�ȏ��
		D3DXVECTOR3 pos;	// �ʒu
		float fWidth;	// ��
		SInfoRoadPoint() : pos({ 0.0f,0.0f,0.0f }), fWidth(0.0f) {}
	};

	CMeshRoad(int nPriority = 3);	// �R���X�g���N�^
	~CMeshRoad();	// �f�X�g���N�^

	static CMeshRoad *Create(void);
	static CMeshRoad *GetInstance(void) { return m_pMeshRoad; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddRoadPoint(D3DXVECTOR3 pos,bool bReCreateVtx = false);
	void CreateVtxBuffEdge(void);	// �G�b�W���ɉ����Ē��_�𐶐�����

	void Save(void);	// �G�f�B�^�[�̂݁B�Q�[���ł͏����Ă�
	void Load(void);	// �G�f�B�^�[�̂݁B�Q�[���ł͏����Ă�

	bool CollisionRoad(D3DXVECTOR3* pPos, D3DXVECTOR3 posOld);

	std::vector<CMeshRoad::SInfoRoadPoint>::iterator SelectRoadPoint(void);
	std::vector<SInfoRoadPoint> *GetList(void) { return &m_aRoadPoint; }
	std::vector<CTunnel*> *GetArrayTunnnel(void) { return &m_aTunnel; }
	void DeleteEdge(std::vector<CMeshRoad::SInfoRoadPoint>::iterator it);
	void ResetIterator(void);

private:
	void SetNormal(VERTEX_3D *pVtx);	// �@���̐ݒ�
	void CreateSpline(void);	// �X�v���C���̐���
	void CreateSideSpline(void);	// ���ʂ̃X�v���C������
	void CreateVtxBetweenRoadPoint(SInfoRoadPoint infoRoadPoint,VERTEX_3D *pVtx, SInfoRoadPoint *infoRoadPointOld = nullptr,int nIdx = 0);	// ���[�h�|�C���g�Ԃ̒��_�̐ݒ�
	void SetEdgeAngle(VERTEX_3D *pVtx, D3DXVECTOR3 posEdge, D3DXVECTOR3 posEdgeOld);	// �ӂ̊p�x�̐ݒ�
	D3DXVECTOR3 GetPosEdge(D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2);

	UINT m_nNumVtx;
	std::vector<SInfoRoadPoint> m_aRoadPoint;
	std::vector<SInfoRoadPoint>::iterator m_it;
	CCutMullSpline *m_pSpline;	// �X�v���C��
	CCutMullSpline *m_pSplineL;	// �����̃X�v���C��
	CCutMullSpline *m_pSplineR;	// �E���̃X�v���C��
	std::vector<CTunnel*> m_aTunnel;	// �g���l���̃|�C���^�̔z��

	int m_effectNum;
	static CMeshRoad *m_pMeshRoad;	// ���g�̃|�C���^
};

namespace MeshRoad
{
const int NUM_EDGE_IN_ROADPOINT = 20;	// ���[�h�|�C���g��ɂ��A����ӂ̐�
const int NUM_VTX_IN_EDGE = 2;	// ��ӂɂ��钸�_��
}

#endif