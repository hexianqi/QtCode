/***************************************************************************************************
**      2020-05-25  HTestLuminous
***************************************************************************************************/

#pragma once

#include "HTestData.h"

HE_BEGIN_NAMESPACE

class HTestLuminousPrivate;

class HTestLuminous : public HTestData
{
    Q_DECLARE_PRIVATE(HTestLuminous)

public:
    explicit HTestLuminous();

public:
    QString typeName() override;

public:
    bool setCalibrate(void *) override;
    bool setData(QString type, QVariant value) override;
    QVariant handleOperation(QString type, QVariant value = QVariant()) override;

protected:
    HTestLuminous(HTestLuminousPrivate &);

protected:
    bool setModule(int value);
    bool setType(QString value);
    bool setGears(int value);
    bool setSample(double value);
    bool matchGears();
};

HE_END_NAMESPACE

