#pragma once

#include "HTestSetWidget1000RGB.h"
#include "HeGui/HAbstractTestSetWidget_p.h"

struct CrystalData
{
    int Id = 0;
    bool enable = false;
    double IntegralTime = 0.0;
    QVector<int> sourceIo;
};

class HTestSetWidget1000RGBPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    HTestSetWidget1000RGBPrivate();

public:
    int index = 0;
    bool first = true;
    QVector<CrystalData> crystalDatas;
};


