/***************************************************************************************************
**      2019-07-19  IQssStyle Qss样式接口。
***************************************************************************************************/

#pragma once

#include "IStyle.h"

HE_BEGIN_NAMESPACE

class IQssStyle : public IStyle
{
public:
    // 调色板
    virtual QPalette toPalette() = 0;
    // 某项颜色
    virtual QColor color(const QString &flag) = 0;
    // 所有样式
    virtual QStringList styles() = 0;
    // 选择样式
    virtual bool selectStyle(const QString &vlaue) = 0;
    // 添加样式
    virtual void addStyle(const QString &key, const QString &fileName) = 0;
};

HE_END_NAMESPACE
