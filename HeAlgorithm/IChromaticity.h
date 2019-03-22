/***************************************************************************************************
**      2018-06-19  IChromaticity 色度参数计算接口。
***************************************************************************************************/

#ifndef ICHROMATICITY_H
#define ICHROMATICITY_H

#include "HAlgorithmGlobal.h"
#include <QLineF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HSpecData;

class HE_ALGORITHM_EXPORT IChromaticity
{
public:
    // 计算光谱参数
    virtual void calcSpectrum(HSpecData *) = 0;
    // 计算等温线段
    virtual QLineF calcIsothermUv(double tc, double duv) = 0;
    virtual QLineF calcIsothermUv(double tc, double duvB, double duvE) = 0;
    virtual QLineF calcIsothermXy(double tc, double duv) = 0;
    virtual QLineF calcIsothermXy(double tc, double duvB, double duvE) = 0;

public:
    // 导出等温线数据
    virtual bool exportIsotherm(QString fileName, QPointF tc, double interval = 1.0) = 0;
    virtual bool exportIsotherm(QString fileName) = 0;
    // 导出UCS数据
    virtual bool exportCieUcs(QString fileName, QPointF tc = QPointF(1400, 25000), double interval = 1.0) = 0;
};

HE_ALGORITHM_END_NAMESPACE

#endif // ICHROMATICITY_H
