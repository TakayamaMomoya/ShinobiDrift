//*****************************************************
//
// オリジナルライブラリ[myLib.h.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _MYLIB_H_
#define _MYLIB_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CSpline
{
private:
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    std::vector<double> d;

public:
    CSpline() {};
    void Init(const std::vector<double>& x, const std::vector<double>& y);

    double Interpolate(double xi);
};
#endif