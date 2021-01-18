/***************************************************************************************************
**      2019-10-23  HBuilder2000DC
***************************************************************************************************/

#ifndef HBUILDER2000DC_H
#define HBUILDER2000DC_H

#include "HeGui/HAbstractBuilder.h"

HE_GUI_USE_NAMESPACE

class HBuilder2000DCPrivate;

class HBuilder2000DC : public HAbstractBuilder
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBuilder2000DC)

public:
    explicit HBuilder2000DC(QObject *parent = nullptr);
    ~HBuilder2000DC() override;

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

#endif // HBUILDER2000DC_H
