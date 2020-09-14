/***************************************************************************************************
**      2020-05-25  HTestLuminous
***************************************************************************************************/

#pragma once

#include "ITestLuminous.h"

HE_DATA_BEGIN_NAMESPACE

class HTestLuminousPrivate;

class HTestLuminous : public ITestLuminous
{
    Q_DECLARE_PRIVATE(HTestLuminous)

public:
    explicit HTestLuminous();

public:
    QString typeName() override;

public:
    void setData(QString type, QVariant value) override;
    bool setCalibrate(ILuminousCalibrateCollection *) override;
    QVariant handleOperation(QString type, QVariant value = QVariant()) override;

protected:
    HTestLuminous(HTestLuminousPrivate &);

protected:
    void setModule(int value);
    void setType(QString value);
    void setGears(int value);
    void setSample(double value);
    bool matchGears();
};

HE_DATA_END_NAMESPACE

