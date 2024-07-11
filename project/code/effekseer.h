//===========================================================
//
// ���̃G�t�F�N�V�A[effekseer.h]
// Author �匴�叫
//
//===========================================================
#ifndef _EFFEKSEER_H_     //���̃}�N������`����ĂȂ�������
#define _EFFEKSEER_H_     //2�d�C���N���[�h��h�~�̃}�N�����`����

#define MAX_EFK   (64)

class CEffekseer
{
public:
	CEffekseer();
	~CEffekseer();

	// ���
	enum TYPE
	{
		TYPE_NONE = 0,  // �Ȃ���Ȃ�
		TYPE_DRIFT,     // �h���t�g���̉ΉԂƉ�
		TYPE_SPARK,     // �Ή�
		TYPE_ENGINE,	// �r�C���̉�
		TYPE_SLASH,		// �a��
		TYPE_PARRY,		// �p���B
		TYPE_MAX
	};

	// ���
	struct Info
	{
		Effekseer::Vector3D pos;       // �ʒu
		Effekseer::Vector3D rot;       // ����
		Effekseer::Vector3D scale;     // �傫��
		Effekseer::EffectRef effect;   // �G�t�F�N�g
		Effekseer::Handle efkHandle;   // �n���h��
		const char* EfkName;           // ���O
		int32_t time;                  // ����
	};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(const char* FileName, ::Effekseer::Vector3D pos, ::Effekseer::Vector3D rot, ::Effekseer::Vector3D scale);

	::EffekseerRendererDX9::RendererRef GetEffekseerRenderer(void) { return m_efkRenderer; }
	::Effekseer::ManagerRef GetEfkManager(void) { return m_efkManager; }
	void SetupEffekseerModules(::Effekseer::ManagerRef efkManager);

	void Release(int idx);

	static const char* m_apEfkName[CEffekseer::TYPE_MAX];

private:

	// �����o�ϐ� 
	Info m_Info[MAX_EFK];
	EffekseerRendererDX9::RendererRef m_efkRenderer;
	::Effekseer::Matrix44 cameraMatrix;
	::Effekseer::Matrix44 projectionMatrix;
	::Effekseer::ManagerRef m_efkManager;
	::Effekseer::Vector3D viewerPosition;
	int m_nNum;
};

#endif