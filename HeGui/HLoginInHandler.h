/***************************************************************************************************
**      2021-07-21  HLoginInHandler
***************************************************************************************************/

#pragma once

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HLoginInHandlerPrivate;

class HLoginInHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HLoginInHandler)

public:
    explicit HLoginInHandler(QObject *parent = nullptr);
    ~HLoginInHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

