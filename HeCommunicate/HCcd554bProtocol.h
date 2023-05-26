/***************************************************************************************************
**      2019-12-16  HCcd554bProtocol
***************************************************************************************************/

#pragma once

#include "HAbstractProtocol.h"

HE_BEGIN_NAMESPACE

class HCcd554bProtocolPrivate;

class HCcd554bProtocol : public HAbstractProtocol
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCcd554bProtocol)

public:
    explicit HCcd554bProtocol(QObject *parent = nullptr);
    ~HCcd554bProtocol() override;

public:
    QString typeName() override;

protected:
    HCcd554bProtocol(HCcd554bProtocolPrivate &, QObject *parent = nullptr);

protected:
    virtual void init();
};

HE_END_NAMESPACE
