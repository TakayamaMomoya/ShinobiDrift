//*****************************************************
//
// ���U���g����[result.h]
// Author:���R����
//
//*****************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;
class CStateResult;
class CNumber;
class CTimer;
class CPolygon2D;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CResult : public CObject
{// �`���[�g���A���̃N���X
public:
	CResult();	// �R���X�g���N�^
	~CResult();	// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void);	// ������
	virtual void Uninit(void);	// �I��
	virtual void Update();	// �X�V
	virtual void Draw();	// �`��
	void UpdateBack(void);	// �w�i�|���S���̍X�V
	void ChangeState(CStateResult *pState);	// �X�e�C�g�̕ύX
	void StartFade(void);	// �t�F�[�h
	void EnableBack(void);	// �w�i�̗L����

	// �ϐ��擾�E�ݒ�֐�

	// �ÓI�����o�֐�
	static CResult *Create(void);	// ��������
private:
	// �����o�֐�
	void SetPlayer(void);	// �v���C���[�ݒ�
	void SetCamera(void);	// �J�����ݒ�
	void SaveTime(void);	// �^�C���̕ۑ�

	// �����o�ϐ�
	CStateResult *m_pState;
	CPolygon2D *m_pBack;	// �w�i�̃|���S��
};

class CStateResult
{// �X�e�C�g�̊��N���X
public:
	CStateResult() {};	// �R���X�g���N�^
	virtual ~CStateResult() {};	 // �f�X�g���N�^

	// �����o�֐�
	virtual void Init(CResult *pResult) = 0;	// ����������
	virtual void Uninit(CResult *pResult);	// �I������
	virtual void Update(CResult *pResult) = 0;	// �X�V����

private:
};

class CStateResultDispTime : public CStateResult
{// �^�C���\��
public:
	CStateResultDispTime();	// �R���X�g���N�^
	virtual ~CStateResultDispTime();	 // �f�X�g���N�^

	// �����o�֐�
	void Init(CResult *pResult) override;	// ����������
	void Uninit(CResult *pResult) override;	// �I������
	void Update(CResult *pResult) override;	// �X�V����

private:
	// �񋓌^��`
	enum E_Menu
	{// ���j���[����
		MENU_CONTINUE = 0,	// �R���e�B�j���[
		MENU_QUIT,	// �߂�
		MENU_MAX
	};

	// �����o�֐�
	void SetNumber(void);	// �����̐ݒ�
	void UpdateNumber(void);	// �����̍X�V
	void UpdateCaption(void);	// ���o���̍X�V

	// �����o�ϐ�
	CTimer *m_pTimeOwn;	// ���g�̃^�C��
	CUI *m_pCaption;	// ���ڂ̌��o��
	float m_fCntAnim;	// �A�j���[�V�����J�E���^�[
	vector<CUI*> m_aMenuPolygon;	// ���j���[�̃|���S��
};

namespace Tutorial
{
CUI *CreateUIDefault(void);
}

#endif