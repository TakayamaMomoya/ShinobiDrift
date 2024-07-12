//*****************************************************
//
// �}�j�s�����[�^�[[manipulater.h]
// Author:���R����
//
//*****************************************************
#ifndef _MANIPULATER_H_
#define _MANIPULATER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"

//*****************************************************
// �O����`
//*****************************************************
class CStateManipulater;
class CMotion;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CManipulater : public CObject
{// �}�j�s�����[�^�[�N���X
public:
    CManipulater(int nPriority = 4);	// �R���X�g���N�^
	~CManipulater();    // �f�X�g���N�^

    // �����o�֐�
	HRESULT Init(void); // ����������
	void Uninit(void);  // �I������
	void Update(void);  // �X�V����
	void Draw(void);    // �`�揈��
    void ChangeState(CStateManipulater *pState);  // �X�e�C�g�̕ύX

    // �ϐ��擾�E�ݒ�֐�
    int GetIdxPart(void) { return m_nIdxPart; } // �p�[�c�ԍ�
    void SetIdxPart(int nIdx) { m_nIdxPart = nIdx; }
    void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu
    D3DXVECTOR3 GetPosition(void) { return m_pos; }
    void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }	// ����
    D3DXVECTOR3 GetRotation(void) { return m_rot; }
    CMotion *GetMotion(void) { return m_pMotion; }  // ���[�V�����擾

    // �ÓI�����o�֐�
    static CManipulater* Create(int nIdxPart, CMotion *pMotion);    // ��������

private:
	// �����o�֐�
    D3DXVECTOR3 m_pos;  // �ʒu
    D3DXVECTOR3 m_rot;  // ����

	// �����o�ϐ�
    int m_nIdxPart; // �p�[�c�̔ԍ�
    CStateManipulater *m_pState;    // �X�e�C�g�̃|�C���^
    CMotion *m_pMotion; // ���[�V�����̃|�C���^
};

class CStateManipulater
{// �X�e�C�g�̊��N���X
public:
    CStateManipulater() {};	// �R���X�g���N�^
    virtual ~CStateManipulater() {};    // �f�X�g���N�^
    
    // �����o�֐�
    virtual void Init(CManipulater *pManipulater) = 0; // ����������
    virtual void Uninit(CManipulater *pManipulater) = 0;  // �I������
    virtual void Update(CManipulater *pManipulater) = 0;  // �X�V����

private:
};

class CStateManipulaterTranslate : public CStateManipulater
{// �ړ��̃X�e�C�g
public:
    CStateManipulaterTranslate();    // �R���X�g���N�^
    virtual ~CStateManipulaterTranslate();   // �f�X�g���N�^

    // �����o�֐�
    void Init(CManipulater *pManipulater) override; // ����������
    void Uninit(CManipulater *pManipulater) override;  // �I������
    void Update(CManipulater *pManipulater) override;  // �X�V����

private:
    enum E_MODE
    {// �����[�h
        MODE_NONE = 0,  // ���ł��Ȃ����
        MODE_X,  // X���𓮂����Ă���
        MODE_Y,  // Y���𓮂����Ă���
        MODE_Z,  // Z���𓮂����Ă���
        MODE_MAX
    };
    // �����o�֐�
    void Input(CManipulater *pManipulater);   // ���͏���
    void FollowModel(CManipulater *pManipulater); // ���f���̒Ǐ]
    void ModeMove(CManipulater *pManipulater);    // ���[�h���Ƃ̓���

    // �����o�ϐ�
    CObjectX *m_pManipulater;   // �}�j�s�����[�^�[
    E_MODE m_mode;  // ���̃��[�h
};

#endif
