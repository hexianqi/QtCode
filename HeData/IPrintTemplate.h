/***************************************************************************************************
**      2021-10-18  IPrintTemplate 打印模版接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

class QPrinter;

HE_BEGIN_NAMESPACE

class IPrintTemplate : public QObject, public IInitializeable
{
    Q_OBJECT

public:
    using QObject::QObject;

public:
    // 打印参数
    virtual QVariantMap param() = 0;
    virtual void setParam(QVariantMap) = 0;
    // 数据项
    virtual QStringList dataType() = 0;
    // 设置数据
    virtual void setData(QVariantMap) = 0;

public:
    // 打印页面
    virtual bool printPages(QPrinter *) = 0;
};

HE_END_NAMESPACE
