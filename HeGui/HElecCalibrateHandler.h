/***************************************************************************************************
**      2019-10-23  HElecCalibrateHandler 电定标处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HElecCalibrateHandlerPrivate;

class HElecCalibrateHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HElecCalibrateHandler)

public:
    explicit HElecCalibrateHandler(QObject *parent = nullptr);
    ~HElecCalibrateHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE
