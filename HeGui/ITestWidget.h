/***************************************************************************************************
**      2019-03-21  ITestWidget 测试窗体接口。
***************************************************************************************************/

#ifndef ITESTWIDGET_H
#define ITESTWIDGET_H

#include "HGuiGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QtWidgets/QWidget>

class QMenu;
class QToolBar;

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

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
    virtual void start() = 0;
    // 停止
    virtual void stop() = 0;
};

HE_GUI_END_NAMESPACE

#endif // ITESTWIDGET_H
