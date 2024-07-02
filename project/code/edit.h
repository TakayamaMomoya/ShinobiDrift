//*****************************************************
//
// �G�f�B�^�[�̏���[edit.h]
// Author:���R����
//
//*****************************************************
#ifndef _EDIT_H_
#define _EDIT_H_

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEdit
{
public:
	CEdit();	// �R���X�g���N�^
	~CEdit();	// �f�X�g���N�^

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void TeleportPlayer(void);
	bool IsAbove(void) { return s_bAbove; }	// ��󎋓_���ǂ����擾
	D3DXVECTOR3 GetPosAbove(void) { return s_posAbove; }	// ��󎋓_�ʒu

private:
	// �����o�֐�
	void InputAbove(void);	// ��󎋓_�̑���

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	static bool s_bAbove;	// ��󎋓_�ɂ��邩�ǂ���
	static D3DXVECTOR3 s_posAbove;	// ��󎋓_�̍��W
};

#endif