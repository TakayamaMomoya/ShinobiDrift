//*****************************************************
//
// ���b�V���G�f�B�^�[�̏���[editMesh.h]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "edit.h"
#include <vector>
#include <list>
#include "meshRoad.h"

//*****************************************************
// �O���錾
//*****************************************************
class CObject3D;
class CObjectX;
class CStateEditMesh;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEditMesh : public CEdit
{
public:
	CEditMesh();
	~CEditMesh();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void ChangeState(CStateEditMesh *pState);

private:
	CObject3D *m_pMesh;	// ���b�V���̃|�C���^
	CObjectX *m_pManipulator;	// �}�j�s�����[�^�[
	CStateEditMesh *m_pState;	// �X�e�C�g
};

class CStateEditMesh
{// ���b�V���G�f�B�b�g�̃X�e�C�g���N���X
public:
	CStateEditMesh() {};
	virtual ~CStateEditMesh() {};

	virtual void Update(CEditMesh *pEdit) = 0;
};

class CStateEditMeshCreateMesh : public CStateEditMesh
{// ���b�V���̐���
public:
	CStateEditMeshCreateMesh() {};
	virtual ~CStateEditMeshCreateMesh() {};

	void Update(CEditMesh *pEdit) override;

private:
	void LimitPos(D3DXVECTOR3 *pPos);
};

class CStateEditMeshDeleteEdge : public CStateEditMesh
{// �ӂ̍폜
public:
	CStateEditMeshDeleteEdge();
	virtual ~CStateEditMeshDeleteEdge() {};

	void Update(CEditMesh *pEdit) override;
};