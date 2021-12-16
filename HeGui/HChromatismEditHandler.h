/***************************************************************************************************
**      2019-05-20  HChromatismEditHandler 色容差编辑处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_BEGIN_NAMESPACE

class HChromatismEditHandlerPrivate;

class HChromatismEditHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HChromatismEditHandler)

public:
    explicit HChromatismEditHandler(QObject *parent = nullptr);
    ~HChromatismEditHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE
