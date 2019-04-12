#ifndef HDEVICESLCODEC_P_H
#define HDEVICESLCODEC_P_H

#include "HDeviceSL_p.h"
#include "HDeviceSLCodec.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class ICodec;

class HDeviceSLCodecPrivate : public HDeviceSLPrivate
{
public:
    HDeviceSLCodecPrivate();

public:
    ICodec *codec;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HDEVICESLCODEC_P_H
