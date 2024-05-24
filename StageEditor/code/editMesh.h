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
};

class CStateEditMeshCurve : public CStateEditMesh
{// �J�[�u�̒���
public:
	CStateEditMeshCurve();
	virtual ~CStateEditMeshCurve() {};

	void Update(CEditMesh *pEdit) override;

private:
	void SetEdge(std::vector<CMeshRoad::SInfoEdge>::iterator it);
	void SetCurve(void);

	std::vector<CMeshRoad::SInfoEdge>::iterator m_itStart;	// �J�[�u�̊J�n�C�e���C�^�[
	bool m_bStart;	// �ŏ��̕ӂ�ݒu�������ǂ���
	std::vector<CMeshRoad::SInfoEdge>::iterator m_itEnd;	// �J�[�u�̏I���C�e���C�^�[
	bool m_bEnd;	// �Ō�̕ӂ�ݒu�������ǂ���
	float m_fAngleCurve;	// �J�[�u�̊p�x
};

class CStateEditMeshDeleteEdge : public CStateEditMesh
{// �ӂ̍폜
public:
	CStateEditMeshDeleteEdge() {};
	virtual ~CStateEditMeshDeleteEdge() {};

	void Update(CEditMesh *pEdit) override;
};