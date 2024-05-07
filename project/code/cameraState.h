//*****************************************************
//
// カメラステイト[cameraState.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _CAMERASTATE_H_
#define _CAMERASTATE_H_

//****************************************************
// 前方宣言
//****************************************************
class CCamera;

//****************************************************
// クラスの定義
//****************************************************
// 基底クラス
class CCameraState
{
public:
	virtual void Update(CCamera *pCamera) = 0;

private:
};

// 出現カメラ
class CApperPlayer : public CCameraState
{
public:
	void Update(CCamera *pCamera) override;

private:
};

// プレイヤー追従
class CFollowPlayer : public CCameraState
{
public:
	void Update(CCamera *pCamera) override;

private:
};

// 操作
class CMoveControl : public CCameraState
{
public:
	void Update(CCamera *pCamera) override;

private:

};


#endif