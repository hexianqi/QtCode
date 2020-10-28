/***************************************************************************************************
**      2020-10-27  ITestDataEditDialog 测试数据编辑对话框接口。
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include "HeCore/IInitializeable.h"
#include "HeData/HDataGlobal.h"
#include <QtWidgets/QDialog>

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT ITestDataEditDialog : public QDialog, public IInitializeable
{
    Q_OBJECT

public:
    using QDialog::QDialog;

public:
    // 设置数据
    virtual void setData(ITestData *) = 0;
};

HE_GUI_END_NAMESPACE
