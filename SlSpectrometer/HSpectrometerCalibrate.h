#pragma once

#include <vector>

using namespace std;

class HSpectrometerCalibrate
{
public:
    HSpectrometerCalibrate();
    ~HSpectrometerCalibrate();

public:
    void reDefault();
    vector<double> dealBotton(vector<double> value);
    vector<double> fit(vector<double> value);
    vector<double> smooth(vector<double> value);
    vector< vector<double> > calcWaveEnergy(vector<double> value);
    bool checkFrameOverflow(int size);
    double toWave(double value);
    double fit(double value);

public:
    bool setSmooth(int times, int range);
    void setStdCurve(vector<double> value);
    bool setPackData(vector<unsigned char> value);
    vector<unsigned char> getPackData();

protected:
    double calcPlanck(double value);
    void calcFitCoefficients();

protected:
    vector<unsigned char> packSetting();
    vector<unsigned char> packPelWave();
    vector<unsigned char> packCurves();
    vector<unsigned char> packFit();
    bool unpackSetting(vector<unsigned char> value, unsigned int &pos);
    bool unpackPelWave(vector<unsigned char> value, unsigned int &pos);
    bool unpackCurves(vector<unsigned char> value, unsigned int &pos);
    bool unpackFit(vector<unsigned char> value, unsigned int &pos);

protected:
    int _reservePelsF;
    int _reservePelsT;
    int _smoothTimes;
    int _smoothRange;
    int _smoothFrame;
    double _stdColorTemperature;

    vector<double> _pels;
    vector<double> _waves;
    vector<double> _stdCurves;
    vector<double> _fitCoefficients;
    vector<double> _fitSamples;
    vector<double> _fitValues;
};

