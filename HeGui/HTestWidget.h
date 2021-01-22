/***************************************************************************************************
**      2020-03-20  HTestWidget 测试窗体。
***************************************************************************************************/

#ifndef HTESTWIDGET_H
#define HTESTWIDGET_H

#include "HAbstractTestWidget.h"

HE_GUI_BEGIN_NAMESPACE

class HTestWidgetPrivate;

class HE_GUI_EXPORT HTestWidget : public HAbstractTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget)

public:
    explicit HTestWidget(QWidget *parent = nullptr);

protected:
    HTestWidget(HTestWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    virtual void init();
    virtual void createAction();
    virtual void createWidget() = 0;
    virtual void createMenu() = 0;
    virtual void createToolBar() = 0;
    virtual void initWidget() = 0;
    virtual void initToolBar();
    virtual void clearResult() = 0;
    virtual void exportExcel() = 0;
};

HE_GUI_END_NAMESPACE

#endif // HTESTWIDGET_H
