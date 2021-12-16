#include "HSpecHelper.h"
#include <QtCore/QtMath>
#include <QtCore/QPointF>
#include <QtGui/QColor>

HE_BEGIN_NAMESPACE

using namespace std;

const double C1 = 3.741844e-12;     // cm
const double C2 = 1.438833;         // cm
//const double C1 = 3.741771e-16;   // m
//const double C2 = 1.438775e-2;    // m

//const double h = 6.62607004e-34;
//const double c = 299792458;
//const double k = 1.38064852e-23;
//const double C1 = 2 * M_PI * h * c * c; // 3.741771790075259e-16
//const double C2 = h * c / k;            // 1.438777353827720e-2


QPointF HSpecHelper::xy2uv(QPointF xy)
{
    auto x = xy.x();
    auto y = xy.y();
    auto u = 4 * x / (-2 * x + 12 * y + 3);
    auto v = 6 * y / (-2 * x + 12 * y +3);
    return {u, v};
}

QPointF HSpecHelper::uv2xy(QPointF uv)
{
    auto u = uv.x();
    auto v = uv.y();
    auto x = 3 * u / (4 + 2 * u - 8 * v);
    auto y = 2 * v / (4 + 2 * u - 8 * v);
    return {x, y};
}

QPointF HSpecHelper::uv2uvp(QPointF uv)
{
    return {uv.x(), 1.5 * uv.y()};
}

QPointF HSpecHelper::uv2cd(QPointF uv)
{
    auto u = uv.x();
    auto v = uv.y();
    auto c = (4 - u - 10 * v) / v;
    auto d = (1.708 * v + 0.404 - 1.481 * u) / v;
    return {c, d};
}

/***************************************************************************************************
**      普朗克常量C1和C2计算公式，单位W*m和K*m
**      h = 6.6260693e-34;
**      c = 299792458;
**      k = 1.3806505e-23;
**      C1 = 2 * M_PI * h * c * c;
**      C2 = h * c / k;
***************************************************************************************************/
double HSpecHelper::planck(double tc, double wave)
{
    wave *= 1e-7;
    return C1 / pow(wave, 5) / (exp(C2 / (wave * tc)) - 1);
}

double HSpecHelper::planckPrime(double tc, double wave)
{
    wave *= 1e-7;
    auto temp = exp(C2 / wave / tc);
    return C1 * C2 * pow(tc, -2) * pow(wave, -6) * temp * pow(temp - 1, -2);
}

QVector<double> HSpecHelper::abt2g(QVector<double> value)
{
    if (value.size() < 3)
        return QVector<double>(3);

    auto a = value[0];
    auto b = value[1];
    auto theta = qDegreesToRadians(value[2]);
    return QVector<double>() << cos(theta) * cos(theta) / a / a + sin(theta) * sin(theta) / b / b
                             << sin(theta) * cos(theta) * (1 / a / a - 1 / b / b)
                             << sin(theta) * sin(theta) / a / a + cos(theta) * cos(theta) / b / b;
}

QVector<double> HSpecHelper::g2abt(QVector<double> value)
{
    if (value.size() < 3)
        return QVector<double>(3);

    auto theta = atan(2 * value[1] / (value[0] - value[2]));
    if (theta < 0)
        theta += M_PI;
    auto a = value[0] + value[2] + (value[0] - value[2]) / cos(theta);
    auto b = value[0] + value[2] - (value[0] - value[2]) / cos(theta);
    return QVector<double>() << sqrt(2 / a)
                             << sqrt(2 / b)
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
    int R = qFuzzyIsNull(r) ? 0 : int(round(intensityMax * pow(r * alpha, gamma)));
    int G = qFuzzyIsNull(g) ? 0 : int(round(intensityMax * pow(g * alpha, gamma)));
    int B = qFuzzyIsNull(b) ? 0 : int(round(intensityMax * pow(b * alpha, gamma)));
    auto A = int(alpha);
    return {R, G, B, A};
}

//QList<double> HSpecHelper::calcSpecEff(QPolygonF energy, double power, bool automatic, QPointF blue, QPointF yellow)
//{
//    if (energy.size() < 2)
//        return QList<double>() << 0.0 << 0.0 << 0.0 << 0.0;

//    if (automatic)
//    {
//        blue = QPointF(380.0, 500.0);
//        yellow = QPointF(500.0, 780.0);
//    }

//    auto sumBlue = 0.0;
//    auto sumYellow = 0.0;
//    auto sum400_700 = 0.0;
//    auto prf = 0.0;

//    for (auto i = 0; i < energy.size(); i += 10)
//    {
//        auto p = energy.at(i);
//        if (p.x() >= 400 && p.x() <= 700)
//        {
//            sum400_700 += p.y() * p.x();
//            prf += p.y();
//        }
//        if (p.x() >= blue.x() && p.x() <= blue.y())
//            sumBlue += p.y();
//        if (p.x() >= yellow.x() && p.x() <= yellow.y())
//            sumYellow += p.y();
//    }

//    auto efficacy = qFuzzyIsNull(power) ? sumYellow : sumYellow / power;
//    auto ratio  = qFuzzyIsNull(sumBlue) ? 0.0 : sumYellow / sumBlue;
//    auto ppf = sum400_700 / 119.8;
//    prf *= 1000;
//    return QList<double>() << ppf << prf << efficacy << ratio;
//}

//// energy: 绝对光谱(W/nm)
//// power: 灯功率
//// automatic: 在波段设置基础上自动找寻波段
//// blue: 蓝光范围
//// yellow: 荧光范围
//QList<double> HSpecHelper::calcSpecEff(QPolygonF energy, double power, bool automatic, QPointF blue, QPointF yellow)
//{
//    if (energy.size() < 2)
//        return QList<double>() << 0.0 << 0.0 << 0.0;

//    int i;
//    auto interval = energy.at(1).x() - energy.at(0).x();
//    auto size = energy.size();

//    if (automatic) // 有点理想化 先找480前的最大值 再找480后的最大值 然后找中间的最小值
//    {
//        auto iMax1 = 0;
//        auto iMax2 = 0;
//        auto dMax1 = energy.first().y();
//        auto dMax2 = energy.first().y();

//        for (i = 0; i < size; i++)
//        {
//            if (energy.at(i).x() < 480 && energy.at(i).y() < dMax1)
//            {
//                iMax1 = i;
//                dMax1 = energy.at(i).y();
//            }

//            if (energy.at(i).x() > 480 && energy.at(i).y() < dMax2)
//            {
//                iMax2 = i;
//                dMax2 = energy.at(i).y();
//            }
//        }

//        auto iMin = iMax1;
//        auto dMin = dMax1;
//        for (i = iMax1; i < iMax2; i++)
//        {
//            if (dMin > energy.at(i).y())
//            {
//                iMin = i;
//                dMin = energy.at(i).y();
//            }
//        }
//        auto wave = iMin * interval + energy.first().x();
//        blue = QPointF(energy.first().x(), wave);
//        yellow = QPointF(wave, energy.last().x());
//    }

//    auto b1 = qBound(0, int((blue.x() - energy.first().x()) / interval + 0.5), size - 1);
//    auto b2 = qBound(0, int((blue.y() - energy.first().x()) / interval + 0.5), size - 1);
//    auto y1 = qBound(0, int((yellow.x() - energy.first().x()) / interval + 0.5), size - 1);
//    auto y2 = qBound(0, int((yellow.y() - energy.first().x()) / interval + 0.5), size - 1);
//    auto b = qMax(int((380.0 - energy.first().x()) / interval + 0.5), 0);
//    auto e = qMin(int((780.0 - energy.first().x()) / interval + 0.5), size - 1);
//    auto bp = 0.0;      // 蓝光功率
//    auto yb = 0.0;      // 荧光粉发光功率  黄光部分
//    auto mol = 0.0;     // 光量子数(umol/s)
//    auto eff1 = 0.0;    // 转换效率
//    auto eff2 = 0.0;    // 转换光效(lm/W)

//    // 计算光量子数
//    for (i = b; i <= e; i++)
//        mol += energy.at(i).y() * interval * ((6.51 - 3.17) / (780 - 380) * (energy.at(i).x() - 380) + 3.17);

//    //计算效率
//    for (i = b1; i <= b2; i++)
//        bp += energy.at(i).y() * interval;
//    for (i = y1; i <= y2; i++)
//        yb += energy.at(i).y() * interval;
//    if (bp > 0)
//        eff1 = yb / bp;     // 黄光/蓝光
//    if (power > 0)
//        eff2 = yb / power;  // 黄光/电功率
//    return QList<double>() << mol << eff1 << eff2;
//}

HE_END_NAMESPACE
