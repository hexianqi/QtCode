/***************************************************************************************************
**      2021-01-18  HBuilder2100DC
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractBuilder.h"

HE_GUI_USE_NAMESPACE

class HBuilder2100DCPrivate;

class HBuilder2100DC : public HAbstractBuilder
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBuilder2100DC)

public:
    explicit HBuilder2100DC(QObject *parent = nullptr);
    ~HBuilder2100DC() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    void buildConfigManage() override;
    void buildTestData() override;
    void buildDevice() override;
    void buildThread() override;
    void buildModel() override;
    void buildMemento() override;
    void buildDatabase() override;
    void buildMenu() override;
    void buildTestWidget() override;
};
