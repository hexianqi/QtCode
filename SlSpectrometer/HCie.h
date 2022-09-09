#pragma once

#include <vector>

using namespace std;

// CMF(color matching function) = 2
struct CIE1931
{
    double wave;
    double X;
    double Y;
    double Z;
    double x;
    double y;
    double z;
    double slope;
};

struct CIE_TC_32
{
    double wave;
    double S[15];
};

struct CIE_UCS
{
    double Tc;
    double urt;
    double vrt;
    double xt;
    double yt;
    double ur;
    double vr;
    double cr;
    double dr;
    double Ur[15];
    double Vr[15];
    double Wr[15];
};

struct CIE_UCS_P
{
    double Tc;
    double urt;
    double vrt;
};

struct CIE_DAYLIGHT
{
    double wave;
    double S[3];
};

struct ISOTHERM
{
    double Tc;
    double u;
    double v;
    double slope;
};

class HCie1931
{
public:
    HCie1931();

public:
    vector<double> calcCoordinate(vector<double> wave, vector<double> energy);
    vector<double> calcWaveDominantPurity(double x, double y);
    vector<vector<double> > calcColorReflectance(vector<double> wave, vector<double> energy);
    vector<double> calcIsoCoordinate(double tc);
    ISOTHERM calcIsotherm(double tc);

protected:
    void read1931();
    void readTc32();

protected:
    vector<CIE1931> _cie1931;
    vector<CIE_TC_32> _cieTc32;
};

class HCieUcs
{
public:
    HCieUcs();

public:
    vector<double> calcColorTemperatureDuv(double u, double v);
    CIE_UCS findCieUcs(double tc);

protected:
    void read();
    void readP();

protected:
    vector<CIE_UCS> _cieUcs;
    vector<CIE_UCS_P> _cieUcsP;
};

class HCieDaylight
{
public:
    HCieDaylight();

public:
    vector<double> calcRefSourceSpectrum(double tc, vector<double> wave);

protected:
    void read();
    double calcRefSpectrum(double tc, double wave);
    double calcRefSpectrumP(double tc, double wave);
    double calcRefSpectrumD(double tc, double wave);
    double calcRefSpectrumM(double tc, double wave);

protected:
    vector<CIE_DAYLIGHT> _cieDaylight;
};

class HPhotopicVision
{
public:
    HPhotopicVision();

public:
    vector<double> calcPhotopic(vector<double> wave, vector<double> energy);

protected:
    void read();

protected:
    vector<double> _wave;
    vector<double> _ratio;
};

