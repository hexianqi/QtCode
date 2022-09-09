#include "HSpectrometer.h"
#include "HSpectrometerAlgorithm.h"
#include "HSpectrometerCalibrate.h"
#include "HSpectrometerProtocol.h"

HSpectrometer::HSpectrometer()
{
    _algorithm = new HSpectrometerAlgorithm();
    _calibrate = new HSpectrometerCalibrate();
    _protocol = new HSpectrometerProtocol();
}

HSpectrometer::~HSpectrometer()
{
    closeProtocol();
    delete _algorithm;
    delete _calibrate;
    delete _protocol;
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
