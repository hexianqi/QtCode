/***************************************************************************************************
**      2022-01-28  HLocationSelectHandler
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_BEGIN_NAMESPACE

class HLocationSelectHandlerPrivate;

class HLocationSelectHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HLocationSelectHandler)

public:
    explicit HLocationSelectHandler(QObject *parent = nullptr);
    ~HLocationSelectHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE

