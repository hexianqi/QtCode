/***************************************************************************************************
**      2019-03-26  ITestDetailWidget 测试详情窗体接口。
***************************************************************************************************/

#ifndef ITESTDETAILWIDGET_H
#define ITESTDETAILWIDGET_H

#include "HGuiGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QtWidgets/QWidget>

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class ITestDetailWidget : public QWidget, public IInitializeable
{
    Q_OBJECT

public:
    using QWidget::QWidget;

public:
    // 刷新窗体
    virtual void refreshWidget() = 0;
};

HE_GUI_END_NAMESPACE

#endif // ITESTDETAILWIDGET_H
