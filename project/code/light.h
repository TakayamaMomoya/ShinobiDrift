//*****************************************************
//
// ���C�g�̏���[light.h]
// Author:���R����
//
//*****************************************************
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define MAX_LIGHT				(3)			//���C�g�̍ő吔

//*****************************************************
// �N���X��`
//*****************************************************
class CLight : public CObject
{
public:
	CLight();	// �R���X�g���N
	~CLight();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void EnableLight(bool bFrag);	// ���C�g�g�p�t���O

	// �ϐ��擾�E�ݒ�֐�
	void SetLightInfo(D3DLIGHT9 light);	// ���C�g���
	D3DLIGHT9 GetLightInfo(void) { return m_light; }

	// �ÓI�����o�֐�
	static CLight *Create(void);	// ��������
	static void ReleaseAll(void);	// �S���C�g�폜

private:
	// �����o�ϐ�
	D3DLIGHT9 m_light;	// ���C�g���
	int m_nID;	// ���ʔԍ�

	// �ÓI�����o�ϐ�
	static int s_nNumAll;	// ����
	static vector<CLight*> s_aLight;	// ���C�g���̊i�[�p�z��
};

#endif