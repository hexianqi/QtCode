/***************************************************************************************************
**      2018-06-19  HSpectrumData 光谱数据接口。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

class HSpecData
{
public:
    HSpecData();

public:
    void clear();

public:
    QPolygonF TestEnergy;
    QPolygonF TestEnergyPercent;
    QPolygonF ReferenceEnergy;
    QPolygonF ReferenceEnergyPercent;
    // 能量参数
    double EnergyTotal;
    double EnergyMax;
    double WavePeak;
    double Bandwidth;
    // 色度参数
    QPointF CoordinateXY;
    QPointF CoordinateUV;
    QPointF CoordinateUVp;
    double WaveDominant;
    double ColorTemperature;
    double ColorPurity;
    double Duv;
    QVector<double> RenderingIndex;
    double RenderingIndexAvg;
    // 明视觉参数
    double VisionFlux;
    double VisionEfficien;
    double RatioRed;
    double RatioGreen;
    double RatioBlue;
    // TM30
    double TM30_Rf;
    double TM30_Rg;
    QList<double> TM30_Rfi;
    QList<double> TM30_hj_at;
    QList<double> TM30_hj_bt;
    QList<double> TM30_hj_ar;
    QList<double> TM30_hj_br;
    QList<double> TM30_hj_atn;
    QList<double> TM30_hj_btn;
    QList<double> TM30_hj_arn;
    QList<double> TM30_hj_brn;
    QList<double> TM30_hj_Rf;
    QList<double> TM30_hj_Rcs;
    QList<double> TM30_hj_Rhs;
};

HE_END_NAMESPACE
