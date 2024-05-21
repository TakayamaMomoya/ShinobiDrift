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

private:
	void LoopCursor(void);
	void CreateBlock(D3DXVECTOR3 pos);
	CBlock *CheckDelete(void);

	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	CObjectX *m_pObjectCursor;	// �J�[�\���̃I�u�W�F�N�gX�ւ̃|�C���^
	int m_nIdxObject;
	char m_aPath[256];
	CBlock::TYPE m_type;
};