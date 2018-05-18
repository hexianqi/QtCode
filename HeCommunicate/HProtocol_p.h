#ifndef HPROTOCOL_P_H
#define HPROTOCOL_P_H

#include "HProtocol.h"

class QMutex;

HE_COMMUNICATE_BEGIN_NAMESPACE

class HProtocolPrivate
{
public:
    HProtocolPrivate();

public:
    IDevice *device = nullptr;
    QMutex *mutex = nullptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HPROTOCOL_P_H
