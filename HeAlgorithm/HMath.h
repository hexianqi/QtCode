/***************************************************************************************************
**      2018-06-19  HMath 常用的数值计算公式类。
***************************************************************************************************/

#ifndef HMATH_H
#define HMATH_H

#include "HAlgorithmGlobal.h"

class QPointF;
class QPolygonF;

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HMath
{
public:
    // 插值
    static double interpolate(double x, double x1, double y1, double x2, double y2);
    static double interpolate(double x, QPointF p1, QPointF p2);
    static double interpolate(double x, QPolygonF poly);
//    static QPolygonF interpolate(QPolygonF poly, double x1, double x2, double interval = 0.1);
//    static QPolygonF interpolate(QPolygonF poly, double x1, double x2, double defaultValue, double interval);
    static double interpolateY(double y, QPointF p1, QPointF p2);
    static double interpolateY(double y, QPolygonF poly);
    // 多项式拟合
    // static bool polyfit(QVector<QPointF> points, QVector<double> &factors);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HMATH_H
