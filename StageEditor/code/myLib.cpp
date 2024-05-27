//*****************************************************
//
// オリジナルライブラリ[myLib.h.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "myLib.h"

//=================================================================================
// スプライン
//=================================================================================
//=====================================================
// 初期化処理
//=====================================================
void CSpline::Init(const std::vector<double>& x, const std::vector<double>& y)
{
    // 引数の受け取り
    this->x = x;
    this->y = y;
    int nSize = x.size();

    // 配列の初期化
    a = y;
    b.resize(nSize, 0.0);
    c.resize(nSize, 0.0);
    d.resize(nSize, 0.0);

    // 区間の距離計算
    std::vector<double> dist(nSize - 1);
    for (int i = 0; i < nSize - 1; ++i)
    {
        dist[i] = x[i + 1] - x[i];
    }

    // 三重対角系のセットアップ
    std::vector<double> alpha(nSize - 1);
    std::vector<double> beta(nSize - 1);

    for (int i = 1; i < nSize - 1; ++i)
    {
        alpha[i] = 3.0 / dist[i] * (a[i + 1] - a[i]) - 3.0 / dist[i - 1] * (a[i] - a[i - 1]);
    }

    // cの三重対角系を解く
    std::vector<double> l(nSize);
    std::vector<double> mu(nSize);
    std::vector<double> z(nSize);
    l[0] = 1.0;
    mu[0] = 0.0;
    z[0] = 0.0;

    for (int i = 1; i < nSize - 1; ++i)
    {
        l[i] = 2.0 * (x[i + 1] - x[i - 1]) - dist[i - 1] * mu[i - 1];
        mu[i] = dist[i] / l[i];
        z[i] = (alpha[i] - dist[i - 1] * z[i - 1]) / l[i];
    }

    l[nSize - 1] = 1.0;
    z[nSize - 1] = 0.0;
    c[nSize - 1] = 0.0;

    for (int j = nSize - 2; j >= 0; --j)
    {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (a[j + 1] - a[j]) / dist[j] - dist[j] * (c[j + 1] + 2.0 * c[j]) / 3.0;
        d[j] = (c[j + 1] - c[j]) / (3.0 * dist[j]);
    }
}

//=====================================================
// 高さの計算
//=====================================================
double CSpline::Interpolate(double xi)
{
    int n = x.size();
    int i = 0;

    while (i < n && xi > x[i])
    {
        ++i;
    }
    if (i >= n)
    {
        i = n - 1;
    }

    double dx = xi - x[i];
    return a[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;
}