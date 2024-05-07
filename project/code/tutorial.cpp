//*****************************************************
//
// チュートリアル処理[tutorial.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "tutorial.h"
#include "object.h"
#include "player.h"
#include "slow.h"
#include "manager.h"
#include "camera.h"
#include "cameraBehavior.h"
#include "UIManager.h"
#include "UI.h"
#include "meshfield.h"
#include "object3D.h"
#include "renderer.h"
#include "texture.h"
#include "animEffect3D.h"
#include "inputManager.h"
#include "fade.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float TIME_SPAWN = 3.0f;	// スポーンまでの間隔
const D3DXVECTOR3 POS_SKIP = { SCREEN_WIDTH * 0.9f,SCREEN_HEIGHT * 0.85f, 0.0f };	// スキップ表示の位置
const D3DXVECTOR3 POS_GAUGE = { POS_SKIP.x + 2.0f,POS_SKIP.y + 28.0f, 0.0f };	// スキップ表示の位置
const D3DXVECTOR2 SIZE_SKIP = { 80.0f,60.0f };	// スキップ表示のサイズ
const D3DXVECTOR2 SIZE_GAUGE = { 70.0f,26.0f };	// スキップゲージのサイズ
const char* PATH_SKIP = "data\\TEXTURE\\UI\\tutorial06.png";	// スキップ表示のパス
const float TIME_SKIP = 2.0f;	// スキップにかかる時間
}

//=====================================================
// コンストラクタ
//=====================================================
CTutorial::CTutorial()
{

}

//=====================================================
// デストラクタ
//=====================================================
CTutorial::~CTutorial()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CTutorial::Init(void)
{
	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CTutorial::Uninit(void)
{
	// オブジェクト全棄
	CObject::ReleaseAll();
}

//=====================================================
// 更新処理
//=====================================================
void CTutorial::Update(void)
{

}

//=====================================================
// 描画処理
//=====================================================
void CTutorial::Draw(void)
{

}