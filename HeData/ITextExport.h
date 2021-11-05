/***************************************************************************************************
**      2021-11-01  ITextExport 文本导出接口。
***************************************************************************************************/

#pragma once

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class ITextExportTemplate;

class ITextExport : public IInitializeable
{
public:
    // 获取模版
    virtual ITextExportTemplate *textTemplate() = 0;
    // 设置模版
    virtual void setTextTemplate(ITextExportTemplate *) = 0;
    // 设置导出路径
    virtual void setExportPath(const QString &) = 0;

public:
    // 保存文件
    virtual bool save() = 0;
    // 追加
    virtual bool append() = 0;
    // 清除
    virtual void clear() = 0;
};

HE_DATA_END_NAMESPACE
