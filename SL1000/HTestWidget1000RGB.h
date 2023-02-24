#pragma once

#include "HeGui/HTestWidget.h"

HE_USE_NAMESPACE

class HTestWidget1000RGBPrivate;

class HTestWidget1000RGB : public HTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget1000RGB)

public:
    explicit HTestWidget1000RGB(QWidget *parent = nullptr);
    ~HTestWidget1000RGB();

public:
    QString typeName() override;

protected:
    void init() override;
    void createWidget() override;
    void createMenu() override;
    void createToolBar() override;
    void initWidget() override;
    void clearResult() override;
    void exportExcel() override;
    void handleAction(HActionType) override;

protected slots:
    void handleStateChanged(bool);
    void handleResultChanged(HActionType, bool);

protected:
    void resetSpec();
    void resetGrade();
    void refreshWidget(bool append);
};

