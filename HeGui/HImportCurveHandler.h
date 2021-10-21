/***************************************************************************************************
**      2021-01-25  HImportCurveHandler
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HImportCurveHandlerPrivate;

class HImportCurveHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HImportCurveHandler)

public:
    explicit HImportCurveHandler(QObject *parent = nullptr);
    ~HImportCurveHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

