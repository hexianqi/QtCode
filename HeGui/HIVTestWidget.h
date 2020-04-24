/***************************************************************************************************
**      2019-11-29  HIVTestWidget
***************************************************************************************************/

#ifndef HIVTESTWIDGET_H
#define HIVTESTWIDGET_H

#include "HTestWidget.h"

HE_GUI_BEGIN_NAMESPACE

class HIVTestWidgetPrivate;

class HIVTestWidget : public HTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HIVTestWidget)

public:
    explicit HIVTestWidget(QWidget *parent = nullptr);
    ~HIVTestWidget() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    bool setTest(bool b) override;
    void handleAction(HActionType action) override;

protected:
    void createWidget() override;
    void createMenu() override;
    void createToolBar() override;
    void clearResult() override;
    void exportExcel() override;
    void handleStateChanged(bool b);
};

HE_GUI_END_NAMESPACE

#endif // HIVTESTWIDGET_H
