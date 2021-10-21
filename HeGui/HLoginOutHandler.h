/***************************************************************************************************
**      2021-07-21  HLoginOutHandler
***************************************************************************************************/

#pragma once

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HLoginOutHandlerPrivate;

class HLoginOutHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HLoginOutHandler)

public:
    explicit HLoginOutHandler(QObject *parent = nullptr);
    ~HLoginOutHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

