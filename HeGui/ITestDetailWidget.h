/***************************************************************************************************
**      2019-03-26  ITestDetailWidget 测试详情窗体接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class ITestDetailWidget : public QWidget, public IInitializeable
{
    Q_OBJECT

public:
    using QWidget::QWidget;

public:
    // 刷新窗体
    virtual void refreshWidget() = 0;
    // 刷新某项
    virtual void refreshData(QString) = 0;
    virtual void refreshData(QStringList) = 0;
};

HE_END_NAMESPACE
