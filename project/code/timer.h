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
#include "gameObject.h"
#include "number.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CTimer : public CGameObject
{
public:
	CTimer();	// �R���X�g���N�^
	~CTimer();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

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
	// �񋓌^��`
	enum E_Number
	{// �����̎��
		NUMBER_MINUTE = 0,	// ��
		NUMBER_SECOND,	// �b
		NUMBER_MILLI,	// �~���b
		NUMBER_MAX
	};

	// �����o�֐�
	void UpdateNumber();	// �����̍X�V

	// �����o�ϐ�
	float m_fSecond;			// ���݂̎���(�b)
	bool m_bStop;				// �^�C�}�[��~�̃t���O
	vector<CNumber*> m_aNumber;	// �����̔z��
};

#endif
