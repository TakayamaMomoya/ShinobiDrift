//*****************************************************
//
// �X�J�C�{�b�N�X�̏���[skybox.h]
// Author:���R����
//
//*****************************************************

#ifndef _SKYBOX_H_
#define _SKYBOX_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CSkybox : public CObjectX
{
public:
	CSkybox(int nPriority = 2);	// �R���X�g���N�^
	~CSkybox();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ϐ��擾�E�ݒ�֐�
	void EnableFollowPlayer(bool bFollowPlayer) { m_bFollowPlayer = bFollowPlayer; }	// �v���C���[�Ǐ]�t���O

	// �ÓI�����o�֐�
	static CSkybox *Create();
	static CSkybox *GetInstance() { return s_pSkybox; }	// �C���X�^���X�̎擾

private:
	// �����o�֐�
	void FollowPlayer(void);	// �v���C���[�̒Ǐ]
	void DetectionChangeTexture(void);	// �e�N�X�`���ύX�̌��m

	// �����o�ϐ�
	bool m_bFollowPlayer;	// �v���C���[�Ǐ]�t���O

	// �ÓI�����o�ϐ�
	static CSkybox *s_pSkybox;	// ���g�̃|�C���^
};

#endif

