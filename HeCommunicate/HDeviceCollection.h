#ifndef HDEVICECOLLECTION_H
#define HDEVICECOLLECTION_H

#include "HCommunicateGlobal.h"
#include "HeCore/HActionType.h"
#include <QMap>
#include <QScopedPointer>

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class IDevice;
class HDeviceCollectionPrivate;

class HE_COMMUNICATE_EXPORT HDeviceCollection : public QMap<QString, IDevice *>
{
public:
    bool isSupport(HActionType action);

protected:
    HDeviceCollection(HDeviceCollectionPrivate &p);

protected:
    QScopedPointer<HDeviceCollectionPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HDEVICECOLLECTION_H
