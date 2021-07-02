/***************************************************************************************************
**      2018-06-19  HSpectrum 常用的光谱计算公式类。
***************************************************************************************************/

#pragma once

#include "HAlgorithmGlobal.h"

class QPointF;
class QPolygonF;
class QColor;

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HSpecHelper
{
public:
    // 色坐标转换
    static QPointF xy2uv(QPointF xy);
    static QPointF uv2xy(QPointF uv);
    static QPointF uv2uvp(QPointF uv);
    static QPointF uv2cd(QPointF uv);
    // 普朗克公式。波长单位为nm
    static double planck(double wave, double tc);
    // 普朗克公式关于色温导数。波长单位为nm
    static double planckPrime(double wave, double tc);
    // 色容差转换
    static QVector<double> abt2g(QVector<double> value);
    static QVector<double> g2abt(QVector<double> value);
    // 波长转颜色
    static QColor wave2color(double wave, double gamma = 0.8, double intensityMax = 255.0);
};

HE_ALGORITHM_END_NAMESPACE
