/***************************************************************************************************
**      2023-03-11  HCcd1305Protocol_COM
***************************************************************************************************/

#pragma once

#include "HAbstractProtocol.h"

HE_BEGIN_NAMESPACE

class HCcd1305Protocol_COMPrivate;

class HCcd1305Protocol_COM : public HAbstractProtocol
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCcd1305Protocol_COM)

public:
    explicit HCcd1305Protocol_COM(QObject *parent = nullptr);
    ~HCcd1305Protocol_COM() override;

public:
    QString typeName() override;

protected:
    HCcd1305Protocol_COM(HCcd1305Protocol_COMPrivate &, QObject *parent = nullptr);

protected:
    virtual void init();
};

HE_END_NAMESPACE

