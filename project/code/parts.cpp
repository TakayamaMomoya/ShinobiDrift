//*****************************************************
//
// パーツの処理[parts.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "parts.h"
#include "model.h"

//====================================================
// コンストラクタ
//====================================================
CParts::CParts()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_IdxModel = -1;
	m_fRadius = 0.0f;
	m_bChangeCol = false;
	m_col = { 0.0f,0.0f,0.0f,0.0f };

	m_pDynamicsWorld = nullptr;
	m_nMass = 1;
	m_nIdxPhysics = - 1;
}

//====================================================
// デストラクタ
//====================================================
CParts::~CParts()
{

}

//====================================================
// 初期化処理
//====================================================
HRESULT CParts::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CParts::Uninit(void)
{
	if (m_pModel != nullptr)
	{
		m_pModel = nullptr;
	}

	delete this;
}

//====================================================
// 更新処理
//====================================================
void CParts::Update(void)
{
	// 箱の位置姿勢情報の取得
	btTransform trans;

	if (CManager::GetPhysics())
		return;

	if (CManager::GetPhysics()->GetDynamicsWorld())
		return;

	btCollisionObject* obj = CManager::GetPhysics()->GetDynamicsWorld()->getCollisionObjectArray()[m_nIdxPhysics];
	btRigidBody* fallRigidBody = btRigidBody::upcast(obj);

	if (fallRigidBody && fallRigidBody->getMotionState())
	{
		fallRigidBody->activate(true);
		fallRigidBody->getMotionState()->getWorldTransform(trans);

		// 位置取得
		m_pos = D3DXVECTOR3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

		// 角度取得
		btQuaternion quaternion = fallRigidBody->getOrientation();
		btMatrix3x3 rot = trans.getBasis();
		btVector3 euler;
		rot.getEulerZYX(euler[2], euler[1], euler[0]);

		m_rot = D3DXVECTOR3(euler[0], euler[1], euler[2]);
	}

	// 移動量を加算
	m_pos += m_move;

	// 前回のマトリックスを保存
	m_mtxWorldOld = m_mtxWorld;
}

//====================================================
// 描画処理
//====================================================
void CParts::Draw(void)
{
	if (m_pModel == nullptr)
	{
		return;
	}

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	LPDIRECT3DTEXTURE9 pTexture;

	// 現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pModel->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pModel->dwNumMat; nCntMat++)
	{
		// マテリアルの保存
		matDef = pMat[nCntMat].MatD3D;

		if (m_bChangeCol)
		{
			// 色の設定
			pMat[nCntMat].MatD3D.Diffuse = m_col;
		}

		//マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの取得
		pTexture = CTexture::GetInstance()->GetAddress(m_pModel->pIdxTexture[nCntMat]);

		//テクスチャ設定
		pDevice->SetTexture(0, pTexture);

		//モデル（パーツ）描画
		m_pModel->pMesh->DrawSubset(nCntMat);

		// 色を戻す
		pMat[nCntMat].MatD3D = matDef;

		// マテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================
// 影用の描画処理
//====================================================
void CParts::DrawShadow(void)
{
	if (m_pModel == nullptr)
	{
		return;
	}

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	LPDIRECT3DTEXTURE9 pTexture;

	// 現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pModel->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pModel->dwNumMat; nCntMat++)
	{
		// マテリアルの保存
		matDef = pMat[nCntMat].MatD3D;

		// 色の設定
		pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pMat[nCntMat].MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの取得
		pTexture = CTexture::GetInstance()->GetAddress(m_pModel->pIdxTexture[nCntMat]);

		//テクスチャ設定
		pDevice->SetTexture(0, pTexture);

		//モデル（パーツ）描画
		m_pModel->pMesh->DrawSubset(nCntMat);

		// 色を戻す
		pMat[nCntMat].MatD3D = matDef;

		// マテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//=====================================================
// 物理設定
//=====================================================
void CParts::InitPhysics(void)
{
	// 落下する箱の衝突形状の作成
	btCollisionShape* pFallShapes = new btBoxShape(btVector3(m_vtxMax.x, m_vtxMax.y, m_vtxMax.z));

	btTransform StratTransform;
	StratTransform.setIdentity();
	StratTransform.setOrigin(btVector3(m_pos.x, m_pos.y, m_pos.z));

	btVector3 fallInertia(0, 0, 0);
	pFallShapes->calculateLocalInertia(m_nMass, fallInertia);

	// 箱のMotionStateの設定
	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(m_pos.x, m_pos.y, m_pos.z)));
	// 箱の初期情報を設定
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(m_nMass, fallMotionState, pFallShapes, fallInertia);
	// 箱の剛体の作成
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);

	// ワールドに箱の剛体を追加
	CManager::GetPhysics()->GetDynamicsWorld()->addRigidBody(fallRigidBody);
	
	// 番号
	m_nIdxPhysics = CManager::GetPhysics()->GetDynamicsWorld()->getNumCollisionObjects() - 1;
}

//=====================================================
// マトリックス設定処理
//=====================================================
void CParts::SetMatrix(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// 変数宣言
	D3DXMATRIX mtxRot, mtxTrans;
	
	// ワールドマトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//=====================================================
// 生成処理
//=====================================================
CParts *CParts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CParts *pCParts = nullptr;

	if (pCParts == nullptr)
	{
		// インスタンス生成
		pCParts = new CParts;

		pCParts->m_pos = pos;
		pCParts->m_rot = rot;

		// 初期化処理
		pCParts->Init();
	}

	return pCParts;
}

//=====================================================
// モデルの最長頂点取得
//=====================================================
void CParts::SetRadius(void)
{
	// 計算用変数
	int nNumVtx;			//頂点数
	DWORD dwSizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;			//頂点バッファへのポインタ
	float fLength = 0.0f;
	D3DXVECTOR3 vtxMin = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 vtxMax = { 0.0f,0.0f,0.0f };

	// 頂点数の取得
	nNumVtx = m_pModel->pMesh->GetNumVertices();

	// フォーマットサイズ入手
	dwSizeFVF = D3DXGetFVFVertexSize(m_pModel->pMesh->GetFVF());

	// 頂点バッファのロック
	m_pModel->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (vtx.x > vtxMax.x)
		{// Xの最大値
			vtxMax.x = vtx.x;
		}
		else if (vtx.x < vtxMin.x)
		{// Xの最小値
			vtxMin.x = vtx.x;
		}

		if (vtx.z > vtxMax.z)
		{// Zの最大値
			vtxMax.z = vtx.z;
		}
		else if (vtx.z < vtxMin.z)
		{// Zの最小値
			vtxMin.z = vtx.z;
		}

		if (vtx.y > vtxMax.y)
		{// Yの最大値
			vtxMax.y = vtx.y;
		}
		else if (vtx.y < vtxMin.y)
		{// Yの最小値
			vtxMin.y = vtx.y;
		}

		if (D3DXVec3Length(&vtx) > fLength)
		{
			fLength = D3DXVec3Length(&vtx);
		}

		pVtxBuff += dwSizeFVF;
	}

	// 最大・最小頂点設定
	m_vtxMax = vtxMax;
	m_vtxMin = vtxMin;

	// 頂点バッファのアンロック
	m_pModel->pMesh->UnlockVertexBuffer();

	// 長さを代入
	m_fRadius = fLength;
}

//=====================================================
// モデルの割り当て
//=====================================================
void CParts::BindModel(int nIdx)
{
	// モデル割り当て
	m_pModel = CModel::GetModel(nIdx);

	// 半径設定
	SetRadius();
}