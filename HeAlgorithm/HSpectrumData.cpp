#include "HSpecData.h"

HE_ALGORITHM_BEGIN_NAMESPACE

HSpecData::HSpecData()
{
    clear();
}

void HSpecData::clear()
{
    Energy.clear();
    EnergyPercent.clear();
    TotalEnergy = 0.0;
    MaxEnergy = 0.0;
    PeakWave = 0.0;
    Bandwidth = 0.0;
    CoordinateXy = QPointF(0.0, 0.0);
    CoordinateUv = QPointF(0.0, 0.0);
    CoordinateUvp = QPointF(0.0, 0.0);
    ColorTemperature = 2300.0;
    Duv = 0.0;
    DominantWave = 0.0;
    ColorPurity = 0.0;
    RenderingIndex.fill(0, 14);
    RenderingIndexAvg = 0.0;
    VisionEnergyRatio = 0.0;
    RedRatio = 0.0;
    GreenRatio = 0.0;
    BlueRatio = 0.0;
    VisionEnergy = 0.0;
    LuminousFlux = 0.0;
    LuminousPower = 0.0;
}

HE_ALGORITHM_END_NAMESPACE
