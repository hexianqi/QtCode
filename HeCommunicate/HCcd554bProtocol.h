/***************************************************************************************************
**      2019-12-16  HCcd554bProtocol
***************************************************************************************************/

#ifndef HCCD554BPROTOCOL_H
#define HCCD554BPROTOCOL_H

#include "HLittleProtocol.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HCcd554bProtocolPrivate;

class HCcd554bProtocol : public HLittleProtocol
{
    Q_DECLARE_PRIVATE(HCcd554bProtocol)

public:
    explicit HCcd554bProtocol();
    ~HCcd554bProtocol() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    HCcd554bProtocol(HCcd554bProtocolPrivate &);
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HCCD554BPROTOCOL_H
