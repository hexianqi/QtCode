#ifndef HBUILDER2000_H
#define HBUILDER2000_H

#include "HeGui/HAbstractBuilder.h"

HE_GUI_USE_NAMESPACE

class HBuilder2000Private;

class HBuilder2000 : public HAbstractBuilder
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBuilder2000)

public:
    explicit HBuilder2000(IMainWindow *parent = nullptr);
    ~HBuilder2000();

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
    void buildTestWidget() override;
};

#endif // HBUILDER2000_H
