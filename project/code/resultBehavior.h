//*****************************************************
//
// ���U���g��Behavior[resultBehavior.h]
// Author:���R����
//
//*****************************************************

#ifndef _RESULTBEHAVIOR_H_
#define _RESULTBEHAVIOR_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include <iostream>
#include <list>

//*****************************************************
// �O���錾
//*****************************************************
class CResult;
class CNumber;
class CObject2D;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CResultBehavior
{
public:
	CResultBehavior();
	virtual ~CResultBehavior();

	virtual void Init(CResult *pResult) = 0;
	virtual void Update(CResult *pResult) = 0;
	virtual void Uninit(CResult *pResult) = 0;
private:

};

class CResultPlayerScore : public CResultBehavior
{
public:
	enum TYPE_NUMBER
	{
		TYPE_ALL = 0,	// ���z
		TYPE_ADD,	// ���Z��V
		TYPE_REPAIR,	// �C����
		TYPE_RESULT,	// ���z
		TYPE_MAX
	};

	CResultPlayerScore();
	~CResultPlayerScore() override;

private:
	void Init(CResult *pResult) override;
	void Update(CResult *pResult) override;
	void Uninit(CResult *pResult) override;

	CNumber *m_apNumber[TYPE_MAX];	// ���l
	CObject2D *m_apCaption[TYPE_MAX];	// ���ڂ̌��o��
	CObject2D *m_pFrame;	// �t���[��
};

class CResultRanking : public CResultBehavior
{
public:
	CResultRanking();
	~CResultRanking() override;

private:
	void Init(CResult *pResult) override;
	void Update(CResult *pResult) override;
	void Uninit(CResult *pResult) override {};
};

#endif