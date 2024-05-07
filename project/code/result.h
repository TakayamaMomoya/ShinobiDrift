//*****************************************************
//
// ���U���g�̏���[result.h]
// Author:���R����
//
//*****************************************************

#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "scene.h"
#include <iostream>
#include <list>

//*****************************************************
// �萔��`
//*****************************************************
namespace Result
{
const int BASE_REWARD = 100000;	// ��{��V
}

//*****************************************************
// �O���錾
//*****************************************************
class CMeshCylinder;
class CResultBehavior;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CResult : public CScene
{
public:
	struct SInfoRanking
	{// �����L���O�̏��
		int nRank;	// �����N
		std::string name;	// ���O
		int nReward;	// ��V
	};

	CResult();	// �R���X�g���N�^
	~CResult();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ChangeBehavior(CResultBehavior *pBehavior);
	std::list<SInfoRanking> GetListRanking(void) { return m_listRanking; }

private:
	void LoadRanking(void);

	std::list<SInfoRanking> m_listRanking;	// �����L���O�̃��X�g
	CResultBehavior *m_pBehavior;
	CMeshCylinder *m_pCylinder;	// �w�i�̃V�����_�[
};

#endif