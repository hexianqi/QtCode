/***************************************************************************************************
**      2018-06-19  IProtocolCollection 协议集合接口。
***************************************************************************************************/

#pragma once

#include "HCommunicateGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class IProtocol;

class IProtocolCollection : public HCollection<IProtocol>
{
public:
    using HCollection::HCollection;
};

HE_COMMUNICATE_END_NAMESPACE
