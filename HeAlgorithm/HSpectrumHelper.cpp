#include "HSpecHelper.h"
#include <QtCore/QtMath>
#include <QtGui/QColor>
#include <QtGui/QPolygonF>

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

QVector<double> HSpecHelper::abt2g(QVector<double> value)
{
    if (value.size() < 3)
        return QVector<double>(3);

    auto a = value[0];
    auto b = value[1];
    auto theta = qDegreesToRadians(value[2]);
    return QVector<double>() << qCos(theta) * qCos(theta) / a / a + qSin(theta) * qSin(theta) / b / b
                             << qSin(theta) * qCos(theta) * (1 / a / a - 1 / b / b)
                             << qSin(theta) * qSin(theta) / a / a + qCos(theta) * qCos(theta) / b / b;
}

QVector<double> HSpecHelper::g2abt(QVector<double> value)
{
    if (value.size() < 3)
        return QVector<double>(3);

    auto theta = qAtan(2 * value[1] / (value[0] - value[2]));
    if (theta < 0)
        theta += M_PI;
    auto a = value[0] + value[2] + (value[0] - value[2]) / qCos(theta);
    auto b = value[0] + value[2] - (value[0] - value[2]) / qCos(theta);
    return QVector<double>() << qSqrt(2 / a)
                             << qSqrt(2 / b)
                             << qRadiansToDegrees(theta/2);
}

QColor HSpecHelper::wave2color(double wave, double gamma, double intensityMax)
{
    double r, g, b, alpha;
    if (wave >= 380.0 && wave < 440.0)
    {
        r = -1.0 * (wave - 440.0) / (440.0 - 380.0);
        g = 0.0;
        b = 1.0;
    }
    else if (wave >= 440.0 && wave < 490.0)
    {
        r = 0.0;
        g = (wave - 440.0) / (490.0 - 440.0);
        b = 1.0;
    }
    else if (wave >= 490.0 && wave < 510.0)
    {
        r = 0.0;
        g = 1.0;
        b = -1.0 * (wave - 510.0) / (510.0 - 490.0);
    }
    else if (wave >= 510.0 && wave < 580.0)
    {
        r = (wave - 510.0) / (580.0 - 510.0);
        g = 1.0;
        b = 0.0;
    }
    else if (wave >= 580.0 && wave < 645.0)
    {
        r = 1.0;
        g = -1.0 * (wave - 645.0) / (645.0 - 580.0);
        b = 0.0;
    }
    else if (wave >= 645.0 && wave <= 780.0)
    {
        r = 1.0;
        g = 0.0;
        b = 0.0;
    }
    else
    {
        r = 0.0;
        g = 0.0;
        b = 0.0;
    }

    // 在可见光谱的边缘处强度较低。
    if (wave >= 380.0 && wave < 420.0)
        alpha = 0.30 + 0.70 * (wave - 380.0) / (420.0 - 380.0);
    else if (wave >= 420.0 && wave < 701.0)
        alpha = 1.0;
    else if (wave >= 701.0 && wave < 780.0)
        alpha = 0.30 + 0.70 * (780.0 - wave) / (780.0 - 700.0);
    else
        alpha = 0.0;

    // 1953年在引入NTSC电视时,计算具有荧光体的监视器的亮度公式如下
    // int Y = int(0.212671*r + 0.715160*g + 0.072169*b);

    // 伽马射线 gamma
    // 照明强度 intensityMax
    int R = qFuzzyIsNull(r) ? 0 : int(std::round(intensityMax * std::pow(r * alpha, gamma)));
    int G = qFuzzyIsNull(g) ? 0 : int(std::round(intensityMax * std::pow(g * alpha, gamma)));
    int B = qFuzzyIsNull(b) ? 0 : int(std::round(intensityMax * std::pow(b * alpha, gamma)));
    auto A = int(alpha);
    return QColor(R, G, B, A);
}

HE_ALGORITHM_END_NAMESPACE
