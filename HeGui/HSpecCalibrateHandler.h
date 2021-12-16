/***************************************************************************************************
**      2019-04-25  HSpecCalibrateHandler 光谱定标处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_BEGIN_NAMESPACE

class HSpecCalibrateHandlerPrivate;

class HSpecCalibrateHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecCalibrateHandler)

public:
    explicit HSpecCalibrateHandler(QObject *parent = nullptr);
    ~HSpecCalibrateHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE
