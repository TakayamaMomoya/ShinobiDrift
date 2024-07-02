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

	static CTimer* GetInstance() { return m_pTimer; }	// ���g�̏��擾

private:
	//�����o�ϐ�
	float m_fSeconds;		// ���݂̎���
	CNumber* m_pNumber;	// �i���o�[�̃|�C���^

	static CTimer* m_pTimer;	// ���g�̃|�C���^
};
#endif
