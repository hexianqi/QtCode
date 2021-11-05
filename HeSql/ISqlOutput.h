/***************************************************************************************************
**      2021-11-04  ISqlOutput 数据库记录输出接口。
***************************************************************************************************/

#pragma once

#include "HSqlGlobal.h"
#include "HeCore/IInitializeable.h"
#include "HeData/HDataGlobal.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE
class IPrintTemplate;
class ITextExportTemplate;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class ISqlTableModel;

class ISqlOutput : public IInitializeable
{
public:
    // 设置模型
    virtual void setModel(ISqlTableModel *) = 0;
    // 设置文本模版
    virtual void setTextTemplate(ITextExportTemplate *) = 0;
    // 设置打印模版
    virtual void setPrintTemplate(IPrintTemplate *) = 0;

public:
    // 导出Excel
    virtual void outputExcel() = 0;
    virtual void outputExcel(int index, int count = -1) = 0;
    // 打印
    virtual void print() = 0;
    // 打印预览
    virtual void printPreview() = 0;
    // 打印Pdf
    virtual void printPdf() = 0;
};

HE_SQL_END_NAMESPACE
