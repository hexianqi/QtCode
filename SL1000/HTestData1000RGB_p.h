#pragma once

#include "HTestData1000RGB.h"
#include "HeData/HTestData_p.h"
#include "HeData/IElecCalibrate.h"
#include "HeData/IElecCalibrateCollection.h"
#include <QtCore/QVector>

class HTestData1000RGBPrivate : public HTestDataPrivate
{
public:
    HTestData1000RGBPrivate();

public:
    IElecCalibrateCollection *collection = nullptr;
    IElecCalibrate *calibrate = nullptr;
    int currentGears = 0;
    QVector<int> sourceIo;
    QVector<int> outputCurrentF;
    QVector<double> outputCurrentR;
};
