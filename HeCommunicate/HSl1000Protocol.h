/***************************************************************************************************
**      2019-12-16  HSl1000Protocol
***************************************************************************************************/

#pragma once

#include "HAbstractProtocol.h"

HE_BEGIN_NAMESPACE

class HSl1000ProtocolPrivate;

class HSl1000Protocol : public HAbstractProtocol
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSl1000Protocol)

public:
    explicit HSl1000Protocol(QObject *parent = nullptr);
    ~HSl1000Protocol() override;

public:
    QString typeName() override;

protected:
    HSl1000Protocol(HSl1000ProtocolPrivate &, QObject *parent = nullptr);

protected:
    virtual void init();
};

HE_END_NAMESPACE
