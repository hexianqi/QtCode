/***************************************************************************************************
**      2018-06-20  HInterp GSL插值函数类。
**                  http://www.gnu.org/software/gsl/doc/html/interp.html
***************************************************************************************************/

#pragma once

#include "HAlgorithmGlobal.h"
#include <QtGui/QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HInterp
{
public:
    enum InterpType
    {
        Linera,             // 线性插值
        Polynomial,         // 多项式插值
        Cspline,            // 具有自然边界条件的三次样条
        CsplinePeriodic,    // 具有周期性边界条件的三次样条
        Akima,              // 具有自然边界条件的非舍入Akima样条
        AkimaPeriodic,      // 具有周期边界条件的非舍入Akima样条
        Steffen             // 最小值和最大值只能出现在数据点上，并且数据点之间永远不会出现虚假振荡
    };

public:
    // 求值
    static double eval(QPolygonF basis, double x, InterpType type = Linera);
    static QVector<double> eval(QPolygonF basis, QVector<double> xa, InterpType type = Linera);
    // 求[a,b:interval]值
    static QPolygonF eval(QPolygonF basis, double a, double b, double interval = 0.1, InterpType type = Linera);
    // 求一阶导数值
    static QVector<double> eval_deriv(QPolygonF basis, QVector<double> xa, InterpType type = Cspline);
    // 求二阶导数值
    static QVector<double> eval_deriv2(QPolygonF basis, QVector<double> xa, InterpType type = Cspline);
    // 求[a,b]积分值
    static double eval_integ(QPolygonF basis, double a, double b, InterpType type = Linera);
};

HE_ALGORITHM_END_NAMESPACE
