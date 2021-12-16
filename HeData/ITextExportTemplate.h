/***************************************************************************************************
**      2021-11-02  ITextExportTemplate 文本导出模版接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class ITextExportTemplate : public IInitializeable
{
public:
    // 数据项
    virtual QStringList dataType() = 0;
    // 设置数据项
    virtual void setDataType(QStringList) = 0;
    // 设置数据
    virtual void setData(QVariant) = 0;

public:
    // 内容
    virtual QString content(bool title = true) = 0;
};

HE_END_NAMESPACE
