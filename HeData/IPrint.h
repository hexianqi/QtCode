/***************************************************************************************************
**      2021-10-18  IPrint 打印接口。
***************************************************************************************************/

#pragma once

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IPrintTemplate;

class IPrint : public IInitializeable
{
public:
    // 打印模版
    virtual IPrintTemplate *printTemplate() = 0;
    // 设置打印模版
    virtual void setPrintTemplate(IPrintTemplate *) = 0;

public:
    // 打印
    virtual bool print() = 0;
    // 打印预览
    virtual bool printPreview() = 0;
    // 打印Pdf
    virtual bool printPdf() = 0;
};

HE_DATA_END_NAMESPACE
