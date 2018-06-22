/***************************************************************************************************
**      2018-06-19  IProtocolCollection 协议集合接口。
***************************************************************************************************/

#ifndef IPROTOCOLCOLLECTION_H
#define IPROTOCOLCOLLECTION_H

#include "HCommunicateGlobal.h"
#include "HeCore/ICollection.h"

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class IProtocol;

class IProtocolCollection : virtual public ICollection<IProtocol>
{
};

HE_COMMUNICATE_END_NAMESPACE

#endif // IPROTOCOLCOLLECTION_H
