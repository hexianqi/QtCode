/***************************************************************************************************
**      2021-01-25  HExportCurveHandler
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HExportCurveHandlerPrivate;

class HExportCurveHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HExportCurveHandler)

public:
    explicit HExportCurveHandler(QObject *parent = nullptr);
    ~HExportCurveHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

