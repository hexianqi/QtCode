/***************************************************************************************************
**      2019-09-16  HModelDemo
***************************************************************************************************/

#pragma once

#include "HeController/HAbstractModel.h"

HE_CONTROLLER_USE_NAMESPACE

class HModelDemoPrivate;

class HModelDemo : public HAbstractModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HModelDemo)

public:
    explicit HModelDemo(QObject *parent = nullptr);
    ~HModelDemo() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    void syncTestData(quint32 type) override;
    void syncMachine(quint32 type) override;
};
