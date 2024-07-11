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
#include "motion.h"

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
        m_pState->Uninit(this);
        m_pState = nullptr;
    }

    Release();
}

//=====================================================
// 更新処理
//=====================================================
void CManipulater::Update(void)
{
    // パーツの位置の取得
    D3DXVECTOR3 posPart = m_pMotion->GetMtxPos(m_nIdxPart);

    SetPosition(posPart);

    if (m_pState != nullptr)
    {
        m_pState->Update(this);
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
        m_pState->Uninit(this);
        m_pState = nullptr;
    }

    m_pState = pState;

    if (m_pState != nullptr)
    {
        m_pState->Init(this);
    }
}

//********************************************************************************
// 移動のステイト
//********************************************************************************
//=====================================================
// コンストラクタ
//=====================================================
CStateManipulaterTranslate::CStateManipulaterTranslate()
{
    m_pManipulater = nullptr;
}

//=====================================================
// デストラクタ
//=====================================================
CStateManipulaterTranslate::~CStateManipulaterTranslate()
{

}

//=====================================================
// 初期化
//=====================================================
void CStateManipulaterTranslate::Init(CManipulater *pManipulater)
{
    m_pManipulater = CObjectX::Create();

    int nIdx = CModel::Load("data\\MODEL\\manipulator.x");
    m_pManipulater->BindModel(nIdx);
    m_pManipulater->EnableZtest(true);
}

//=====================================================
// 終了
//=====================================================
void CStateManipulaterTranslate::Uninit(CManipulater *pManipulater)
{

}

//=====================================================
// 更新
//=====================================================
void CStateManipulaterTranslate::Update(CManipulater *pManipulater)
{
    D3DXVECTOR3 posManipulater = pManipulater->GetPosition();

    m_pManipulater->SetPosition(posManipulater);
}
