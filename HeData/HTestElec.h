/***************************************************************************************************
**      2019-10-21  HTestElec
***************************************************************************************************/

#pragma once

#include "HDataType.h"
#include "HTestData.h"

HE_BEGIN_NAMESPACE

class HTestElecPrivate;

class HTestElec : public HTestData
{
    Q_DECLARE_PRIVATE(HTestElec)

public:
    explicit HTestElec();

public:
    QString typeName() override;

public:
    bool setCalibrate(void *) override;
    bool setData(QString type, QVariant value) override;

protected:
    HTestElec(HTestElecPrivate &);

protected:
    bool setModule(int value);
    bool setGears(HElecType type, int value);
    bool setParam(HElecType type, double value);
    void calcRelation(HElecType type);
};

HE_END_NAMESPACE
