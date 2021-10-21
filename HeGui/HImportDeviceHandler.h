/***************************************************************************************************
**      2021-01-25  HImportDeviceHandler
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HImportDeviceHandlerPrivate;

class HImportDeviceHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HImportDeviceHandler)

public:
    explicit HImportDeviceHandler(QObject *parent = nullptr);
    ~HImportDeviceHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

