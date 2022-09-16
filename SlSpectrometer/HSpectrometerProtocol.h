#pragma once

#include <vector>
#include <thread>

using namespace std;

class HUsbPortCy;

class HSpectrometerProtocol
{
public:
    HSpectrometerProtocol();
    ~HSpectrometerProtocol();

public:
    bool isSimulate();

public:
    bool open();
    bool close();
    void setSimulate(bool b);
    bool setIntegralTime(double value);
    bool getSample(vector<int> &value);
    bool setRam(vector<unsigned char> value);
    bool getRam(vector<unsigned char> &value);
    bool sn(vector<unsigned char> &value);

public:
    bool getSampleI(double integrationTime, vector<int> &value);
    bool clearState();
    bool queryState(int *value);
    bool startSample(double integrationTime);
    bool getSampleT(vector<int> &value);

protected:
    bool setData(unsigned char cmd, vector<unsigned char> value, int sleepTime = 0);
    bool getData(int size, unsigned char cmd, unsigned char block, vector<unsigned char> &value, int sleepTime = 0);
    bool transport(vector<unsigned char> downData, vector<unsigned char> &upData, int sleepTime = 0);
    double simulateData(double v);

protected:
    double _integralTime;
    bool _simulate;
    HUsbPortCy *_port;
    thread *_thread;
};
