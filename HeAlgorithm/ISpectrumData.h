#ifndef ISPECTRUMDATA_H
#define ISPECTRUMDATA_H

#include "HeAlgorithm_global.h"

#include <QPolygonF>

namespace He {
namespace Algorithm {
namespace Spectrum {

// 光谱数据
class HEALGORITHM_EXPORT ISpectrumData
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
        SpectrueLuminous = 0.0;
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
    double SpectrueLuminous;
    double SDCM;
};

} // namespace Spectrum
} // namespace Algorithm
} // namespace He


#endif // ISPECTRUMDATA_H
