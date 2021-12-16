/***************************************************************************************************
**      2018-06-19  IProtocolCollection 协议集合接口。
***************************************************************************************************/

#pragma once

#include "HeCore/HCollection.h"

HE_BEGIN_NAMESPACE

class IProtocol;

class IProtocolCollection : public HCollection<IProtocol>
{
public:
    using HCollection::HCollection;
};

HE_END_NAMESPACE
