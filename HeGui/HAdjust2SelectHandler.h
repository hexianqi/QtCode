/***************************************************************************************************
**      2019-04-29  HAdjustSelectHandler 调整数据选择处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HAdjust2SelectHandlerPrivate;

class HAdjust2SelectHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAdjust2SelectHandler)

public:
    explicit HAdjust2SelectHandler(QObject *parent = nullptr);
    ~HAdjust2SelectHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE
