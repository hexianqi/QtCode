#pragma once

#include "HSpectrometerGlobal.h"
#include "HSpectrometerData.h"

using namespace std;

class HSpectrometerAlgorithm;
class HSpectrometerCalibrate;
class HSpectrometerProtocol;
class HSpectrometerTest;

class SLSPECTROMETER_EXPORT HSpectrometer
{
public:
    HSpectrometer();
    ~HSpectrometer();

public:
    bool setSmooth(int times, int range);
    void setStdCurve(vector<double> value);
    double pelsToWave(int value);

public:
    bool openProtocol();
    bool closeProtocol();
    bool setIntegralTime(double value);
    bool getSample(vector<double> &value, double &percent, bool fit = true);
    bool getSampleI(double integrationTime, vector<double> &value, double &percent, bool fit = true);
    bool getSN(vector<unsigned char> &value);
    HSpectrometerData *getSpectrometerData(vector<double> value);

public:
    bool clearState();
    bool queryState(int *value);
    bool startSample(double integrationTime);
    bool getSampleT(vector<double> &value, double &percent, bool fit = true);

protected:
    vector<double> processSample(vector<int> &data, double &percent, bool fit);

protected:
    HSpectrometerAlgorithm *_algorithm;
    HSpectrometerCalibrate *_calibrate;
    HSpectrometerProtocol *_protocol;
    HSpectrometerTest *_test;
};
