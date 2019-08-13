#pragma once

#include <vector>

using namespace std;

class CUsbPortCy;

class CProtocolSpec
{
public:
    CProtocolSpec();
    ~CProtocolSpec();

public:
    bool open();
    bool close();
    bool setIntegralTime(double value);
    bool getSpectrum(vector<int> &value, int sleepTime);
    bool setRam(vector<unsigned char> value);
    bool getRam(vector<unsigned char> &value);

protected:
    bool setData(unsigned char cmd, vector<unsigned char> value, int sleepTime = 0);
    bool getData(int size, unsigned char cmd, unsigned char block, vector<unsigned char> &value, int sleepTime = 0);
    bool transport(vector<unsigned char> downData, vector<unsigned char> &upData, int sleepTime = 0);
    double simulate(double v);

protected:
    CUsbPortCy *_port;
    double _integralTime;
    bool _simulate;
};
