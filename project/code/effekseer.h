//===========================================================
//
// 私のエフェクシア[effekseer.h]
// Author 大原怜将
//
//===========================================================
#ifndef _EFFEKSEER_H_     //このマクロが定義されてなかったら
#define _EFFEKSEER_H_     //2重インクルードを防止のマクロを定義する

#define MAX_EFK   (64)

class CEffekseer
{
public:
	CEffekseer();
	~CEffekseer();

	// 種類
	enum TYPE
	{
		TYPE_NONE = 0,  // なんもない
		TYPE_DRIFT,     // ドリフト時の火花と煙
		TYPE_SPARK,     // 火花
		TYPE_ENGINE,	// 排気口の火
		TYPE_SLASH,		// 斬撃
		TYPE_PARRY,		// パリィ
		TYPE_MAX
	};

	// 情報
	struct Info
	{
		Effekseer::Vector3D pos;       // 位置
		Effekseer::Vector3D rot;       // 向き
		Effekseer::Vector3D scale;     // 大きさ
		Effekseer::EffectRef effect;   // エフェクト
		Effekseer::Handle efkHandle;   // ハンドル
		const char* EfkName;           // 名前
		int32_t time;                  // 時間
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

	// メンバ変数 
	Info m_Info[MAX_EFK];
	EffekseerRendererDX9::RendererRef m_efkRenderer;
	::Effekseer::Matrix44 cameraMatrix;
	::Effekseer::Matrix44 projectionMatrix;
	::Effekseer::ManagerRef m_efkManager;
	::Effekseer::Vector3D viewerPosition;
	int m_nNum;
};

#endif