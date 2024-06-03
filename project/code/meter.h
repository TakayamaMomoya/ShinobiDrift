//*****************************************************
//
// ���[�^�[[meter.h]
// Author:�X��x��
//
//*****************************************************

#ifndef _METER_H_
#define _METER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "number.h"
#include "player.h"
#include "UI.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define MAX_PLACE	(10)	// �ő包��

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CMeter : public CObject
{
public:
	CMeter(int nPriority = 7);	// �R���X�g���N�^
	~CMeter();	//	�f�X�g���N�^

	// �����o�֐�
	static CMeter* Create();	// ����

	HRESULT Init();
	void Uninit();
	void Update();
	void Acceleration();
	void Needle();

	// ���[�^�[�̎擾
	int GetMeter() { return m_NowMeter; }

	static CMeter* GetInstance() { return m_pMeter; }

private:
	//�����o�ϐ�
	int m_NowMeter;		// ���݂̃��[�^�[�l
	int m_nCntMeter;	// �J�E���g���Z
	int m_nIdxTexture;	// �e�N�X�`���ԍ�

	float m_fRot;		// ����

	CNumber* m_pNumber;	// �i���o�[�̃|�C���^
	CPlayer* m_pPlayer;	// �v���C���[�̃|�C���^
	CUI* m_pUI;			// UI�̃|�C���^
	static CMeter* m_pMeter;	// ���g�̃|�C���^
};

#endif
