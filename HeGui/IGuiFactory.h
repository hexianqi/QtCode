/***************************************************************************************************
**      2018-06-19  IGuiFactory Gui工厂接口。
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class ITestSetWidget;
class ITestDataEditDialog;
class IGuiHandler;
class HAction;

class IGuiFactory : public IInitializeable
{
public:
    // 创建测试设置窗体
    virtual ITestSetWidget *createTestSetWidget(QString type, QWidget *parent = nullptr, QVariantMap param = QVariantMap()) = 0;
    // 创建测试数据编辑对话框
    virtual ITestDataEditDialog *createTestDataEditDialog(QString type, QWidget *parent = nullptr, QVariantMap param = QVariantMap()) = 0;
    // 创建处理者
    virtual IGuiHandler *createHandler(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建动作
    virtual HAction *createAction(QString text, QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_GUI_END_NAMESPACE
