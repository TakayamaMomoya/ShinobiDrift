//===========================================================
//
// 私のエフェクシア[effekseer.cpp]
// Author 大原怜将
//
//===========================================================

#include <iostream>
#include <string>

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "effekseer.h"
#include "camera.h"
#include "debugproc.h"

// エフェクトの名前
const char* CEffekseer::m_apEfkName[CEffekseer::TYPE_MAX] =
{
	"",                               // なんもない
	"data\\EFFEKSEER\\Effect\\drift.efkefc",  // ドリフト時の火花と煙
	"data\\EFFEKSEER\\Effect\\spark.efkefc",  // 壁衝突時の火花
	"data\\EFFEKSEER\\Effect\\bikefire.efkefc",  // 排気口の火
	"data\\EFFEKSEER\\Effect\\slash00.efkefc",  // 斬撃
};

//===========================================================
// コンストラクタ
//===========================================================
CEffekseer::CEffekseer()
{
	// 値を初期化
	for (int i = 0; i < MAX_EFK; i++)
	{
		m_Info[i].pos = {};
		m_Info[i].rot = {};
		m_Info[i].effect = nullptr;
		m_Info[i].efkHandle = NULL;
		m_Info[i].EfkName = {};
		m_Info[i].time = 0;
	}

	m_nNum = 0;
}

//===========================================================
// デストラクタ
//===========================================================
CEffekseer::~CEffekseer()
{

}

//===========================================================
// 初期化処理
//===========================================================
void CEffekseer::Init(void)
{
	// エフェクトのマネージャーの作成
	m_efkManager = ::Effekseer::Manager::Create(8000);

	// Specify a position of view
	// 視点位置を確定
	viewerPosition = ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f);

	// 座標系を設定する。アプリケーションと一致させる必要がある。
	m_efkManager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

	// Setup effekseer modules
	// Effekseerのモジュールをセットアップする
	SetupEffekseerModules(m_efkManager);

	// Specify a projection matrix
	// 投影行列を設定
	projectionMatrix.PerspectiveFovLH(90.0f / 180.0f * 3.14f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 1.0f, 500.0f);

	// Specify a camera matrix
		// カメラ行列を設定
	cameraMatrix.LookAtLH(viewerPosition, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f));
}

//===========================================================
// 終了処理
//===========================================================
void CEffekseer::Uninit(void)
{
	for (int i = 0; i < MAX_EFK; i++)
	{
		m_Info[i].pos = {};
		m_Info[i].rot = {};
		m_Info[i].effect = nullptr;
		m_Info[i].efkHandle = NULL;
		m_Info[i].EfkName = {};
		m_Info[i].time = 0;
	}

	m_nNum = 0;
}

//===========================================================
// 更新処理
//===========================================================
void CEffekseer::Update(void)
{
	for (int i = 0; i < MAX_EFK; i++)
	{
		if (m_Info[i].effect != nullptr)
		{
			// Move the effect
			// エフェクトの移動
			m_efkManager->AddLocation(m_Info[i].efkHandle, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f));

			// Set layer parameters
			// レイヤーパラメータの設定
			Effekseer::Manager::LayerParameter layerParameter;
			layerParameter.ViewerPosition = viewerPosition;
			m_efkManager->SetLayerParameter(0, layerParameter);

			// Update the manager
			// マネージャーの更新
			Effekseer::Manager::UpdateParameter updateParameter;
			m_efkManager->Update(updateParameter);

			// Update a time
			// 時間を更新する
			m_efkRenderer->SetTime(m_Info[i].time / 60.0f);
			m_Info[i].time++;

			// 毎フレーム、エフェクトが再生終了しているか確認する
			if (m_efkManager->Exists(m_Info[i].efkHandle) == false)
			{
				// 新たにエフェクトを再生し直す。座標はエフェクトを表示したい場所を設定する
				// (位置や回転、拡大縮小も設定しなおす必要がある)
				m_efkManager->StopEffect(m_Info[i].efkHandle);
				Release(i);
			}
		}
	}
}

//===========================================================
// 描画処理
//===========================================================
void CEffekseer::Draw(void)
{
	if (m_efkRenderer != nullptr)
	{
		// Specify a projection matrix
		// 投影行列を設定
		m_efkRenderer->SetProjectionMatrix(projectionMatrix);

		// カメラの情報取得
		CCamera* pCamera = CManager::GetCamera();

		// ビューマトリックス
		auto ViewMatrix = pCamera->GetCamera()->mtxView;

		// プロジェクションマトリックス
		auto Projection = pCamera->GetCamera()->mtxProjection;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				projectionMatrix.Values[i][j] = Projection.m[i][j];
				cameraMatrix.Values[i][j] = ViewMatrix.m[i][j];
			}
		}

		// Specify a camera matrix
		// カメラ行列を設定
		m_efkRenderer->SetCameraMatrix(cameraMatrix);

		// Begin to rendering effects
		// エフェクトの描画開始処理を行う。
		m_efkRenderer->BeginRendering();

		// Render effects
		// エフェクトの描画を行う。
		Effekseer::Manager::DrawParameter drawParameter;
		drawParameter.ZNear = 0.0f;
		drawParameter.ZFar = 1.0f;
		drawParameter.ViewProjectionMatrix = m_efkRenderer->GetCameraProjectionMatrix();
		m_efkManager->Draw(drawParameter);

		// Finish to rendering effects
		// エフェクトの描画終了処理を行う。
		m_efkRenderer->EndRendering();
	}
}

//===========================================================
// 設定
//===========================================================
void CEffekseer::Set(const char *FileName, ::Effekseer::Vector3D pos, ::Effekseer::Vector3D rot, ::Effekseer::Vector3D scale)
{
	for (int i = 0; i < MAX_EFK; i++)
	{
		if (m_Info[i].effect == nullptr)
		{
			// char16_tに変換
			std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
			std::u16string string16t = converter.from_bytes(FileName);

			m_Info[i].pos = pos;
 			m_Info[i].rot = rot;
			m_Info[i].scale = scale;
			m_Info[i].time = 0;

			//std::char_16
			// Load an effect
			// エフェクトの読込
			m_Info[i].effect = Effekseer::Effect::Create(m_efkManager, string16t.c_str());

			// Play an effect
			// エフェクトの再生
			m_Info[i].efkHandle = m_efkManager->Play(m_Info[i].effect, 0, 0, 0);

			// 位置、向き、大きさ設定
			m_efkManager->SetLocation(m_Info[i].efkHandle, m_Info[i].pos);
			m_efkManager->SetRotation(m_Info[i].efkHandle, {0.0f, 1.0f, 0.0f}, rot.Y);
			m_efkManager->SetScale(m_Info[i].efkHandle, m_Info[i].scale.X, m_Info[i].scale.Y, m_Info[i].scale.Z);
			
			break;
		}
	}
}

//===========================================================
// モジュール設定
//===========================================================
void CEffekseer::SetupEffekseerModules(::Effekseer::ManagerRef efkManager)
{
		// Create a  graphics device
	// 描画デバイスの作成
	::Effekseer::Backend::GraphicsDeviceRef graphicsDevice;
	graphicsDevice = ::EffekseerRendererDX9::CreateGraphicsDevice(CRenderer::GetInstance()->GetDevice());

	// Create a renderer of effects
	// エフェクトのレンダラーの作成
	m_efkRenderer = ::EffekseerRendererDX9::Renderer::Create(graphicsDevice, 8000);

	// Sprcify rendering modules
	// 描画モジュールの設定
	efkManager->SetSpriteRenderer(m_efkRenderer->CreateSpriteRenderer());
	efkManager->SetRibbonRenderer(m_efkRenderer->CreateRibbonRenderer());
	efkManager->SetRingRenderer(m_efkRenderer->CreateRingRenderer());
	efkManager->SetTrackRenderer(m_efkRenderer->CreateTrackRenderer());
	efkManager->SetModelRenderer(m_efkRenderer->CreateModelRenderer());

	// Specify a texture, model, curve and material loader
	// It can be extended by yourself. It is loaded from a file on now.
	// テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
	// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
	efkManager->SetTextureLoader(m_efkRenderer->CreateTextureLoader());
	efkManager->SetModelLoader(m_efkRenderer->CreateModelLoader());
	efkManager->SetMaterialLoader(m_efkRenderer->CreateMaterialLoader());
	efkManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
}

void CEffekseer::Release(int idx)
{
	// 値を初期化
	m_Info[idx].pos = {};
	m_Info[idx].rot = {};
	m_Info[idx].scale = {};
	m_Info[idx].effect = nullptr;
	m_Info[idx].efkHandle = NULL;
	m_Info[idx].EfkName = {};
	m_Info[idx].time = 0;
}