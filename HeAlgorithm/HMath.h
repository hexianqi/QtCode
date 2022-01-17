/***************************************************************************************************
**      2018-06-19  HMath 常用的数值计算公式类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QVector>

class QPointF;
class QPolygonF;

HE_BEGIN_NAMESPACE

class HMath
{
public:
    // 求和
    static double sum(const QVector<double> &);
    // 平均值
    static double mean(const QVector<double> &);
    // 百分比
    static QVector<double> percent(const QVector<double> &);
    static QPolygonF percentY(const QPolygonF &);
    // 插值
    static double interpolate(double x, double x1, double y1, double x2, double y2);
    static double interpolate(double x, QPointF p1, QPointF p2);
    static double interpolate(double x, const QPolygonF &poly);
    static QPolygonF interpolate(const QPolygonF &poly, double x1, double x2, double interval = 0.1);
    static double interpolateY(double y, QPointF p1, QPointF p2);
    static double interpolateY(double y, const QPolygonF &poly);
    // 多项式拟合
    // static bool polyfit(QVector<QPointF> points, QVector<double> &factors);

public:
    // 计算椭圆
    static QPolygonF calcEllipse(QPointF center, double r, double theta, double a, double b);
};

HE_END_NAMESPACE
