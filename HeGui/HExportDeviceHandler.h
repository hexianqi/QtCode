/***************************************************************************************************
**      2021-01-25  HExportDeviceHandler
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HExportDeviceHandlerPrivate;

class HExportDeviceHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HExportDeviceHandler)

public:
    explicit HExportDeviceHandler(QObject *parent = nullptr);
    ~HExportDeviceHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;

};

HE_GUI_END_NAMESPACE

