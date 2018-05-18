#ifndef HDEVICECOLLECTION_H
#define HDEVICECOLLECTION_H

#include "IDeviceCollection.h"
#include "HeCore/HCollection.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HDeviceCollectionPrivate;

class HDeviceCollection : public HCollection<IDevice>, public IDeviceCollection
{
public:
    explicit HDeviceCollection();
    ~HDeviceCollection();

public:
    virtual void initialize(QVariantMap param) override;
    virtual void addSupport(HActionType action) override;
    virtual bool isSupport(HActionType action) override;

protected:
    HDeviceCollection(HDeviceCollectionPrivate &p);

protected:
    QScopedPointer<HDeviceCollectionPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HDEVICECOLLECTION_H
