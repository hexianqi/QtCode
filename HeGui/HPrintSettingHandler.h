/***************************************************************************************************
**      2022-06-21  HPrintSettingHandler
***************************************************************************************************/

#pragma once

#include "HAbstractGuiHandler.h"

HE_BEGIN_NAMESPACE

class HPrintSettingHandlerPrivate;

class HPrintSettingHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPrintSettingHandler)

public:
    explicit HPrintSettingHandler(QObject *parent = nullptr);
    ~HPrintSettingHandler() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE

