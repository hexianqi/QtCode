/***************************************************************************************************
**      2019-07-10  HSlSimulation
***************************************************************************************************/

#ifndef HSLSIMULATION_H
#define HSLSIMULATION_H

#include "HAbstractDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSlSimulationPrivate;

class HSlSimulation : public HAbstractDevice
{
    Q_DECLARE_PRIVATE(HSlSimulation)

public:
    explicit HSlSimulation();
    ~HSlSimulation() override;

public:
    QString typeName() override;

public:
    HErrorType open() override;
    HErrorType close() override;
    HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HSlSimulation(HSlSimulationPrivate &);

protected:
    double simulate(double v);
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HSLSIMULATION_H
