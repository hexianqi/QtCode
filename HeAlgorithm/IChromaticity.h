/***************************************************************************************************
**      2018-06-19  IChromaticity 色度参数计算接口。
***************************************************************************************************/

#pragma once

#include "HAlgorithmGlobal.h"
#include <QtCore/QLineF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HSpecData;

class IChromaticity
{
public:
    // 计算光谱参数
    virtual void calcSpectrum(HSpecData *) = 0;
    // 计算等温线段
    virtual QLineF calcIsothermUV(double tc, double duv) = 0;
    virtual QLineF calcIsothermUV(double tc, double duvB, double duvE) = 0;
    virtual QLineF calcIsothermXY(double tc, double duv) = 0;
    virtual QLineF calcIsothermXY(double tc, double duvB, double duvE) = 0;

public:
    // 导出等温线数据
    virtual bool exportIsotherm(const QString &fileName, QPointF tc, double interval = 1.0) = 0;
    virtual bool exportIsotherm(const QString &fileName) = 0;
    // 导出UCS数据
    virtual bool exportCieUcs(const QString &fileName, QPointF tc = QPointF(1400, 25000), double interval = 1.0) = 0;
};

HE_ALGORITHM_END_NAMESPACE
