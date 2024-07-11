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

    // �ÓI�����o�֐�
    static CManipulater* Create(int nIdxPart, CMotion *pMotion);    // ��������

private:
	// �����o�֐�


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
    virtual void Uninit(void) = 0;  // �I������
    virtual void Update(void) = 0;  // �X�V����

private:
};

class CStateManipulaterTranslate : public CStateManipulater
{// �ړ��̃X�e�C�g
public:
    CStateManipulaterTranslate() {};    // �R���X�g���N�^
    virtual ~CStateManipulaterTranslate() {};   // �f�X�g���N�^

    // �����o�֐�
    void Init(void) override; // ����������
    void Uninit(void) override;  // �I������
    void Update(void) override;  // �X�V����

private:
};

#endif
