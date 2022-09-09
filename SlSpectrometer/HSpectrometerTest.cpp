#include "HSpectrometerTest.h"
#include "HSpectrometerCalibrate.h"

HSpectrometerTest::HSpectrometerTest(HSpectrometerCalibrate *p)
{
    _calibrate = p;
    _avg = false;
    _fit = true;
}

HSpectrometerTest::~HSpectrometerTest()
{
}

int HSpectrometerTest::commWaitTime()
{
    return _commWaitTime;
}

double HSpectrometerTest::setIntegralTime(double value)
{
    if (value < 1)
        value = 1;
    if (value > 500)
        value = 500;
    _commWaitTime = (int)value;
    _sampleCache.clear();
    return value;
}

double HSpectrometerTest::calcMaxSample(vector<double> value)
{
    double r = 0;
    for (size_t i = 0; i < value.size(); i++)
    {
        if (value[i] > r)
            r = value[i];
    }
    return r;
}

vector<double> HSpectrometerTest::preprocess(vector<double> value)
{
    if (value.size() < 1)
        return value;

    if (_avg)
        value = average(value);
    value = _calibrate->dealBotton(value);
    return _calibrate->smooth(value);
}

vector< vector<double> > HSpectrometerTest::calcEnergy(vector<double> value)
{
    return _calibrate->calcWaveEnergy(value);
}

vector<double> HSpectrometerTest::average(vector<double> value)
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
