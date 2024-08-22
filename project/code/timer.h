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
#include "number.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CTimer : public CObject
{
public:
	CTimer();	// �R���X�g���N�^
	~CTimer();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init();
	void Uninit();
	void Update();

	void Minutes();
	void Second();
	void MilliSecond();

	// �ϐ��擾�E�ݒ�֐�
	float GetSecond() { return m_fSecond; }	// �b
	void SetSecond(float fSecond) { m_fSecond = fSecond; }
	void AddSecond(float fSecond) { m_fSecond += fSecond; }
	bool GetFlag() { return m_bStop; }	// ����t���O
	void SetFlag(bool bStop) { m_bStop = bStop; }

	// �ÓI�����o�֐�
	static CTimer *Create();	// ����

private:
	// �����o�ϐ�
	float m_fSecond;			// ���݂̎���(�b)
	bool m_bStop;				// �^�C�}�[��~�̃t���O
	CNumber* m_pMinutes;		// ���\���̃|�C���^
	CNumber* m_pSecond;			// �b�\���̃|�C���^
	CNumber* m_pMilli;			// �~���b�\���̃|�C���^
};

#endif
