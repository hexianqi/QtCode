/***************************************************************************************************
**      2023-03-27  HBuilder1000I
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractBuilder.h"

HE_USE_NAMESPACE

class HBuilder1000IPrivate;

class HBuilder1000I : public HAbstractBuilder
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBuilder1000I)

public:
    explicit HBuilder1000I(QObject *parent = nullptr);
    ~HBuilder1000I() override;

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



