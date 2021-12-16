/***************************************************************************************************
**      2021-01-25  HExportDeviceHandler
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_BEGIN_NAMESPACE

class HExportDeviceHandlerPrivate;

class HExportDeviceHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HExportDeviceHandler)

public:
    explicit HExportDeviceHandler(QObject *parent = nullptr);
    ~HExportDeviceHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;

};

HE_END_NAMESPACE

