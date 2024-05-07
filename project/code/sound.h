//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���R����
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	typedef enum
	{
		LABEL_BGM_TITLE = 0,				// �^�C�g��BGM
		LABEL_BGM_GAME,					// �Q�[��BGM
		LABEL_BGM_BOSS00,					// �{�XBGM�O
		LABEL_SE_START_GAME,			// �Q�[���X�^�[�g

		LABEL_SE_HIT00,					// �q�b�g�O
		LABEL_SE_HIT01,					// �q�b�g�P
		LABEL_SE_SHOT00,					// �ˌ��O
		LABEL_SE_SHOT01,					// �ˌ��P
		LABEL_SE_SHOT02,					// �ˌ��Q
		LABEL_SE_SHOT03,					// �ˌ��R
		LABEL_SE_SHOT04,					// �ˌ��S
		LABEL_SE_EXPLOSION00,					// �����O
		LABEL_SE_EXPLOSION01,					// �����P
		LABEL_SE_DASH00,					// �_�b�V���O
		LABEL_SE_DASH01,					// �_�b�V���P
		LABEL_SE_BOOST00,					// �u�[�X�g�O
		LABEL_SE_WARNING00,					// �x���O
		LABEL_SE_LAND00,					// ���n�O
		LABEL_SE_IMPACT00,					// �Ռ��O
		LABEL_SE_IMPACT01,					// �Ռ��P
		LABEL_SE_SLASH00,					// �a���O

		LABEL_SE_PAUSE_MENU,			// �|�[�Y
		LABEL_SE_PAUSE_ARROW,			// �|�[�Y�ړ�
		LABEL_SE_PAUSE_ENTER,			// �|�[�Y�I��
		LABEL_MAX
	} LABEL;
	typedef enum
	{
		FADESTATE_NONE = 0,	//�������Ă��Ȃ����
		FADESTATE_IN,	//�t�F�[�h�C�����
		FADESTATE_OUT,	//�t�F�[�h�A�E�g���
		FADESTATE_MAX
	}FADESTATE;

	CSound();	// �R���X�g���N�^
	~CSound();	// �f�X�g���N�^

	static CSound *Create(HWND hWnd);
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void Update(void);

	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void Stop(void);

	void SetVolume(LABEL label, float fVolume);
	void SetFade(LABEL LabelNow, LABEL LabelNext, float fSpeed);

	static CSound *GetInstance(void) { return m_pSound; }

private:
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX];	// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];	// �I�[�f�B�I�f�[�^�T�C�Y
	FADESTATE m_fadeSound;	// �t�F�[�h���
	LABEL m_SoundLabelNow;	// ���݂̃T�E���h���x��
	LABEL m_SoundLabelNext;	// ���̃T�E���h���x��
	float m_fSpeedFadeSound;	// �T�E���h���t�F�[�h����X�s�[�h
	float m_fVolumeSound;	// �T�E���h�̃{�����[��

	// �T�E���h�̏��
	SOUNDINFO m_aSoundInfo[LABEL_MAX] =
	{
		{ "data/SOUND/BGM/title.wav", -1 },				// �^�C�g��BGM
		{ "data/SOUND/BGM/game.wav", -1 },				// �Q�[��BGM
		{ "data/SOUND/BGM/boss00.wav", -1 },				// �{�XBGM�O
		{ "data/SOUND/SE/enter.wav",0 },			// �Q�[���X�^�[�g

		{ "data/SOUND/SE/hit00.wav",0 },					// �q�b�g�O
		{ "data/SOUND/SE/hit01.wav",0 },					// �q�b�g�P
		{ "data/SOUND/SE/shot00.wav",0 },					// �ˌ��O
		{ "data/SOUND/SE/shot01.wav",0 },					// �ˌ��P
		{ "data/SOUND/SE/shot02.wav",0 },					// �ˌ��Q
		{ "data/SOUND/SE/shot03.wav",0 },					// �ˌ��R
		{ "data/SOUND/SE/shot04.wav",0 },					// �ˌ��S
		{ "data/SOUND/SE/explosion00.wav",0 },					// �����O
		{ "data/SOUND/SE/explosion01.wav",0 },					// �����P
		{ "data/SOUND/SE/dash00.wav",0 },					// �_�b�V���O
		{ "data/SOUND/SE/dash01.wav",0 },					// �_�b�V���P
		{ "data/SOUND/SE/boost00.wav",0 },					// �u�[�X�g�O
		{ "data/SOUND/SE/warning00.wav",-1 },					// �x���O
		{ "data/SOUND/SE/land00.wav",0 },					// ���n�O
		{ "data/SOUND/SE/impact00.wav",0 },					// �Ռ��O
		{ "data/SOUND/SE/impact01.wav",0 },					// �Ռ��P
		{ "data/SOUND/SE/slash00.wav",0 },					// �a���O

		{ "data/SOUND/SE/pause.wav",0 },				// �|�[�Y
		{ "data/SOUND/SE/pause_arrow.wav",0 },			// �I��
		{ "data/SOUND/SE/pause_enter.wav",0 },			// ����
	};

	static CSound *m_pSound;	// ���g�̃|�C���^
};

namespace Sound
{
void Play(CSound::LABEL label);
}

#endif