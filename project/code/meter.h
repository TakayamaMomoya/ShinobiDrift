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
	void Deceleration();

private:
	//�����o�ϐ�
	float m_nMeter;		// ���݂̃��[�^�[�l
	int m_nCntMeter;	// �J�E���g���Z
	CNumber* m_pNumber;	// �i���o�[�̃|�C���^
	CPlayer* m_pPlayer;	// �v���C���[�̃|�C���^
};
#endif
