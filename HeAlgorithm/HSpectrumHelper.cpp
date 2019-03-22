#include "HSpecHelper.h"
#include <QPolygonF>
#include <QtMath>

HE_ALGORITHM_BEGIN_NAMESPACE

const double C1 = 3.741844e-12;
const double C2 = 1.438833;

QPointF HSpecHelper::xy2uv(QPointF xy)
{
    auto x = xy.x();
    auto y = xy.y();
    auto u = 4 * x / (-2 * x + 12 * y + 3);
    auto v = 6 * y / (-2 * x + 12 * y +3);
    return QPointF(u, v);
}

QPointF HSpecHelper::uv2xy(QPointF uv)
{
    auto u = uv.x();
    auto v = uv.y();
    auto x = 3 * u / (4 + 2 * u - 8 * v);
    auto y = 2 * v / (4 + 2 * u - 8 * v);
    return QPointF(x, y);
}

QPointF HSpecHelper::uv2uvp(QPointF uv)
{
    return QPointF(uv.x(), 1.5 * uv.y());
}

QPointF HSpecHelper::uv2cd(QPointF uv)
{
    auto u = uv.x();
    auto v = uv.y();
    auto c = (4 - u - 10 * v) / v;
    auto d = (1.708 * v + 0.404 - 1.481 * u) / v;
    return QPointF(c, d);
}

/***************************************************************************************************
**      普朗克常量C1和C2计算公式，单位W*m和K*m
**      h = 6.6260693e-34;
**      c = 299792458;
**      k = 1.3806505e-23;
**      C1 = 2 * M_PI * h * c * c;
**      C2 = h * c / k;
***************************************************************************************************/
double HSpecHelper::planck(double wave, double tc)
{
    wave *= 1e-7;
    return C1 / qPow(wave, 5) / (qExp(C2 / (wave * tc)) - 1);
}

double HSpecHelper::planckPrime(double wave, double tc)
{
    wave *= 1e-7;
    auto temp = qExp(C2 / wave / tc);
    return C1 * C2 * qPow(tc, -2) * qPow(wave, -6) * temp * qPow(temp - 1, -2);
}

HE_ALGORITHM_END_NAMESPACE
