//*****************************************************
//
// �����N�^�C���̏���[rankTime.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "rankTime.h"
#include "timer.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int NUM_TIMER_RUNKER = 3;	// �����J�[�̃^�C���̐�
const D3DXVECTOR3 POS_NUMBER_DEFAULT = { 0.9f, 0.2f,0.0f };	// �����̃f�t�H���g�ʒu
const float SCALE_NUMBER = 0.5f;	// �^�C�}�[�̐����̃X�P�[��
const float DIST_TIMER = 0.1f;	// �^�C�}�[�Ԃ̋���
const string PATH_SAVE = "data\\BYNARY\\ranking.bin";	// �����L���O�̃t�@�C���p�X
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CRankTime *CRankTime::s_pRankTime = nullptr;

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CRankTime::CRankTime()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CRankTime::~CRankTime()
{

}

//=====================================================
// ��������
//=====================================================
CRankTime* CRankTime::Create(void)
{
	if (s_pRankTime == nullptr)
	{// �C���X�^���X����
		s_pRankTime = new CRankTime;

		if (s_pRankTime != nullptr)
		{// ������
			s_pRankTime->Init();
		}
	}
	
	return s_pRankTime;
}

//=====================================================
// ����������
//=====================================================
HRESULT CRankTime::Init(void)
{
	m_aTimer.resize(NUM_TIMER_RUNKER);

	vector<float> aTime = RankTime::LoadRankTime();

	// �^�C�}�[�̐���
	for (int i = 0; i < NUM_TIMER_RUNKER; i++)
	{
		m_aTimer[i] = CTimer::Create();

		if (m_aTimer[i] == nullptr)
			continue;
		D3DXVECTOR3 pos = POS_NUMBER_DEFAULT;
		pos.y += DIST_TIMER * i;
		m_aTimer[i]->SetPosition(pos);	// �ʒu
		m_aTimer[i]->SetScaleNumber(SCALE_NUMBER);// �X�P�[��
		m_aTimer[i]->SetSecond(aTime[i]);
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CRankTime::Uninit(void)
{
	s_pRankTime = nullptr;

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CRankTime::Update(void)
{

}

namespace RankTime
{
//=====================================================
// �����L���O�^�C���Ǎ�
//=====================================================
vector<float> LoadRankTime(void)
{
	vector<float> aTime;

	// �t�@�C�����J��
	std::ifstream inputFile(PATH_SAVE, std::ios::binary);

	if (!inputFile.is_open())
		assert(("�����L���O�t�@�C�����J���܂���ł���", false));

	while(true)
	{// �t�@�C���̏I���܂œǂݍ���
		float fTime;

		inputFile.read(reinterpret_cast<char*>(&fTime), sizeof(float));

		if (inputFile.eof())
			break;

		aTime.push_back(fTime);
	}

	inputFile.close();

	return aTime;
}

//=====================================================
// �����L���O�^�C���ۑ�
//=====================================================
void SaveRankTime(vector<float> aTime)
{
	// �t�@�C�����J��
	std::ofstream outputFile(PATH_SAVE, std::ios::binary);

	if (!outputFile.is_open())
		assert(("�����L���O�t�@�C�����J���܂���ł���", false));

	// ��񐔕ۑ�
	size_t size = aTime.size();

	// �z��̕ۑ�
	outputFile.write(reinterpret_cast<char*>(aTime.data()), sizeof(float) * size);

	outputFile.close();
}
}