/***************************************************************************************************
**      2019-11-29  HIVTestHandler
***************************************************************************************************/

#pragma once

#include "HAbstractGuiHandler.h"

HE_BEGIN_NAMESPACE

class HIVTestHandlerPrivate;

class HIVTestHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HIVTestHandler)

public:
    explicit HIVTestHandler(QObject *parent = nullptr);
    ~HIVTestHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE
