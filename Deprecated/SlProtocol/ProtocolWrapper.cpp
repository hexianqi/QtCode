#include "ProtocolWrapper.h"
#include "ProtocolFacade.h"

CProtocolFacade *_theObj = new CProtocolFacade();

bool OpenProtocol()
{
    return _theObj->openProtocol();
}

bool CloseProtocol()
{
    return _theObj->closeProtocol();
}

bool SetIntegralTime(double value)
{
    return _theObj->setIntegralTime(value);
}

bool SetSmooth(int times, int range)
{
    return _theObj->setSmooth(times, range);
}

bool GetSpectrumSample(int value[], int *size, double *percent, bool fit)
{
    vector<int> v;
    if (!_theObj->getSpectrumSample(v, *percent, fit))
        return false;
    if (*size > v.size())
        *size = v.size();
    for (int i = 0; i < *size; i++)
        value[i] = v[i];
    return true;
}

bool GetSpectrumEnergy(double value[], int *size, double *percent)
{
    vector<double> v;
    if (!_theObj->getSpectrumEnergy(v, *percent))
        return false;
    if (*size > v.size())
        *size = v.size();
    for (int i = 0; i < *size; i++)
        value[i] = v[i];
    return true;
}

double PelsToWave(int value)
{
    return _theObj->pelsToWave(value);
}

double HandleNonlinear(int value)
{
    return _theObj->handleNonlinear(value);
}

bool SetStdCurve(double value[], int size)
{
    vector<double> v(size);
    for (int i = 0; i < size; i++)
        v[i] = value[i];
    return _theObj->setStdCurve(v);
}
