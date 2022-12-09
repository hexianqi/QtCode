/***************************************************************************************************
**      2022-12-06  HTestRGB
***************************************************************************************************/

#pragma once

#include "HeData/HTestData.h"
#include "HeData/HDataType.h"

HE_USE_NAMESPACE

class HTestData1000RGBPrivate;

class HTestData1000RGB : public HTestData
{
    Q_DECLARE_PRIVATE(HTestData1000RGB)

public:
    explicit HTestData1000RGB();

public:
    QString typeName() override;

public:
    bool setCalibrate(void *) override;
    bool setData(QString type, QVariant value) override;
    QVariant data(QString type) override;

protected:
    bool setModule(int value);
    bool setCurrentGears(int value);
    QVector<double> calcSample(HElecType type, QVariant value, QString name, bool calcIndex = false);
//    void calcRelation(HElecType type);
};




