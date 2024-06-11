//*****************************************************
//
// ���b�V�����̏���[meshRoad.h]
// Author:���R����
//
//*****************************************************

#ifndef _MESHROAD_H_
#define _MESHROAD_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "object3D.h"
#include <vector>

//*****************************************************
// �O����`
//*****************************************************
class CCutMullSpline;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CMeshRoad : public CObject3D
{
public:
	struct SInfoRoadPoint
	{// �ӂɕK�v�ȏ��
		D3DXVECTOR3 pos;
		SInfoRoadPoint() : pos({ 0.0f,0.0f,0.0f }) {}
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

	bool CollisionRoad(D3DXVECTOR3* pPos);

	void Save(void);	// �G�f�B�^�[�̂݁B�Q�[���ł͏����Ă�
	void Load(void);	// �G�f�B�^�[�̂݁B�Q�[���ł͏����Ă�

	std::vector<CMeshRoad::SInfoRoadPoint>::iterator SelectEdge(void);
	std::vector<SInfoRoadPoint> *GetList(void) { return &m_listRoadPoint; }
	void DeleteEdge(std::vector<CMeshRoad::SInfoRoadPoint>::iterator it);
	void ResetIterator(void);

private:
	void SetNormal(VERTEX_3D *pVtx);	// �@���̐ݒ�
	void CreateSpline(void);	// �X�v���C���̐���
	void CreateVtxBetweenRoadPoint(SInfoRoadPoint infoRoadPoint, VERTEX_3D *pVtx, SInfoRoadPoint *infoRoadPointOld = nullptr, int nIdx = 0);	// ���[�h�|�C���g�Ԃ̒��_�̐ݒ�
	void SetEdgeAngle(VERTEX_3D *pVtx, D3DXVECTOR3 posEdge, D3DXVECTOR3 posEdgeOld);	// �ӂ̊p�x�̐ݒ�
	D3DXVECTOR3 GetPosEdge(D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2);

	UINT m_nNumVtx;
	std::vector<SInfoRoadPoint> m_listRoadPoint;
	std::vector<SInfoRoadPoint>::iterator m_it;
	CCutMullSpline *m_pSpline;	// �X�v���C��

	int m_effectNum;
	static CMeshRoad *m_pMeshRoad;
};

namespace MeshRoad
{
CMeshRoad *GetInstance(void);
}

#endif