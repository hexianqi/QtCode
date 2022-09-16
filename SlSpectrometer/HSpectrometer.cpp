#include "HSpectrometer.h"
#include "HSpectrometerAlgorithm.h"
#include "HSpectrometerCalibrate.h"
#include "HSpectrometerProtocol.h"
#include "HSpectrometerTest.h"

HSpectrometer::HSpectrometer()
{
    _algorithm = new HSpectrometerAlgorithm();
    _calibrate = new HSpectrometerCalibrate();
    _protocol = new HSpectrometerProtocol();
    _test = new HSpectrometerTest(_calibrate);
}

HSpectrometer::~HSpectrometer()
{
    closeProtocol();
    delete _test;
    delete _protocol;
    delete _calibrate;
    delete _algorithm;
}

bool HSpectrometer::setSmooth(int times, int range)
{
    return _calibrate->setSmooth(times, range);
}

void HSpectrometer::setStdCurve(vector<double> value)
{
    _calibrate->setStdCurve(value);
}

double HSpectrometer::pelsToWave(int value)
{
    return _calibrate->toWave(value);
}

bool HSpectrometer::openProtocol()
{
    if (!_protocol->open())
        return false;

    vector<unsigned char> data;
    if (!_protocol->getRam(data))
        return false;
    return _calibrate->setPackData(data);
}

bool HSpectrometer::closeProtocol()
{
    return _protocol->close();
}

bool HSpectrometer::setIntegralTime(double value)
{
    value = _test->setIntegralTime(value);
    return _protocol->setIntegralTime(value);
}

bool HSpectrometer::getSample(vector<double> &value, double &percent, bool fit)
{
    vector<int> data;
    if (!_protocol->getSample(data))
        return false;

    value = processSample(data, percent, fit);
    return true;
}

bool HSpectrometer::getSampleI(double integrationTime, vector<double> &value, double &percent, bool fit)
{
    vector<int> data;
    if (!_protocol->getSampleI(integrationTime, data))
        return false;

    value = processSample(data, percent, fit);
    return true;
}

bool HSpectrometer::getSN(vector<unsigned char> &value)
{
    return _protocol->sn(value);
}

HSpectrometerData *HSpectrometer::getSpectrometerData(vector<double> value)
{
    auto r = _calibrate->calcWaveEnergy(value);
    return _algorithm->calcSpectrum(r[0], r[1]);
}

bool HSpectrometer::clearState()
{
    return _protocol->clearState();
}

bool HSpectrometer::queryState(int *value)
{
    return _protocol->queryState(value);
}

bool HSpectrometer::getSampleT(vector<double> &value, double &percent, bool fit)
{
    vector<int> data;
    if (!_protocol->getSampleT(data))
        return false;

    value = processSample(data, percent, fit);
    return true;
}

vector<double> HSpectrometer::processSample(vector<int> &data, double &percent, bool fit)
{
    vector<double> value;
    for (unsigned int i = 0; i < data.size(); i++)
        value.push_back(data[i] * 1.0);

    percent = 100 * _test->calcMaxSample(value) / 65535.0;
    return _test->preprocess(value, fit);
}
