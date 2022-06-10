/***************************************************************************************************
**      2022-06-08  HTrendTestHandler
***************************************************************************************************/

#pragma once

#include "HAbstractGuiHandler.h"

HE_BEGIN_NAMESPACE

class HTrendTestHandlerPrivate;

class HTrendTestHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTrendTestHandler)

public:
    explicit HTrendTestHandler(QObject *parent = nullptr);
    ~HTrendTestHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE

