//*****************************************************
//
// �藠���̏���[shuriken.h]
// Author:�匴�叫
//
//*****************************************************

#ifndef _SHURIKEN_H_
#define _SHURIKEN_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CShuriken : public CObjectX
{
public:
	CShuriken();	// �R���X�g���N�^
	~CShuriken();	                // �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);             // ����������
	void Uninit(void);              // �I������
	void Update(void);              // �X�V����
	void Draw(void);                // �`�揈��
	void Hit(float fDamage);	// �q�b�g����
	static CShuriken* Create(D3DXVECTOR3 pos);     // ��������

	// �ݒ�n
	static std::list<CShuriken*> GetList(void) { return m_aShuriken; }

private:
	// �����o�֐�
	void Debug(void);	// �f�o�b�O����

	// �����o�ϐ�
	float m_fLife;	// ����

	// �ÓI�����o�֐�
	static std::list<CShuriken*> m_aShuriken;  // �藠���̃��X�g
};

#endif