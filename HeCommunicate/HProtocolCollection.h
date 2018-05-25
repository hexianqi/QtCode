#ifndef HPROTOCOLCOLLECTION_H
#define HPROTOCOLCOLLECTION_H

#include "IProtocolCollection.h"
#include "HeCore/HCollection.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HProtocolCollectionPrivate;

class HProtocolCollection : public HCollection<IProtocol>, public IProtocolCollection
{
public:
    explicit HProtocolCollection();
    ~HProtocolCollection();

public:
    virtual QString typeName() override;

protected:
    HProtocolCollection(HProtocolCollectionPrivate &p);

protected:
    QScopedPointer<HProtocolCollectionPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HPROTOCOLCOLLECTION_H
