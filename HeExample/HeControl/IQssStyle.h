/***************************************************************************************************
**      2019-07-19  IQssStyle Qss样式接口。
***************************************************************************************************/

#pragma once

#include "IStyle.h"

HE_CONTROL_BEGIN_NAMESPACE

class IQssStyle : public IStyle
{
    Q_OBJECT

public:
    using IStyle::IStyle;

public:
    // 调色板
    virtual QPalette toPalette() = 0;
    // 所有样式
    virtual QStringList styles() = 0;
    // 选择样式
    virtual bool selectStyle(QString vlaue) = 0;
    // 添加样式
    virtual void addStyle(QString key, QString fileName) = 0;
};

HE_CONTROL_END_NAMESPACE
