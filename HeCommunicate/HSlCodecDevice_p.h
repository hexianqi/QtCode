#ifndef HSLCODECDEVICE_P_H
#define HSLCODECDEVICE_P_H

#include "HSlDevice_p.h"
#include "HSlCodecDevice.h"
#include <QtCore/QSharedPointer>

HE_COMMUNICATE_BEGIN_NAMESPACE

class ICodec;

class HSlCodecDevicePrivate : public HSlDevicePrivate
{
public:
    HSlCodecDevicePrivate();

public:
    QSharedPointer<ICodec> codec;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HSLCODECDEVICE_P_H
