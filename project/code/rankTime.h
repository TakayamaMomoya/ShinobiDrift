//*****************************************************
//
// �����N�^�C���̏���[rankTime.h]
// Author:���R����
//
//*****************************************************
#ifndef _RANKTIME_H_
#define _RANKTIME_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CTimer;
class CUI;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CRankTime : public CObject
{
public:
	CRankTime();	// �R���X�g���N�^
	~CRankTime();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init();
	void Uninit();
	void Update();

	// �ÓI�����o�֐�
	static CRankTime* Create();	// ����
	static CRankTime* GetInstance() { return s_pRankTime; }	// �C���X�^���X�擾

private:
	// �����o�ϐ�
	vector<CTimer*> m_aTimer;	// �����J�[�̃^�C���z��

	// �ÓI�����o�ϐ�
	static CRankTime* s_pRankTime;	// ���g�̃|�C���^
};

namespace RankTime
{
// �����L���O�^�C���Ǎ�
vector<float> LoadRankTime(void);

// �����L���O�^�C���ۑ�
void SaveRankTime(vector<float> aTime);
}

#endif