/***************************************************************************************************
**      2019-12-16  HCcd554bProtocol
***************************************************************************************************/

#pragma once

#include "HLittleProtocol.h"

HE_BEGIN_NAMESPACE

class HCcd554bProtocolPrivate;

class HCcd554bProtocol : public HLittleProtocol
{
    Q_DECLARE_PRIVATE(HCcd554bProtocol)

public:
    explicit HCcd554bProtocol();
    ~HCcd554bProtocol() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

protected:
    HCcd554bProtocol(HCcd554bProtocolPrivate &);
};

HE_END_NAMESPACE
