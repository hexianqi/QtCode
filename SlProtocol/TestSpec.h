#pragma once

#include <vector>
#include <deque>

using namespace std;

class CCalibrateSpec;

class CTestSpec
{
public:
    CTestSpec(CCalibrateSpec *);
    ~CTestSpec();

public:
    int commWaitTime();

public:
    double setIntegralTime(double value);
    int calcMaxSample(vector<int> value);
    vector<int> preprocess(vector<int> value);
    vector<double> calcEnergy(vector<int> value);

protected:
    vector<int> average(vector<int> value);

protected:
    CCalibrateSpec *_calibrate;
    bool _avg;
    bool _fit;
    int _commWaitTime;
    deque<vector<int> > _sampleCache;
};
