/***************************************************************************************************
**      2019-06-12  ICustomStyle 定制样式接口。
***************************************************************************************************/

#pragma once

#include "IStyle.h"

HE_CONTROL_BEGIN_NAMESPACE

class ICustomStyle : public IStyle
{
public:
    // 按钮样式
    virtual QString pushButton(QVariantMap param = QVariantMap()) = 0;
    // 文本框样式
    virtual QString lineEdit(QVariantMap param = QVariantMap()) = 0;
    // 进度条样式
    virtual QString progressBar(QVariantMap param = QVariantMap()) = 0;
    // 滑块条样式
    virtual QString slider(QVariantMap param = QVariantMap()) = 0;
    // 单选框样式
    virtual QString radioButton(QVariantMap param = QVariantMap()) = 0;
    // 复选框样式
    virtual QString checkBox(QVariantMap param = QVariantMap()) = 0;
    // 滚动条样式
    virtual QString scrollBar(QVariantMap param = QVariantMap()) = 0;
};

HE_CONTROL_END_NAMESPACE
