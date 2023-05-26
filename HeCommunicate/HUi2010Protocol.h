/***************************************************************************************************
**      2023-05-26  HUi2010Protocol
***************************************************************************************************/

#pragma once

#include "HAbstractProtocol.h"

HE_BEGIN_NAMESPACE

class HUi2010ProtocolPrivate;

class HUi2010Protocol : public HAbstractProtocol
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HUi2010Protocol)

public:
    explicit HUi2010Protocol(QObject *parent = nullptr);
    ~HUi2010Protocol() override;

public:
    QString typeName() override;

public:
    bool getData(HActionType action, QVariantList &value, QVariant::Type type = QVariant::Int, int delay = 0) override;

protected:
    virtual void init();
};

HE_END_NAMESPACE

