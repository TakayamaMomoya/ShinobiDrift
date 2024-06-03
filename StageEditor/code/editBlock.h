//*****************************************************
//
// �u���b�N�G�f�B�^�[�̏���[editBlock.h]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "block.h"
#include "edit.h"

//*****************************************************
// �O���錾
//*****************************************************
class CObjectX;
class CStateEditBlock;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEditBlock : public CEdit
{
public:
	CEditBlock();	// �R���X�g���N�^
	~CEditBlock();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Save(void);
	void ChangeState(CStateEditBlock *pState);

private:
	char m_aPath[256];
	CStateEditBlock *m_pState;	// �X�e�C�g�̃|�C���^
};

//*****************************************************
// �X�e�C�g�N���X�̒�`
//*****************************************************
class CStateEditBlock
{// �u���b�N�G�f�B�b�g�̃X�e�C�g���N���X
public:
	CStateEditBlock() {};
	virtual ~CStateEditBlock() {};

	virtual void Init(CEditBlock *pEdit) = 0;
	virtual void Uninit(CEditBlock *pEdit) = 0;
	virtual void Update(CEditBlock *pEdit) = 0;
};

class CStateCreateBlockNormal : public CStateEditBlock
{// �ʏ�u���b�N�̐���
public:
	CStateCreateBlockNormal() : m_pObjectCursor(nullptr) {};
	virtual ~CStateCreateBlockNormal() {};

	void Init(CEditBlock *pEdit) override;
	void Uninit(CEditBlock *pEdit) override;
	void Update(CEditBlock *pEdit) override;

private:
	void CreateBlock(D3DXVECTOR3 pos);
	CBlock *CheckDelete(void);

	int m_nIdxObject;
	CBlock::TYPE m_type;
	CObjectX *m_pObjectCursor;	// �J�[�\���̉��I�u�W�F�N�g
};