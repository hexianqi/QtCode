/***************************************************************************************************
**      2019-05-15  HProductInfoEditHandler 产品信息配置处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HProductInfoEditHandlerPrivate;

class HProductInfoEditHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HProductInfoEditHandler)

public:
    explicit HProductInfoEditHandler(QObject *parent = nullptr);
    ~HProductInfoEditHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE
