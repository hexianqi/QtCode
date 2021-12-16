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
    void setData(QString type, QVariant value) override;
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

HE_END_NAMESPACE

