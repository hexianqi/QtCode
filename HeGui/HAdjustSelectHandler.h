/***************************************************************************************************
**      2019-04-29  HAdjustSelectHandler 调整数据选择处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HAdjustSelectHandlerPrivate;

class HAdjustSelectHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAdjustSelectHandler)

public:
    explicit HAdjustSelectHandler(QObject *parent = nullptr);
    ~HAdjustSelectHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE
