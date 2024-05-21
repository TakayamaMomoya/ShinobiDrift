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
#include <list>

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CMeshRoad : public CObject3D
{
public:
	CMeshRoad(int nPriority = 3);	// �R���X�g���N�^
	~CMeshRoad();	// �f�X�g���N�^

	static CMeshRoad *Create(void);
	static CMeshRoad *GetInstance(void) { return m_pMeshRoad; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddEdge(D3DXVECTOR3 pos, float fRot,bool bReCreateVtx = false);
	void CreateVtxBuffEdge(void);	// �G�b�W���ɉ����Ē��_�𐶐�����

private:
	struct SInfoEdge
	{// �ӂɕK�v�ȏ��
		D3DXVECTOR3 pos;
		float fRot;
		SInfoEdge() : pos({ 0.0f,0.0f,0.0f }), fRot(0.0f) {}
	};

	UINT m_nNumVtx;
	std::list<SInfoEdge> m_listEdge;
	static CMeshRoad *m_pMeshRoad;
};

#endif