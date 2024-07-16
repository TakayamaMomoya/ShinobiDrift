//*****************************************************
//
// �G�X�|�i�[[enemySpawner.h]
// Author:���R����
//
//*****************************************************
#ifndef _ENEMYSPAWNER_H_
#define _ENEMYSPAWNER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object3D.h"
#include "polygon3D.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemySpawner : public CObject3D
{
public:
	CEnemySpawner(int nPriority = 7);	// �R���X�g���N�^
	~CEnemySpawner();	//	�f�X�g���N�^

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �ʒu�擾
	void SetRotation(float fRot) { m_fRot = fRot; }	// �����擾�ݒ�
	float GetRotation() { return m_fRot; }	// �����擾����

	// �ÓI�����o�֐�
	static CEnemySpawner* Create(D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f }, float fRot = 0.0f, float fLength = 1000.0f);	// ����

private:
	// �����o�֐�
	void SetPolygon(void);

	// �����o�ϐ�
	int m_nTransitionTime;		// �J�ڎ���
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_posStart;	// �S�[���̎n�_
	D3DXVECTOR3 m_posEnd;	// �S�[���̏I�_
	float m_fRot;		// ����
	float m_fLength;	// ����
	CPolygon3D* m_pObj3D;	// �I�u�W�F�N�g3D�̃|�C���^
};

#endif
