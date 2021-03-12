/***************************************************************************************************
**      2019-12-16  HCcd1305Protocol
***************************************************************************************************/

#pragma once

#include "HBigProtocol.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HCcd1305ProtocolPrivate;

class HCcd1305Protocol : public HBigProtocol
{
    Q_DECLARE_PRIVATE(HCcd1305Protocol)

public:
    explicit HCcd1305Protocol();
    ~HCcd1305Protocol() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    HCcd1305Protocol(HCcd1305ProtocolPrivate &);
};

HE_COMMUNICATE_END_NAMESPACE
