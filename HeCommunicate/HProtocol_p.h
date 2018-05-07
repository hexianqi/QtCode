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
    IProtocolStrategy *strategy;
    QMutex *mutex;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HPROTOCOL_P_H
