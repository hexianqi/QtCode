#pragma once

#include <vector>

using namespace std;

class CCalibrateSpec
{
public:
    CCalibrateSpec();
    ~CCalibrateSpec();

public:
    void reDefault();
    vector<int> dealBotton(vector<int> value);
    vector<int> fit(vector<int> value);
    vector<int> smooth(vector<int> value);
    vector<double> calcEnergy(vector<int> value);
    bool checkFrameOverflow(size_t size);
    double toWave(int value);
    int fit(int value);

public:
    bool setSmooth(int times, int range);
    bool setStdCurve(vector<double> value);
    bool setData(vector<unsigned char> value);
    vector<unsigned char> getData();

protected:
    double calcPlanck(double value);
    void calcFitCoefficients();

protected:
    vector<unsigned char> packSetting();
    vector<unsigned char> packPelWave();
    vector<unsigned char> packCurves();
    vector<unsigned char> packFit();
    bool unpackSetting(vector<unsigned char> value, size_t &pos);
    bool unpackPelWave(vector<unsigned char> value, size_t &pos);
    bool unpackCurves(vector<unsigned char> value, size_t &pos);
    bool unpackFit(vector<unsigned char> value, size_t &pos);

protected:
    int _reservePelsF;
    int _reservePelsT;
    int _smoothTimes;
    int _smoothRange;
    int _smoothFrame;
    double _stdColorTemperature;

    vector<double> _pels;
    vector<double> _waves;
    vector<int> _stdCurves;
    vector<double> _samples;
    vector<double> _fits;
    vector<double> _fitCoefficients;
};
