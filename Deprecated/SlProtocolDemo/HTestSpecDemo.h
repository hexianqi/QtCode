/***************************************************************************************************
**      2019-10-02  HTestSpecDemo
***************************************************************************************************/

#pragma once

#include "HeData/HTestSpec.h"

HE_DATA_USE_NAMESPACE

class HTestSpecDemoPrivate;

class HTestSpecDemo : public HTestSpec
{
    Q_DECLARE_PRIVATE(HTestSpecDemo)

public:
    explicit HTestSpecDemo();
    ~HTestSpecDemo() override;

public:
    bool setSample(QVector<double> value, bool avg = false) override;
    bool setEnergy(QPolygonF value, double percent);
    QVector<double> stdCurve();

protected:
    HTestSpecDemo(HTestSpecDemoPrivate &);
};
