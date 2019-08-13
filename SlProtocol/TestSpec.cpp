#include "TestSpec.h"
#include "CalibrateSpec.h"

CTestSpec::CTestSpec(CCalibrateSpec *p)
{
    _calibrate = p;
    _avg = false;
    _fit = true;
}

CTestSpec::~CTestSpec()
{
}

int CTestSpec::commWaitTime()
{
    return _commWaitTime;
}

double CTestSpec::setIntegralTime(double value)
{
    if (value < 1)
        value = 1;
    if (value > 500)
        value = 500;
    _commWaitTime = (int)value;
    _sampleCache.clear();
    return value;
}

int CTestSpec::calcMaxSample(vector<int> value)
{
    int r = 0;
    for (size_t i = 0; i < value.size(); i++)
    {
        if (value[i] > r)
            r = value[i];
    }
    return r;
}

vector<int> CTestSpec::preprocess(vector<int> value)
{
    if (value.size() < 1)
        return value;

    if (_avg)
        value = average(value);
    value = _calibrate->dealBotton(value);
    if (_fit)
        value = _calibrate->fit(value);
    return _calibrate->smooth(value);
}

vector<double> CTestSpec::calcEnergy(vector<int> value)
{
    return _calibrate->calcEnergy(value);
}

vector<int> CTestSpec::average(vector<int> value)
{
    size_t i, j;
    if (_calibrate->checkFrameOverflow(_sampleCache.size()))
        _sampleCache.pop_front();
    _sampleCache.push_back(value);

    for (i = 0; i < value.size(); i++)
    {
        int r = 0;
        for (j = 0; j < _sampleCache.size(); j++)
            r += _sampleCache[j][i];
        value[i] = r / j;
    }
    return value;
}
