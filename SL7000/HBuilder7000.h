/***************************************************************************************************
**      2022-01-31  HBuilder7000
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractBuilder.h"

HE_USE_NAMESPACE

class HBuilder7000Private;

class HBuilder7000 : public HAbstractBuilder
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBuilder7000)

public:
    explicit HBuilder7000(QObject *parent = nullptr);
    ~HBuilder7000() override;

public:
    QString typeName() override;

protected:
    HBuilder7000(HBuilder7000Private &p, QObject *parent = nullptr);

protected:
    void buildConfigManage() override;
    void buildTestData() override;
    void buildTemplate() override;
    void buildDevice() override;
    void buildThread() override;
    void buildModel() override;
    void buildMemento() override;
    void buildDatabase() override;
    void buildMenu() override;
    void buildTestWidget() override;
};
