#pragma once

#include "HLogRedirectService.h"
#include "HAbstractService_p.h"

HE_BEGIN_NAMESPACE

class HLogRedirectServicePrivate : public HAbstractServicePrivate
{
public:
    bool useTime = true;
    bool useContext = false;
    HLogRedirectService::MsgType msgType = HLogRedirectService::MsgType_All;
};

HE_END_NAMESPACE
