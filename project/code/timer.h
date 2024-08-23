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
// �O���錾
//*****************************************************
class CUI;

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

	// �ϐ��擾�E�ݒ�֐�
	float GetSecond() { return m_fSecond; }	// �b
	void SetSecond(float fSecond) { m_fSecond = fSecond; }
	void AddSecond(float fSecond) { m_fSecond += fSecond; }
	bool GetFlag() { return m_bStop; }	// ����t���O
	void SetFlag(bool bStop) { m_bStop = bStop; }
	void SetPosition(D3DXVECTOR3 pos) override;	// �ʒu
	void SetScaleNumber(float fScale);	// �����̃X�P�[��
	float GetScaleNumber(void) { return m_fScaleNumber; }

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
	void TransformNumber();	// �����̃g�����X�t�H�[���ݒ�

	// �����o�ϐ�
	float m_fSecond;			// ���݂̎���(�b)
	float m_fScaleNumber;	// �����̃X�P�[��
	bool m_bStop;				// �^�C�}�[��~�̃t���O
	vector<CNumber*> m_aNumber;	// �����̔z��
	vector<CUI*> m_aColon;	// �R�����̔z��
};

#endif
