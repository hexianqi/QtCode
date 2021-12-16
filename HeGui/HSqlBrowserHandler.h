/***************************************************************************************************
**      2019-05-15  HSqlBrowserHandler 数据库浏览器处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractGuiHandler.h"

HE_BEGIN_NAMESPACE

class HSqlBrowserHandlerPrivate;

class HSqlBrowserHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSqlBrowserHandler)

public:
    explicit HSqlBrowserHandler(QObject *parent = nullptr);
    ~HSqlBrowserHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE
