/***************************************************************************************************
**      2018-06-19  HSpectrumData 光谱数据接口。
***************************************************************************************************/

#pragma once

#include "HAlgorithmGlobal.h"
#include <QtGui/QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HSpecData
{
public:
    HSpecData();

public:
    void clear();

public:
    // 能量参数
    QPolygonF Energy;
    QPolygonF EnergyPercent;
    double TotalEnergy;
    double MaxEnergy;
    double PeakWave;
    double Bandwidth;
    // 色度参数
    QPointF CoordinateUv;
    QPointF CoordinateXy;
    QPointF CoordinateUvp;
    double ColorTemperature;
    double Duv;
    double DominantWave;
    double ColorPurity;
    QVector<double> RenderingIndex;
    double RenderingIndexAvg;
    // 明视觉参数
    double VisionFlux;
    double VisionEfficien;
    double RedRatio;
    double GreenRatio;
    double BlueRatio;
};

HE_ALGORITHM_END_NAMESPACE
