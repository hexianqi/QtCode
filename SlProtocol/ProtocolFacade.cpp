#include "ProtocolFacade.h"
#include "ProtocolSpec.h"
#include "CalibrateSpec.h"
#include "TestSpec.h"

CProtocolFacade::CProtocolFacade()
{
    _protocol = new CProtocolSpec();
    _calibrate = new CCalibrateSpec();
    _test = new CTestSpec(_calibrate);
}

CProtocolFacade::~CProtocolFacade()
{
    closeProtocol();
}

bool CProtocolFacade::openProtocol()
{
    if (!_protocol->open())
        return false;

    vector<unsigned char> buff;
    if (!_protocol->getRam(buff))
        return false;
    return _calibrate->setData(buff);
}

bool CProtocolFacade::closeProtocol()
{
    return _protocol->close();
}

bool CProtocolFacade::setIntegralTime(double value)
{
    value = _test->setIntegralTime(value);
    return _protocol->setIntegralTime(value);
}

bool CProtocolFacade::setSmooth(int times, int range)
{
    return _calibrate->setSmooth(times, range);
}

bool CProtocolFacade::getSpectrumSample(vector<int> &value, double &percent, bool fit)
{
    vector<int> data;
    if (!_protocol->getSpectrum(data, _test->commWaitTime()))
        return false;

    percent = 100 * _test->calcMaxSample(data) / 65535.0;
    value = _test->preprocess(data);
    if (fit)
    {
        for (size_t i = 0; i < value.size(); i++)
            value[i] = handleNonlinear(value[i]);
    }
    return true;
}

bool CProtocolFacade::getSpectrumEnergy(vector<double> &value, double &percent)
{
    vector<double> result;
    vector<int> data;

    if (!getSpectrumSample(data, percent, true))
        return false;
    value = _test->calcEnergy(data);
    return true;
}

double CProtocolFacade::pelsToWave(int value)
{
    return _calibrate->toWave(value);
}

double CProtocolFacade::handleNonlinear(int value)
{
    return _calibrate->fit(value);
}

bool CProtocolFacade::setStdCurve(vector<double> value)
{
    return _calibrate->setStdCurve(value);
}

bool CProtocolFacade::setCalibrateData(vector<unsigned char> value)
{
    return _calibrate->setData(value);
}

bool CProtocolFacade::getCalibrateData(vector<unsigned char> &value)
{
    value = _calibrate->getData();
    return true;
}
