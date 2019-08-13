#include "ProtocolSpec.h"
#include "UsbPortCy.h"
#include <windows.h>
#include <cmath>

using namespace std;

CProtocolSpec::CProtocolSpec()
{
    _port = new CUsbPortCy;
    _simulate = false;
}

CProtocolSpec::~CProtocolSpec()
{
    close();
}

bool CProtocolSpec::open()
{
    if (_simulate)
        return true;
    if (!_port->open(0))
        return false;
    return setIntegralTime(2);
}

bool CProtocolSpec::close()
{
    if (_simulate)
        return true;
    return _port->close();
}

bool CProtocolSpec::setIntegralTime(double value)
{
    if (_simulate)
    {
        _integralTime = value;
        return true;
    }
    vector<unsigned char> data(4);
    unsigned int t = static_cast<unsigned int>(value * 500);
    data[0] = static_cast<unsigned char>((t >> 24) & 0xff);
    data[1] = static_cast<unsigned char>((t >> 16) & 0xff);
    data[2] = static_cast<unsigned char>((t >>  8) & 0xff);
    data[3] = static_cast<unsigned char>((t >>  0) & 0xff);
    return setData(0x01, data);
}

bool CProtocolSpec::getSpectrum(vector<int> &value, int sleepTime)
{
    if (_simulate)
    {
        value.clear();
        for (int i = 0; i < 2304; i++)
            value.push_back(simulate(i));
        return true;
    }
    vector<unsigned char> data;
    if (!getData(4176 + 4, 0x02, 0x00, data, sleepTime))
        return false;
    size_t size = data.size() / 2;
    value.resize(size);
    for (size_t i = 0; i < size; i++)
        value[i] = data[2 * i] * 256 + data[2 * i + 1];
    return true;
}

double CProtocolSpec::simulate(double v)
{
    if (v < 50)
        return 1000;

    double pi = 3.14159265359;
    double r = pi * v / 2304;
    double k = 600 * _integralTime;
    double t = k * sin(r);
    //    double p = 1 + ((qrand() % 2000) - 1000) / 100000.0;                    // 1%误差
    //    double p = (qrand() % 2000) - 1000;                                     // [-1000, 1000]误差
    //    double p = 0.9 + qSin(qDegreesToRadians(d->intergalTime * 1.8)) * 0.1;    // 和积分时间成sin曲线关系
    double p = 0.9 + sin(pi * t / 60000) * 0.1;          // 和采样值成sin曲线关系
    return t * p + 1000;
}

bool CProtocolSpec::setRam(vector<unsigned char> value)
{
    if (value.size() < 2)
        return false;

    int i, n;
    for (i = value.size() % 250; i != 0 && i < 250; i++)
        value.push_back(0);
    n = value.size() / 250;
    for (i = 0; i < n; i++)
    {
        vector<unsigned char> buff;
        buff.push_back(i + 1);
        buff.insert(buff.end(), value.begin() + i * 250, value.begin() + (i + 1) * 250);
        if (!setData(0x03, buff, 300))
            return false;
    }
    return true;
}

bool CProtocolSpec::getRam(vector<unsigned char> &value)
{
    vector<unsigned char> buff;
    size_t size = 250 + 4;
    if (!getData(size, 0x04, 0x01, buff))
        return false;
    value.clear();
    value.insert(value.end(), buff.begin(), buff.end());

    unsigned char n = std::ceil((value[0] * 256.0 + value[1]) / 250);
    for (unsigned char i = 1; i < n; i++)
    {
        if (!getData(size, 0x04, i + 1, buff, 300))
            return false;
        value.insert(value.end(), buff.begin(), buff.end());
    }
    return true;
}

bool CProtocolSpec::setData(unsigned char cmd, vector<unsigned char> value, int sleepTime)
{
    if (value.size() % 2 == 0)
        value.push_back(0);
    size_t size = value.size() + 3;
    vector<unsigned char> downData;
    vector<unsigned char> upData(4);
    downData.push_back(size / 256);
    downData.push_back(size % 256);
    downData.push_back(cmd);
    downData.insert(downData.end(), value.begin(), value.end());

    if (!transport(downData, upData, sleepTime))
        return false;
    if (upData.size() < 4
        || upData[0] != 0x00
        || upData[1] != 0x04
        || upData[2] != cmd)
        return false;
    return true;
}

bool CProtocolSpec::getData(int size, unsigned char cmd, unsigned char block, vector<unsigned char> &value, int sleepTime)
{
    vector<unsigned char> downData;
    vector<unsigned char> upData(size);
    downData.push_back(0x00);
    downData.push_back(0x04);
    downData.push_back(cmd);
    downData.push_back(block);

    if (!transport(downData, upData, sleepTime))
        return false;
    if (upData.size() < 4
        || upData[0] != size / 256
        || upData[1] != size % 256
        || upData[2] != cmd)
        return false;
    value.clear();
    for (int i = 4; i < size; i++)
        value.push_back(upData[i]);
    return true;
}

bool CProtocolSpec::transport(vector<unsigned char> downData, vector<unsigned char> &upData, int sleepTime)
{
    if (_port->write(downData))
        return false;

    if (sleepTime > 10)
        Sleep(sleepTime);
    return _port->read(upData);
}
