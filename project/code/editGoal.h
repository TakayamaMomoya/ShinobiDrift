//*****************************************************
//
// �S�[���G�f�B�^�[�̏���[editGoal.h]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "edit.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEditGoal : public CEdit
{
public:
	CEditGoal();
	~CEditGoal();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

private:
};