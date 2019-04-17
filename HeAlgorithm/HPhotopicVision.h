/***************************************************************************************************
**      2018-06-19  HPhotopicVision 明视觉比例系数计算类。
***************************************************************************************************/


#ifndef HPHOTOPICVISION_H
#define HPHOTOPICVISION_H

#include "HAlgorithmGlobal.h"
#include <QtGui/QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HPhotopicVision
{
public:
    HPhotopicVision();

public:
    // 计算明视觉光谱能量比、红色比、蓝色比、绿色比
    void calcVisionRatio(QPolygonF value, double &energy, double &red, double &green, double &blue);
    // 计算明视觉光谱能量
    double calcVisionEnergy(QPolygonF value);

protected:
    void readStandard();

protected:
    QPolygonF _stdData;
};

HE_ALGORITHM_END_NAMESPACE

#endif // HPHOTOPICVISION_H
