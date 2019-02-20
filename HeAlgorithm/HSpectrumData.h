/***************************************************************************************************
**      2018-06-19  HSpectrumData 光谱数据接口。
***************************************************************************************************/

#ifndef HSPECTRUMDATA_H
#define HSPECTRUMDATA_H

#include "HAlgorithmGlobal.h"
#include <QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HSpectrumData
{
public:
    HSpectrumData();

public:
    void clear();

public:
    // 能量参数
    QPolygonF Energy;
    double TotalEnergy;
    double MaxEnergy;
    double PeakWave;
    double Bandwidth;
    // 明视觉参数
    double EnergyRatio;
    double RedRatio;
    double GreenRadio;
    double BlueRatio;
    double VisionEnergy;
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
    // 其他
    double Luminous;
    double SDCM;
};

HE_ALGORITHM_END_NAMESPACE

#endif // HSPECTRUMDATA_H
