/***************************************************************************************************
**      2018-06-19  HSpectrum 常用的光谱计算公式类。
***************************************************************************************************/

#ifndef HSPECTRUM_H
#define HSPECTRUM_H

#include "HAlgorithmGlobal.h"

class QPointF;

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HSpectrum
{
public:
    //色坐标转换
    static QPointF xy2uv(QPointF xy);
    static QPointF uv2xy(QPointF uv);
    static QPointF uv2uvp(QPointF uv);
    static QPointF uv2cd(QPointF uv);
    //普朗克公式。波长单位为nm
    static double planck(double wave, double tc);
    //普朗克公式关于色温导数。波长单位为nm
    static double planckPrime(double wave, double tc);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HSPECTRUM_H
