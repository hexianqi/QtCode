/***************************************************************************************************
**      2019-09-19  HModelSpec
***************************************************************************************************/

#pragma once

#include "HeController/HAbstractModel.h"

HE_CONTROLLER_USE_NAMESPACE

class HModelSpecPrivate;

class HModelSpec : public HAbstractModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HModelSpec)

public:
    explicit HModelSpec(QObject *parent = nullptr);
    ~HModelSpec() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    void syncTestData(quint32 type) override;
    void syncDevice(quint32 type) override;
};
