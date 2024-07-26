//*****************************************************
//
// ���[�^�[[meter.h]
// Author:�X��x��
//
//*****************************************************

#ifndef _METER_H_
#define _METER_H_

//*****************************************************
// �O���錾
//*****************************************************
class CNumber;
class CUI;

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CMeter : public CObject
{
public:
	CMeter(int nPriority = 7);	// �R���X�g���N�^
	~CMeter();	//	�f�X�g���N�^

	// �����o�֐�
	HRESULT Init();
	void Uninit();
	void Update();

	// �ϐ��擾�E�ݒ�֐�
	int GetMeter() { return m_NowMeter; }	// ���[�^�[�l

	// �ÓI�����o�֐�
	static CMeter* Create();	// ����
	static CMeter* GetInstance() { return m_pMeter; }	// �C���X�^���X�擾

private:
	// �����o�֐�
	void Acceleration();
	void Needle();

	//�����o�ϐ�
	int m_NowMeter;		// ���݂̃��[�^�[�l
	int m_nCntMeter;	// �J�E���g���Z
	float m_fRot;		// ����
	CNumber* m_pNumber;	// �i���o�[�̃|�C���^
	CUI* m_pNeedle;			// �jUI�̃|�C���^
	CUI* m_pBackMeter;			// ���[�^�[�w�i�̃|�C���^
	static CMeter* m_pMeter;	// ���g�̃|�C���^
};

#endif
