/***************************************************************************************************
**      2021-01-18  HDaXinProtocol
***************************************************************************************************/

#pragma once

#include "HeCommunicate/HAbstractProtocol.h"

HE_USE_NAMESPACE

class HDaXinProtocolPrivate;

class HDaXinProtocol : public HAbstractProtocol
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HDaXinProtocol)

public:
    explicit HDaXinProtocol(QObject *parent = nullptr);
    ~HDaXinProtocol() override;

public:
    QString typeName() override;

protected:
    virtual void init();
};

