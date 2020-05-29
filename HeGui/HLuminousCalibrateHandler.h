/***************************************************************************************************
**      2020-05-27  HLuminousCalibrateHandler 光定标处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HLuminousCalibrateHandlerPrivate;

class HLuminousCalibrateHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HLuminousCalibrateHandler)

public:
    explicit HLuminousCalibrateHandler(QObject *parent = nullptr);
    ~HLuminousCalibrateHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

