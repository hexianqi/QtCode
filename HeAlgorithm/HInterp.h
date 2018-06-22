/***************************************************************************************************
**      2018-06-20  HInterp GSL插值方法类。
**                  http://www.gnu.org/software/gsl/doc/html/interp.html#sec-interpolation
***************************************************************************************************/

#ifndef HINTERPOLATION_H
#define HINTERPOLATION_H

#include "HAlgorithmGlobal.h"
#include <QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HInterp
{
public:
    enum HInterpType
    {
        Linera,             // 线性插值
        Polynomial,         // 多项式插值
        Cspline,            // 具有自然边界条件的三次样条
        CsplinePeriodic,    // 具有周期性边界条件的三次样条
        Akima,              // 具有自然边界条件的非舍入Akima样条
        AkimaPeriodic,      // 具有周期边界条件的非舍入Akima样条
        Steffen             // 最小值和最大值只能出现在数据点上，并且数据点之间永远不会出现虚假振荡。[2.0以上才支持]
    };

public:
    // 求值
    static double eval(QPolygonF basis, double x, HInterpType type = HInterpType::Linera);
    static QVector<double> eval(QPolygonF basis, QVector<double> x, HInterpType type = HInterpType::Linera);
    // 求[a,b:interval]值
    static QPolygonF eval(QPolygonF basis, double a, double b, double interval = 0.1, HInterpType type = HInterpType::Linera);
    // 求一阶导数
    static QVector<double> evalDeriv(QPolygonF basis, QVector<double> x, HInterpType type = HInterpType::Cspline);
    // 求二阶导数
    static QVector<double> evalDeriv2(QPolygonF basis, QVector<double> x, HInterpType type = HInterpType::Cspline);
    // 求[a,b]积分
    double evalInteg(QPolygonF basis, double a, double b, HInterpType type = HInterpType::Linera);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HINTERPOLATION_H
