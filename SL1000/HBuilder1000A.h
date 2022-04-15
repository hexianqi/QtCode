/***************************************************************************************************
**      2022-04-12  HBuilder1000A
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractBuilder.h"

HE_USE_NAMESPACE

class HBuilder1000APrivate;

class HBuilder1000A : public HAbstractBuilder
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBuilder1000A)

public:
    explicit HBuilder1000A(QObject *parent = nullptr);
    ~HBuilder1000A() override;

public:
    QString typeName() override;

protected:
    HBuilder1000A(HBuilder1000APrivate &p, QObject *parent = nullptr);

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
