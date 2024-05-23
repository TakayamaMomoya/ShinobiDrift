//*****************************************************
//
// �^�C���̏���[timer.h]
// Author:�X��x��
//
//*****************************************************

#ifndef _TIMER_H_
#define _TIMER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "number.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define MAX_PLACE	(10)	// �ő包��

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CTimer : public CObject
{
public:
	CTimer(int nPriority = 7);	// �R���X�g���N�^
	~CTimer();	// �f�X�g���N�^

	// �����o�֐�
	static CTimer* Create();	// ����

	HRESULT Init();
	void Uninit();
	void Update();
	void Sub(int nTime) { m_nSeconds -= nTime; }

private:
	//�����o�ϐ�
	int m_nSeconds;		// ���݂̎���
	int m_nCntSeconds;	// �J�E���g���Z
	CNumber* m_pNumber;	// �i���o�[�̃|�C���^
};
#endif