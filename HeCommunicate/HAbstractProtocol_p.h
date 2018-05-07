#ifndef HABSTRACTPROTOCOL_P_H
#define HABSTRACTPROTOCOL_P_H

#include "HAbstractProtocol.h"

class QMutex;

HE_COMMUNICATE_BEGIN_NAMESPACE

class IPort;

class HAbstractProtocolPrivate
{
public:
    HAbstractProtocolPrivate();

public:
    IProtocolInfo *info;
    IPort *port;
    QMutex *mutex;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTPROTOCOL_P_H
