//*****************************************************
//
// UI�̏���[UI.h]
// Author:���R����
//
//*****************************************************
#ifndef _UI_H_
#define _UI_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "polygon2D.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CUI	: public CPolygon2D
{
public:
	CUI(int nPriority = 6);	// �R���X�g���N�^
	~CUI();	//	�f�X�g���N�^

	// �����o�֐�
	static CUI *Create(void);	// ��������
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	// �ϐ��擾�E�ݒ�֐�
	void SetSize(float width, float height) override;	// �T�C�Y
	D3DXVECTOR2 GetSize(void) override;
	virtual void SetPosition(D3DXVECTOR3 pos);	// �ʒu
	virtual D3DXVECTOR3 GetPosition(void);

private:
};

#endif