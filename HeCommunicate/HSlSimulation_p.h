#ifndef HSLSIMULATION_P_H
#define HSLSIMULATION_P_H

#include "HSlSimulation.h"
#include "HAbstractDevice_p.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSlSimulationPrivate : public HAbstractDevicePrivate
{
public:
    double intergalTime = 1;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HSLSIMULATION_P_H
