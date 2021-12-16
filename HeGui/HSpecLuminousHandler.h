/***************************************************************************************************
**      2020-03-26  HSpecLuminousHandler 光通量自吸收配置处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_BEGIN_NAMESPACE

class HSpecLuminousHandlerPrivate;

class HSpecLuminousHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecLuminousHandler)

public:
    explicit HSpecLuminousHandler(QObject *parent = nullptr);
    ~HSpecLuminousHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE
