/***************************************************************************************************
**      2021-02-02  HBuilder2000AC
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractBuilder.h"

HE_GUI_USE_NAMESPACE

class HBuilder2000ACPrivate;

class HBuilder2000AC : public HAbstractBuilder
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBuilder2000AC)

public:
    explicit HBuilder2000AC(QObject *parent = nullptr);
    ~HBuilder2000AC() override;

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
