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

	HRESULT Init(void);             // ����������
	void Uninit(void);              // �I������
	void Update(void);              // �X�V����
	void Draw(void);                // �`�揈��
	static CShuriken* Create(D3DXVECTOR3 pos);     // ��������

private:

	void MoveToPlyaer(void);  // �v���C���[�Ɍ������Ĉړ����鏈��

};

#endif