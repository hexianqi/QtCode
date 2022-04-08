/***************************************************************************************************
**      2022-04-06  HAngleTestHandler
***************************************************************************************************/

#pragma once

#include "HAbstractGuiHandler.h"

HE_BEGIN_NAMESPACE

class HAngleTestHandlerPrivate;

class HAngleTestHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAngleTestHandler)

public:
    explicit HAngleTestHandler(QObject *parent = nullptr);
    ~HAngleTestHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE
