/***************************************************************************************************
**      2019-03-28  ITestSetWidget 测试设置窗体接口。
***************************************************************************************************/

#ifndef ITESTSETWIDGET_H
#define ITESTSETWIDGET_H

#include "HGuiGlobal.h"
#include "HeCore/IInitializeable.h"
#include "HeCore/HActionType.h"
#include <QtWidgets/QWidget>

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT ITestSetWidget : public QWidget, public IInitializeable
{
    Q_OBJECT

public:
    using QWidget::QWidget;

signals:
    void testStateChanged(bool b);
    void testModeChanged(int value);

public:
    // 处理动作
    virtual void handleAction(HActionType action) = 0;
    // 设置测试状态
    virtual bool setTestState(bool b) = 0;
    // 获取测试状态
    virtual bool testState() = 0;
    // 设置测试模式
    virtual bool setTestMode(int value) = 0;
    // 获取测试模式
    virtual int testMode() = 0;
};

HE_GUI_END_NAMESPACE

#endif // ITESTSETWIDGET_H
