/***************************************************************************************************
**      2019-12-16  HCcd1305Protocol
***************************************************************************************************/

#pragma once

#include "HAbstractProtocol.h"

HE_BEGIN_NAMESPACE

class HCcd1305ProtocolPrivate;

class HCcd1305Protocol : public HAbstractProtocol
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCcd1305Protocol)

public:
    explicit HCcd1305Protocol(QObject *parent = nullptr);
    ~HCcd1305Protocol() override;

public:
    QString typeName() override;

protected:
    HCcd1305Protocol(HCcd1305ProtocolPrivate &, QObject *parent = nullptr);

protected:
    virtual void init();
};

HE_END_NAMESPACE
