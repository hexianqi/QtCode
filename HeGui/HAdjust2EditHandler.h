/***************************************************************************************************
**      2019-04-29  HAdjustEditHandler 调整编辑处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_BEGIN_NAMESPACE

class HAdjust2EditHandlerPrivate;

class HAdjust2EditHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAdjust2EditHandler)

public:
    explicit HAdjust2EditHandler(QObject *parent = nullptr);
    ~HAdjust2EditHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE
