/***************************************************************************************************
**      2020-10-27  ITestDataEditDialog 测试数据编辑对话框接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"
#include <QtWidgets/QDialog>

HE_BEGIN_NAMESPACE

class ITestData;

class ITestDataEditDialog : public QDialog, public IInitializeable
{
    Q_OBJECT

public:
    using QDialog::QDialog;

public:
    // 设置数据
    virtual void setData(ITestData *) = 0;
};

HE_END_NAMESPACE
