//*****************************************************
//
// 3D�|���S���̏���[polygon3D.h]
// Author:���R����
//
//*****************************************************
#ifndef _POLYGON3D_H_
#define _POLYGON3D_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object3D.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPolygon3D : public CObject3D
{
public:
	enum MODE
	{
		MODE_NORMAL = 0,	// �ʏ탂�[�h
		MODE_BILLBOARD,	// �r���{�[�h
		MODE_STRETCHBILLBOARD,	// �X�g���b�`�r���{�[�h
		MODE_MAX
	};

	CPolygon3D(int nPriority = 5);	// �R���X�g���N�^
	~CPolygon3D();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPolygon3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f });
	float GetWidth(void) { return m_width; }	// �T�C�Y�擾
	float GetHeight(void) { return m_heigth; }	// �T�C�Y�擾
	void SetSize(float width, float height);
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }
	int GetIdxTexture(void) { return m_nIdxTexture; }
	D3DXCOLOR GetColor(void) { return m_col; }
	void SetColor(D3DXCOLOR col);
	void SetTex(D3DXVECTOR2 rd, D3DXVECTOR2 lu);
	void SetFactSB(float fFact) { m_fFactSB = fFact; }
	void SetVtx(void);
	void SetMode(MODE mode);
	MODE GetMode(void) { return m_mode; }
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }
	LPDIRECT3DVERTEXBUFFER9 CreateVtxBuff(int nNumVtx = 4);

private:
	void SetVtxNormal(void);
	void SetVtxStretchBillboard(void);
	void SetMtx(void);
	void SetMtxBillboard(void);

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	D3DXCOLOR m_col;	// �F
	float m_width;	// ��
	float m_heigth;	// ����
	float m_fFactSB;	// �X�g���b�`�r���{�[�h�̂Ƃ��̌��₷���̕␳
	int m_nIdxTexture;	// �e�N�X�`���̔ԍ�
	int m_nNumVtx;	// ���_��
	MODE m_mode;	// ���[�h
};

#endif