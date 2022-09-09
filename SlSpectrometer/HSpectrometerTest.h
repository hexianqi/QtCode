#pragma once

#include <vector>
#include <deque>

using namespace std;

class HSpectrometerCalibrate;

class HSpectrometerTest
{
public:
    HSpectrometerTest(HSpectrometerCalibrate *);
    ~HSpectrometerTest();

public:
    int commWaitTime();

public:
    double setIntegralTime(double value);
    double calcMaxSample(vector<double> value);
    vector<double> preprocess(vector<double> value);
    vector< vector<double> > calcEnergy(vector<double> value);

protected:
    vector<double> average(vector<double> value);

protected:
    HSpectrometerCalibrate *_calibrate;
    bool _avg;
    bool _fit;
    int _commWaitTime;
    deque<vector<double> > _sampleCache;
};
