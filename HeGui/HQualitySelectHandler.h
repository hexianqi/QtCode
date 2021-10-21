/***************************************************************************************************
**      2019-05-07  HQualitySelectHandler 品质数据选择处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HQualitySelectHandlerPrivate;

class HQualitySelectHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HQualitySelectHandler)

public:
    explicit HQualitySelectHandler(QObject *parent = nullptr);
    ~HQualitySelectHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE
