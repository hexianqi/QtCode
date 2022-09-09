#pragma once

#include "HSpectrometerGlobal.h"

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
    bool openProtocol();
    bool closeProtocol();


protected:
    HSpectrometerAlgorithm *_algorithm;
    HSpectrometerCalibrate *_calibrate;
    HSpectrometerProtocol *_protocol;
};
