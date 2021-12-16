/***************************************************************************************************
**      2019-05-15  HProductEditHandler 产品信息配置处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractGuiHandler.h"

HE_BEGIN_NAMESPACE

class HProductEditHandlerPrivate;

class HProductEditHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HProductEditHandler)

public:
    explicit HProductEditHandler(QObject *parent = nullptr);
    ~HProductEditHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE
