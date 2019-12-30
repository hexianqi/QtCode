/***************************************************************************************************
**      2019-12-16  HSl1000Protocol
***************************************************************************************************/

#ifndef HSL1000PROTOCOL_H
#define HSL1000PROTOCOL_H

#include "HLittleProtocol.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSl1000ProtocolPrivate;

class HSl1000Protocol : public HLittleProtocol
{
    Q_DECLARE_PRIVATE(HSl1000Protocol)

public:
    explicit HSl1000Protocol();
    ~HSl1000Protocol() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    HSl1000Protocol(HSl1000ProtocolPrivate &);
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HSL1000PROTOCOL_H
