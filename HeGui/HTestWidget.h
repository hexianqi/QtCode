/***************************************************************************************************
**      2020-03-20  HTestWidget 测试窗体。
***************************************************************************************************/

#pragma once

#include "HAbstractTestWidget.h"

HE_BEGIN_NAMESPACE

class HTestWidgetPrivate;

class HTestWidget : public HAbstractTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget)

public:
    explicit HTestWidget(QWidget *parent = nullptr);

protected:
    HTestWidget(HTestWidgetPrivate &p, QWidget *parent = nullptr);

protected slots:
    void closeEvent(QCloseEvent *) override;

protected:
    virtual void init();
    virtual void createAction();
    virtual void createWidget() = 0;
    virtual void createMenu() = 0;
    virtual void createToolBar() = 0;
    virtual void initWidget() = 0;
    virtual void initToolBar();
    virtual void initStyleSheet();
    virtual void clearResult() = 0;
    virtual void saveResult();
    virtual void exportExcel() = 0;
    virtual void readSettings();
    virtual void writeSettings();
};

HE_END_NAMESPACE
