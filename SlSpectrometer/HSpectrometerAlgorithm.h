#pragma once

#include "HSpectrometerData.h"
#include "HCie.h"

class HSpectrometerAlgorithm
{
public:
    HSpectrometerAlgorithm();
    ~HSpectrometerAlgorithm();

public:
    HSpectrometerData *calcSpectrum(vector<double> wave, vector<double> energy);

public:
    vector<double> wave();

protected:
    void calcEnergy(HSpectrometerData *);
    void calcChromaticity(HSpectrometerData *);
    void calcRenderingIndex(HSpectrometerData *);
    void calcPhotopicVision(HSpectrometerData *);

protected:
    CIE_UCS calcCieUcs(double tc);

protected:
    vector<double> _wave;

protected:
    HCie1931 *_cie1931;
    HCieUcs *_cieUcs;
    HCieDaylight *_cieDaylight;
    HPhotopicVision *_photopicVision;
};

