/***************************************************************************************************
**      2020-04-08  HSpecTcHandler 色温配置处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HSpecTcHandlerPrivate;

class HSpecTcHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecTcHandler)

public:
    explicit HSpecTcHandler(QObject *parent = nullptr);
    ~HSpecTcHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE
