/***************************************************************************************************
**      2018-06-19  ISpectrumData 光谱数据接口。
***************************************************************************************************/

#ifndef ISPECTRUMDATA_H
#define ISPECTRUMDATA_H

#include "HAlgorithmGlobal.h"
#include <QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT ISpectrumData
{
public:
    ISpectrumData() { clear(); }

public:
    void clear()
    {
        Energy.clear();
        TotalEnergy = 0.0;
        MaxEnergy = 0.0;
        PeakWave = 0.0;
        Bandwidth = 0.0;
        EnergyRatio = 0.0;
        RedRatio = 0.0;
        GreenRadio = 0.0;
        BlueRatio = 0.0;
        VisionEnergy = 0.0;
        CoordinateXy = QPointF(0.0, 0.0);
        CoordinateUv = QPointF(0.0, 0.0);
        CoordinateUvp = QPointF(0.0, 0.0);
        ColorTemperature = 2300.0;
        Duv = 0.0;
        DominantWave = 0.0;
        ColorPurity = 0.0;
        RenderingIndex.fill(0, 14);
        RenderingIndexAvg = 0.0;
        Luminous = 0.0;
        SDCM = 0;
    }

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

#endif // ISPECTRUMDATA_H
