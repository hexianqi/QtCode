#include "HSpecData.h"

HE_BEGIN_NAMESPACE

HSpecData::HSpecData()
{
    clear();
}

void HSpecData::clear()
{
    TestEnergy.clear();
    TestEnergyPercent.clear();
    ReferenceEnergy.clear();
    ReferenceEnergyPercent.clear();
    EnergyTotal = 0.0;
    EnergyMax = 0.0;
    WavePeak = 0.0;
    Bandwidth = 0.0;
    CoordinateXY = QPointF(0.0, 0.0);
    CoordinateUV = QPointF(0.0, 0.0);
    CoordinateUVp = QPointF(0.0, 0.0);
    ColorTemperature = 2300.0;
    Duv = 0.0;
    WaveDominant = 0.0;
    ColorPurity = 0.0;
    RenderingIndex.fill(0, 15);
    RenderingIndexAvg = 0.0;
    VisionFlux = 0.0;
    VisionEfficien = 0.0;
    RatioRed = 0.0;
    RatioGreen = 0.0;
    RatioBlue = 0.0;
    TM30_Rf = 0.0;
    TM30_Rg = 0.0;
}

HE_END_NAMESPACE
