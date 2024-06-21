//*****************************************************
//
// �p�[�c�̏���[parts.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "parts.h"
#include "model.h"

//====================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//====================================================
CParts::~CParts()
{

}

//====================================================
// ����������
//====================================================
HRESULT CParts::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	return S_OK;
}

//====================================================
// �I������
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
// �X�V����
//====================================================
void CParts::Update(void)
{
	// ���̈ʒu�p�����̎擾
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

		// �ʒu�擾
		m_pos = D3DXVECTOR3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

		// �p�x�擾
		btQuaternion quaternion = fallRigidBody->getOrientation();
		btMatrix3x3 rot = trans.getBasis();
		btVector3 euler;
		rot.getEulerZYX(euler[2], euler[1], euler[0]);

		m_rot = D3DXVECTOR3(euler[0], euler[1], euler[2]);
	}

	// �ړ��ʂ����Z
	m_pos += m_move;

	// �O��̃}�g���b�N�X��ۑ�
	m_mtxWorldOld = m_mtxWorld;
}

//====================================================
// �`�揈��
//====================================================
void CParts::Draw(void)
{
	if (m_pModel == nullptr)
	{
		return;
	}

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	LPDIRECT3DTEXTURE9 pTexture;

	// ���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pModel->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pModel->dwNumMat; nCntMat++)
	{
		// �}�e���A���̕ۑ�
		matDef = pMat[nCntMat].MatD3D;

		if (m_bChangeCol)
		{
			// �F�̐ݒ�
			pMat[nCntMat].MatD3D.Diffuse = m_col;
		}

		//�}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̎擾
		pTexture = CTexture::GetInstance()->GetAddress(m_pModel->pIdxTexture[nCntMat]);

		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, pTexture);

		//���f���i�p�[�c�j�`��
		m_pModel->pMesh->DrawSubset(nCntMat);

		// �F��߂�
		pMat[nCntMat].MatD3D = matDef;

		// �}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================
// �e�p�̕`�揈��
//====================================================
void CParts::DrawShadow(void)
{
	if (m_pModel == nullptr)
	{
		return;
	}

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	LPDIRECT3DTEXTURE9 pTexture;

	// ���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pModel->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pModel->dwNumMat; nCntMat++)
	{
		// �}�e���A���̕ۑ�
		matDef = pMat[nCntMat].MatD3D;

		// �F�̐ݒ�
		pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pMat[nCntMat].MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//�}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̎擾
		pTexture = CTexture::GetInstance()->GetAddress(m_pModel->pIdxTexture[nCntMat]);

		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, pTexture);

		//���f���i�p�[�c�j�`��
		m_pModel->pMesh->DrawSubset(nCntMat);

		// �F��߂�
		pMat[nCntMat].MatD3D = matDef;

		// �}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//=====================================================
// �����ݒ�
//=====================================================
void CParts::InitPhysics(void)
{
	// �������锠�̏Փˌ`��̍쐬
	btCollisionShape* pFallShapes = new btBoxShape(btVector3(m_vtxMax.x, m_vtxMax.y, m_vtxMax.z));

	btTransform StratTransform;
	StratTransform.setIdentity();
	StratTransform.setOrigin(btVector3(m_pos.x, m_pos.y, m_pos.z));

	btVector3 fallInertia(0, 0, 0);
	pFallShapes->calculateLocalInertia(m_nMass, fallInertia);

	// ����MotionState�̐ݒ�
	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(m_pos.x, m_pos.y, m_pos.z)));
	// ���̏�������ݒ�
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(m_nMass, fallMotionState, pFallShapes, fallInertia);
	// ���̍��̂̍쐬
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);

	// ���[���h�ɔ��̍��̂�ǉ�
	CManager::GetPhysics()->GetDynamicsWorld()->addRigidBody(fallRigidBody);
	
	// �ԍ�
	m_nIdxPhysics = CManager::GetPhysics()->GetDynamicsWorld()->getNumCollisionObjects() - 1;
}

//=====================================================
// �}�g���b�N�X�ݒ菈��
//=====================================================
void CParts::SetMatrix(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;
	
	// ���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//=====================================================
// ��������
//=====================================================
CParts *CParts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CParts *pCParts = nullptr;

	if (pCParts == nullptr)
	{
		// �C���X�^���X����
		pCParts = new CParts;

		pCParts->m_pos = pos;
		pCParts->m_rot = rot;

		// ����������
		pCParts->Init();
	}

	return pCParts;
}

//=====================================================
// ���f���̍Œ����_�擾
//=====================================================
void CParts::SetRadius(void)
{
	// �v�Z�p�ϐ�
	int nNumVtx;			//���_��
	DWORD dwSizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	float fLength = 0.0f;
	D3DXVECTOR3 vtxMin = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 vtxMax = { 0.0f,0.0f,0.0f };

	// ���_���̎擾
	nNumVtx = m_pModel->pMesh->GetNumVertices();

	// �t�H�[�}�b�g�T�C�Y����
	dwSizeFVF = D3DXGetFVFVertexSize(m_pModel->pMesh->GetFVF());

	// ���_�o�b�t�@�̃��b�N
	m_pModel->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (vtx.x > vtxMax.x)
		{// X�̍ő�l
			vtxMax.x = vtx.x;
		}
		else if (vtx.x < vtxMin.x)
		{// X�̍ŏ��l
			vtxMin.x = vtx.x;
		}

		if (vtx.z > vtxMax.z)
		{// Z�̍ő�l
			vtxMax.z = vtx.z;
		}
		else if (vtx.z < vtxMin.z)
		{// Z�̍ŏ��l
			vtxMin.z = vtx.z;
		}

		if (vtx.y > vtxMax.y)
		{// Y�̍ő�l
			vtxMax.y = vtx.y;
		}
		else if (vtx.y < vtxMin.y)
		{// Y�̍ŏ��l
			vtxMin.y = vtx.y;
		}

		if (D3DXVec3Length(&vtx) > fLength)
		{
			fLength = D3DXVec3Length(&vtx);
		}

		pVtxBuff += dwSizeFVF;
	}

	// �ő�E�ŏ����_�ݒ�
	m_vtxMax = vtxMax;
	m_vtxMin = vtxMin;

	// ���_�o�b�t�@�̃A�����b�N
	m_pModel->pMesh->UnlockVertexBuffer();

	// ��������
	m_fRadius = fLength;
}

//=====================================================
// ���f���̊��蓖��
//=====================================================
void CParts::BindModel(int nIdx)
{
	// ���f�����蓖��
	m_pModel = CModel::GetModel(nIdx);

	// ���a�ݒ�
	SetRadius();
}