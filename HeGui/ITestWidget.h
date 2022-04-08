/***************************************************************************************************
**      2019-03-21  ITestWidget 测试窗体接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"
#include <QtWidgets/QWidget>

class QMenu;
class QToolBar;

HE_BEGIN_NAMESPACE

class ITestWidget : public QWidget, public IInitializeable
{
    Q_OBJECT

public:
    using QWidget::QWidget;

public:
    // 菜单
    virtual QList<QMenu *> menus() = 0;
    // 工具栏
    virtual QList<QToolBar *> toolBars() = 0;

public:
    // 启动
    virtual bool start() = 0;
    // 停止
    virtual bool stop() = 0;
};

HE_END_NAMESPACE
