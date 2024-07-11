//*****************************************************
//
// マニピュレーター[manipulater.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "manipulater.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{

}

//=====================================================
// コンストラクタ
//=====================================================
CManipulater::CManipulater(int nPriority)
{
    m_nIdxPart = 0;
    m_pState = nullptr;
    m_pMotion = nullptr;
}

//=====================================================
// デストラクタ
//=====================================================
CManipulater::~CManipulater()
{

}

//=====================================================
// 生成処理
//=====================================================
CManipulater* CManipulater::Create(int nIdxPart, CMotion *pMotion)
{
    CManipulater *pManipulater = nullptr;

	if (pManipulater == nullptr)
	{
        pManipulater = new CManipulater;

		if (pManipulater != nullptr)
		{
			// 初期化
            pManipulater->Init();

            pManipulater->m_nIdxPart = nIdxPart;
            pManipulater->m_pMotion = pMotion;
		}
	}

	return pManipulater;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CManipulater::Init(void)
{
    ChangeState(new CStateManipulaterTranslate);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CManipulater::Uninit(void)
{
    if (m_pState != nullptr)
    {
        m_pState->Uninit();
        m_pState = nullptr;
    }

    Release();
}

//=====================================================
// 更新処理
//=====================================================
void CManipulater::Update(void)
{
    if (m_pState != nullptr)
    {
        m_pState->Update();
    }
}

//=====================================================
// 描画処理
//=====================================================
void CManipulater::Draw(void)
{

}

//=====================================================
// ステイトの変更
//=====================================================
void CManipulater::ChangeState(CStateManipulater *pState)
{
    if (m_pState != nullptr)
    {
        m_pState->Uninit();
        m_pState = nullptr;
    }

    m_pState = pState;

    if (m_pState != nullptr)
    {
        m_pState->Init();
    }
}

//********************************************************************************
// 移動のステイト
//********************************************************************************
//=====================================================
// 初期化
//=====================================================
void CStateManipulaterTranslate::Init(void)
{

}

//=====================================================
// 終了
//=====================================================
void CStateManipulaterTranslate::Uninit(void)
{

}

//=====================================================
// 更新
//=====================================================
void CStateManipulaterTranslate::Update(void)
{

}
