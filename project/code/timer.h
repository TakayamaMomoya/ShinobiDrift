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

	void Minutes();
	void Second();
	void MilliSecond();

	static CTimer* GetInstance() { return s_pTimer; }	// ���g�̏��擾

private:
	//�����o�ϐ�
	float m_fSecond;			// ���݂̎���(�b)
	float m_fMilli;				// ���݂̎���(�~���b)

	CNumber* m_pMinutes;		// ���\���̃|�C���^
	CNumber* m_pSecond;			// �b�\���̃|�C���^
	CNumber* m_pMilli;			// �~���b�\���̃|�C���^

	static CTimer* s_pTimer;	// ���g�̃|�C���^
};

#endif
