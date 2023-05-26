/***************************************************************************************************
**      2019-05-27  HUi2008Protocol UI2008协议。
***************************************************************************************************/

#pragma once

#include "HAbstractProtocol.h"

HE_BEGIN_NAMESPACE

class HUi2008ProtocolPrivate;

class HUi2008Protocol : public HAbstractProtocol
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HUi2008Protocol)

public:
    explicit HUi2008Protocol(QObject *parent = nullptr);
    ~HUi2008Protocol() override;

public:
    QString typeName() override;

public:
    bool getData(HActionType action, QVariantList &value, QVariant::Type type = QVariant::Int, int delay = 0) override;

protected:
    virtual void init();
};

HE_END_NAMESPACE
