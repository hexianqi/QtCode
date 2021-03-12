#pragma once

#include "HCcd1305Protocol.h"
#include "HBigProtocol_p.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HCcd1305ProtocolPrivate : public HBigProtocolPrivate
{
public:
    HCcd1305ProtocolPrivate();
};

HE_COMMUNICATE_END_NAMESPACE
