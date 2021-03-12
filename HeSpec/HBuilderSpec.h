#pragma once

#include "HeGui/HAbstractBuilder.h"

HE_GUI_USE_NAMESPACE

class HBuilderSpecPrivate;

class HBuilderSpec : public HAbstractBuilder
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBuilderSpec)

public:
    explicit HBuilderSpec(QObject *parent = nullptr);
    ~HBuilderSpec() override;

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
