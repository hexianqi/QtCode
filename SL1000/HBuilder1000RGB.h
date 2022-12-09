/***************************************************************************************************
**      2022-12-06  HBuilder1000RGB
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractBuilder.h"

HE_USE_NAMESPACE

class HBuilder1000RGBPrivate;

class HBuilder1000RGB : public HAbstractBuilder
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBuilder1000RGB)

public:
    explicit HBuilder1000RGB(QObject *parent = nullptr);
    ~HBuilder1000RGB() override;

public:
    QString typeName() override;

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



