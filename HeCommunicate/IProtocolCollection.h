#ifndef IPROTOCOLCOLLECTION_H
#define IPROTOCOLCOLLECTION_H

#include "HCommunicateGlobal.h"
#include "HeCore/ICollection.h"

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class IProtocol;

class HE_COMMUNICATE_EXPORT IProtocolCollection : virtual public ICollection<IProtocol>
{
};

HE_COMMUNICATE_END_NAMESPACE

#endif // IPROTOCOLCOLLECTION_H
