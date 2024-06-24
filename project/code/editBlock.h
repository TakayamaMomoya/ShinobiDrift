//*****************************************************
//
// �u���b�N�G�f�B�^�[�̏���[editBlock.h]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
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
	CStateCreateBlockNormal() : m_pObjectCursor(nullptr), m_nIdxObject(-1), m_type(CBlock::TYPE::TYPE_WALL), m_behaviour(CBlock::BEHAVIOUR::BEHAVIOUR_NORMAL) {};
	virtual ~CStateCreateBlockNormal() {};

	void Init(CEditBlock *pEdit) override;
	void Uninit(CEditBlock *pEdit) override;
	void Update(CEditBlock *pEdit) override;

private:
	void ChangeBlockBehaviour(void);
	void CreateBlock(D3DXVECTOR3 pos);
	CBlock *CheckDelete(void);

	int m_nIdxObject;
	CBlock::TYPE m_type;
	CObjectX *m_pObjectCursor;	// �J�[�\���̉��I�u�W�F�N�g
	CBlock::BEHAVIOUR m_behaviour;	// �u���b�N�̃r�w�C�r�A
};

class CStateEditGrabBlock : public CStateEditBlock
{// �͂ރu���b�N�̕ҏW
public:
	CStateEditGrabBlock() {};
	virtual ~CStateEditGrabBlock() {};

	// �����o�֐�
	void Init(CEditBlock *pEdit) override;
	void Uninit(CEditBlock *pEdit) override;
	void Update(CEditBlock *pEdit) override;

private:
	// �����o�֐�
	void SelectGrabBlock(void);
	void EditGrabBlock(void);

	// �����o�ϐ�
	std::list<CBlockGrab*>::iterator m_it;	// �C�e���[�^�[
};