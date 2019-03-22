/***************************************************************************************************
**      2018-06-19  HDeviceCollection 设备集合类。
***************************************************************************************************/

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
    virtual ~HDeviceCollection();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void addSupport(HActionType action) override;
    bool isSupport(HActionType action) override;

protected:
    HDeviceCollection(HDeviceCollectionPrivate &);

protected:
    QScopedPointer<HDeviceCollectionPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HDEVICECOLLECTION_H
