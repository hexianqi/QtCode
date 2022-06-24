/***************************************************************************************************
**      2022-06-21  IPrintSettingDialog 打印配置对话框接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"
#include <QtWidgets/QDialog>

HE_BEGIN_NAMESPACE

class IPrintTemplate;

class IPrintSettingDialog : public QDialog, public IInitializeable
{
    Q_OBJECT

public:
    using QDialog::QDialog;

public:
    // 设置模板
    virtual void setPrintTemplate(IPrintTemplate *) = 0;
};

HE_END_NAMESPACE
