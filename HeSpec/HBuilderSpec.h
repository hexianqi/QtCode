#ifndef HBUILDERSPEC_H
#define HBUILDERSPEC_H

#include "HeGui/HAbstractBuilder.h"

HE_GUI_USE_NAMESPACE

class HBuilderSpecPrivate;

class HBuilderSpec : public HAbstractBuilder
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBuilderSpec)

public:
    explicit HBuilderSpec(QWidget *parent = nullptr);
    ~HBuilderSpec() override;

public:
    QString typeName() override;

protected:
    void buildFactory() override;
    void buildConfigManage() override;
    void buildTestData() override;
    void buildDevice() override;
    void buildThread() override;
    void buildModel() override;
    void buildTestWidget() override;
};

#endif // HBUILDERSPEC_H
