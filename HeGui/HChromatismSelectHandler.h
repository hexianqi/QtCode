/***************************************************************************************************
**      2019-05-20  HChromatismSelectHandler 色容差数据选择处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_BEGIN_NAMESPACE

class HChromatismSelectHandlerPrivate;

class HChromatismSelectHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HChromatismSelectHandler)

public:
    explicit HChromatismSelectHandler(QObject *parent = nullptr);
    ~HChromatismSelectHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE
