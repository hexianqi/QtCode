/***************************************************************************************************
**      2022-02-08  HKeyenceProtocol
***************************************************************************************************/

#pragma once

#include "HeCommunicate/HAbstractProtocol.h"

HE_USE_NAMESPACE

class HKeyenceProtocolPrivate;

class HKeyenceProtocol : public HAbstractProtocol
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HKeyenceProtocol)

public:
    explicit HKeyenceProtocol(QObject *parent = nullptr);
    ~HKeyenceProtocol() override;

public:
    QString typeName() override;

protected:
    virtual void init();
};



