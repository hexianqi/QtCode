/***************************************************************************************************
**      2019-03-01  HTestHandler 测试处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HTestHandlerPrivate;

class HTestHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestHandler)

public:
    explicit HTestHandler(QObject *parent = nullptr);
    ~HTestHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE
