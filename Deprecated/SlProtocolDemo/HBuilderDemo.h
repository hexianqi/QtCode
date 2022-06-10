/***************************************************************************************************
**      2019-09-12  HBuilderDemo
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractBuilder.h"

HE_GUI_USE_NAMESPACE

class HBuilderDemoPrivate;

class HBuilderDemo : public HAbstractBuilder
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBuilderDemo)

public:
    explicit HBuilderDemo(IMainWindow *parent = nullptr);
    ~HBuilderDemo() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    void buildConfigManage() override;
    void buildTestData() override;
    void buildDevice() override;
    void buildThread() override;
    void buildModel() override;
    void buildDatabase() override;
    void buildMenu() override;
    void buildTestWidget() override;
};
