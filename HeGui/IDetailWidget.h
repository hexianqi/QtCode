/***************************************************************************************************
**      2019-03-26  IDetailWidget 详情窗体接口。
***************************************************************************************************/

#ifndef IDETAILWIDGET_H
#define IDETAILWIDGET_H

#include "HGuiGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QtWidgets/QWidget>

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class IDetailWidget : public QWidget, public IInitializeable
{
    Q_OBJECT

public:
    using QWidget::QWidget;

public:
    // 刷新窗体
    virtual void refreshWidget() = 0;
};

HE_GUI_END_NAMESPACE

#endif // IDETAILWIDGET_H
