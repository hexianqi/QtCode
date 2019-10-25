#ifndef HSPECTHREAD_P_H
#define HSPECTHREAD_P_H

#include "HSpecThread.h"
#include "HAbstractThread_p.h"
#include "HeData/HDataGlobal.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecThreadPrivate : public HAbstractThreadPrivate
{
public:
    HSpecThreadPrivate();
};

HE_CONTROLLER_END_NAMESPACE

#endif // HSPECTHREAD_P_H
