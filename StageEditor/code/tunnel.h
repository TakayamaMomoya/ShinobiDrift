//*****************************************************
//
// トンネルの処理[tunnel.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _TUNNEL_H_	// 二重インクルード防止
#define _TUNNEL_H_

//*****************************************************
// インクルード
//*****************************************************
#include "meshcylinder.h"
#include "meshRoad.h"

//*****************************************************
// クラス定義
//*****************************************************
class CTunnel : public CMeshCylinder
{
public:
	CTunnel(int nPriority = 5);	// コンストラクタ
	~CTunnel();	// デストラクタ

	// メンバ変数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CTunnel *Create(std::vector<CMeshRoad::SInfoRoadPoint>::iterator itStart, std::vector<CMeshRoad::SInfoRoadPoint>::iterator itEnd);

private:
};
#endif