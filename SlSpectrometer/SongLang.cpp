#include "SongLang.h"
#include "HSpectrometer.h"

HSpectrometer *_theObj = new HSpectrometer();
vector<double> _samples;

bool openSpectrometers(int /*index*/)
{
    return _theObj->openProtocol();
}

bool closeSpectrometers(int /*index*/)
{
    return _theObj->closeProtocol();
}

bool setStdCurve(int /*index*/, double *value, int size)
{
    vector<double> v;
    for (int i = 0; i < size; i++)
        v.push_back(value[i]);
    _theObj->setStdCurve(v);
    return true;
}

bool setIntegrationTime(int /*index*/, double value)
{
    return _theObj->setIntegralTime(value);
}

bool getWave(int /*index*/, double *value, int size)
{
    if (size < 1)
        return false;
    for (int i = 0; i < 2048; i++)
        value[i] = _theObj->pelsToWave(i);
    return true;
}

double pelsToWave(int /*index*/, double value)
{
    return _theObj->pelsToWave(value);
}

bool getSample(int /*index*/, double *value, int size)
{
    double percent;
    vector<double> v;
    if (!_theObj->getSample(v, percent, true))
        return false;
    if (size > v.size())
        size = v.size();
    for (int i = 0; i < size; i++)
        value[i] = v[i];
    return true;
}

bool getSampleI(int /*index*/, double integrationTime, double *value, int size)
{
    double percent;
    vector<double> v;
    if (!_theObj->getSampleI(integrationTime, v, percent, true))
        return false;
    if (size > v.size())
        size = v.size();
    for (int i = 0; i < size; i++)
        value[i] = v[i];
    return true;
}

bool getSN(int /*index*/, unsigned char *value, int size)
{
    vector<unsigned char> v;
    if (!_theObj->getSN(v))
        return false;
    if (size > v.size())
        size = v.size();
    for (int i = 0; i < size; i++)
        value[i] = v[i];
    return true;
}

bool clearState(int /*index*/)
{
    return _theObj->clearState();
}

bool queryState(int /*index*/, int *value)
{
    return _theObj->queryState(value);
}

bool startSample(int /*index*/, double integrationTime)
{
    _samples.clear();
    return _theObj->startSample(integrationTime);
}

bool getSampleT(int /*index*/, double *value, int size)
{
    if (_samples.size() == 0)
    {
        double percent;
        if (!_theObj->getSampleT(_samples, percent, true))
            return false;
    }
    if (size > _samples.size())
        size = _samples.size();
    for (int i = 0; i < size; i++)
        value[i] = _samples[i];
    return true;
}


bool getSpectrometerData(int /*index*/, HSpectrometerData *data, double *sample, int size)
{
    vector<double> v;
    for (int i = 0; i < size; i++)
        v.push_back(sample[i]);
    data = _theObj->getSpectrometerData(v);
    return data != nullptr;
}
