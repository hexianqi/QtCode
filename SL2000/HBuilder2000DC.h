/***************************************************************************************************
**      2019-10-23  HBuilder2000DC
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractBuilder.h"

HE_USE_NAMESPACE

class HBuilder2000DCPrivate;

class HBuilder2000DC : public HAbstractBuilder
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBuilder2000DC)

public:
    explicit HBuilder2000DC(QObject *parent = nullptr);
    ~HBuilder2000DC() override;

public:
    QString typeName() override;

protected:
    HBuilder2000DC(HBuilder2000DCPrivate &p, QObject *parent = nullptr);

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
