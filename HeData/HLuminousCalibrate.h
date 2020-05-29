/***************************************************************************************************
**      2020-05-22  HLuminousCalibrate 光校准数据类。
***************************************************************************************************/

#pragma once

#include "ILuminousCalibrate.h"

HE_DATA_BEGIN_NAMESPACE

class HLuminousCalibratePrivate;

class HLuminousCalibrate : public ILuminousCalibrate
{
    Q_DECLARE_PRIVATE(HLuminousCalibrate)

public:
    explicit HLuminousCalibrate();
    virtual ~HLuminousCalibrate() = default;

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void setTotalGears(int value) override;
    int totalGears() override;
    double toReal(double value, QString type, int index = 0) override;

protected:
    HLuminousCalibrate(HLuminousCalibratePrivate &);
};

HE_DATA_END_NAMESPACE

