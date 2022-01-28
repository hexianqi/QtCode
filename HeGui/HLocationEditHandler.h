/***************************************************************************************************
**      2022-01-28  HLocationEditHandler
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_BEGIN_NAMESPACE

class HLocationEditHandlerPrivate;

class HLocationEditHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HLocationEditHandler)

public:
    explicit HLocationEditHandler(QObject *parent = nullptr);
    ~HLocationEditHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE

