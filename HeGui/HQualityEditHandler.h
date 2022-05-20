/***************************************************************************************************
**      2019-05-07  HQualityEditHandler 品质数据编辑处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_BEGIN_NAMESPACE

class HQualityEditHandlerPrivate;

class HQualityEditHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HQualityEditHandler)

public:
    explicit HQualityEditHandler(QObject *parent = nullptr);
    ~HQualityEditHandler() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE
