/***************************************************************************************************
**      2019-04-29  HAdjustEditHandler 调整编辑处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HAdjustEditHandlerPrivate;

class HAdjustEditHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAdjustEditHandler)

public:
    explicit HAdjustEditHandler(QObject *parent = nullptr);
    ~HAdjustEditHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE
