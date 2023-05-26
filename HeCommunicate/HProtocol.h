/***************************************************************************************************
**      2023-05-26  HProtocol
***************************************************************************************************/

#pragma once

#include "HAbstractProtocol.h"

HE_BEGIN_NAMESPACE

class HProtocolPrivate;

class HProtocol : public HAbstractProtocol
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HProtocol)

public:
    explicit HProtocol(QObject *parent = nullptr);
    ~HProtocol() override;

public:
    QString typeName() override;

protected:
    HProtocol(HProtocolPrivate &p, QObject *parent = nullptr);
};

HE_END_NAMESPACE

