/***************************************************************************************************
**      2021-10-18  IPrintTemplate 打印模版接口。
***************************************************************************************************/

#pragma once

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

class QPrinter;

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IPrintTemplate : public QObject, public IInitializeable
{
    Q_OBJECT

public:
    using QObject::QObject;

public:
    // 数据项
    virtual QStringList dataType() = 0;
    // 设置数据
    virtual void setData(QVariantMap) = 0;

public:
    // 打印页面
    virtual bool printPages(QPrinter *) = 0;
};

HE_DATA_END_NAMESPACE
