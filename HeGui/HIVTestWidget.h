/***************************************************************************************************
**      2019-11-29  HIVTestWidget
***************************************************************************************************/

#ifndef HIVTESTWIDGET_H
#define HIVTESTWIDGET_H

#include "HAbstractTestWidget.h"

HE_GUI_BEGIN_NAMESPACE

class HIVTestWidgetPrivate;

class HIVTestWidget : public HAbstractTestWidget
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
    void exportExcel();
    void clearResult();
    void handleTestStateChanged(bool b);

private:
    void init();
    void createAction();
    void createToolBar();
    void createWidget();
};

HE_GUI_END_NAMESPACE

#endif // HIVTESTWIDGET_H
