#ifndef HABSTRACTPROTOCOL_P_H
#define HABSTRACTPROTOCOL_P_H

#include "HAbstractProtocol.h"

class QMutex;

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractProtocolPrivate
{
public:
    HAbstractProtocolPrivate();

public:
    IDevice *device = nullptr;
    QMutex *mutex = nullptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTPROTOCOL_P_H
