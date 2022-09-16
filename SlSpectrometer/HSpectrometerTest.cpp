#include "HSpectrometerTest.h"
#include "HSpectrometerCalibrate.h"

HSpectrometerTest::HSpectrometerTest(HSpectrometerCalibrate *p)
{
    _calibrate = p;
    _avg = false;
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
    unsigned int i;
    double r = 0;
    for (i = 0; i < value.size(); i++)
    {
        if (value[i] > r)
            r = value[i];
    }
    return r;
}

vector<double> HSpectrometerTest::preprocess(vector<double> value, bool fix)
{
    if (value.size() < 1)
        return value;

    if (_avg)
        value = average(value);
    value = _calibrate->dealBotton(value);
    value =  _calibrate->smooth(value);
    if (fix)
        value = fit(value);
    return value;
}

vector<double> HSpectrometerTest::average(vector<double> value)
{
    unsigned int i, j;
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

vector<double> HSpectrometerTest::fit(vector<double> value)
{
    for (unsigned int i = 0; i < value.size(); i++)
        value[i] = max(0.0, _calibrate->fit(value[i]));
    return value;
}
