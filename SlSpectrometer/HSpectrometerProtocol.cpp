#include "HSpectrometerProtocol.h"
#include "HUsbPortCy.h"
#include <math.h>
#include <windows.h>
#include <thread>
#include <mutex>
#include <condition_variable>

#ifdef USE_SPEC
#define DOWN_SIZE 4
#else
#define DOWN_SIZE 8
#endif

int _state;
vector<unsigned char> _downData(DOWN_SIZE);
vector<unsigned char> _upData(4180);
vector<int> _outdata(2088);

#ifdef H_THREAD_COMM
bool _stop = false;
mutex _mutex;
condition_variable _condition;

void processing_thread(HUsbPortCy *port)
{
    while(true)
    {
        unique_lock<std::mutex> lock(_mutex);
        _condition.wait(lock);

        if (_stop)
            break;

        _state = 0;
        if (!port->write(_downData))
        {
            _state = -1;
            continue;
        }

        _state = 1;
        if (!port->read(_upData))
        {
            _state = -1;
            continue;
        }

        for (unsigned int i = 0; i < _outdata.size(); i++)
            _outdata[i] = _upData[2 * i + 4] * 256 + _upData[2 * i + 4];
        _state = 2;
        lock.unlock();
    }
}
#endif

HSpectrometerProtocol::HSpectrometerProtocol()
{
    _integralTime = 2;
    _simulate = false;
    _port = new HUsbPortCy;
#ifdef H_THREAD_COMM
    _thread = new thread(processing_thread, _port);
#endif

}

HSpectrometerProtocol::~HSpectrometerProtocol()
{
#ifdef H_THREAD_COMM
    _stop = true;
    _condition.notify_one();
    _thread->join();
#endif
    close();
}

bool HSpectrometerProtocol::isSimulate()
{
    return _simulate;
}

bool HSpectrometerProtocol::open()
{
    if (_simulate)
        return true;
    if (!_port->open(0))
        return false;
    return setIntegralTime(2);
}

bool HSpectrometerProtocol::close()
{
    if (_simulate)
        return true;
    return _port->close();
}

void HSpectrometerProtocol::setSimulate(bool b)
{
    _simulate = b;
}

bool HSpectrometerProtocol::setIntegralTime(double value)
{
    if (_simulate)
    {
        _integralTime = value;
        return true;
    }
    vector<unsigned char> data(4);
    unsigned int t = static_cast<unsigned int>(value * 1000);
    data[0] = static_cast<unsigned char>((t >> 24) & 0xff);
    data[1] = static_cast<unsigned char>((t >> 16) & 0xff);
    data[2] = static_cast<unsigned char>((t >>  8) & 0xff);
    data[3] = static_cast<unsigned char>((t >>  0) & 0xff);
    return setData(0x01, data);
}

bool HSpectrometerProtocol::getSpectrum(vector<int> &value)
{
    if (_simulate)
    {
        value.clear();
        for (int i = 0; i < 2304; i++)
            value.push_back(simulateData(i));
        return true;
    }

    vector<unsigned char> data;
    if (!getData(4176 + 4, 0x02, 0x00, data))
        return false;
    size_t size = data.size() / 2;
    value.resize(size);
    for (size_t i = 0; i < size; i++)
        value[i] = data[2 * i] * 256 + data[2 * i + 1];
    return true;
}

bool HSpectrometerProtocol::setRam(vector<unsigned char> value)
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

bool HSpectrometerProtocol::getRam(vector<unsigned char> &value)
{
    vector<unsigned char> buff;
    size_t size = 250 + 4;
    if (!getData(size, 0x04, 0x01, buff))
        return false;
    value.clear();
    value.insert(value.end(), buff.begin(), buff.end());

    unsigned char n = ceil((value[0] * 256.0 + value[1]) / 250);
    for (unsigned char i = 1; i < n; i++)
    {
        if (!getData(size, 0x04, i + 1, buff, 300))
            return false;
        value.insert(value.end(), buff.begin(), buff.end());
    }
    return true;
}

bool HSpectrometerProtocol::sn(vector<unsigned char> &value)
{
    vector<unsigned char> downData;
    vector<unsigned char> upData(8);
    downData.push_back(0x00);
    downData.push_back(0x04);
    downData.push_back(0x05);
    downData.push_back(0x00);

    if (!transport(downData, upData))
        return false;
    if (upData.size() < 4
        || upData[0] != 0x00
        || upData[1] != 0x08
        || upData[2] != 0x05)
        return false;
    value.clear();
    for (int i = 0; i < 4; i++)
        value.push_back(upData[i + 3]);
    return true;
}

bool HSpectrometerProtocol::getSpectrumI(double integrationTime, vector<int> &value)
{
    _state = 0;
    unsigned int t = static_cast<unsigned int>(integrationTime * 1000);
    int size1 = 512;
    int size2 = 3668;
    vector<unsigned char> downData;
    vector<unsigned char> upData1(size1);
    vector<unsigned char> upData2(size2);
    downData.push_back(0x00);
    downData.push_back(0x08);
    downData.push_back(0x06);
    downData.push_back(static_cast<unsigned char>((t >> 24) & 0xff));
    downData.push_back(static_cast<unsigned char>((t >> 16) & 0xff));
    downData.push_back(static_cast<unsigned char>((t >>  8) & 0xff));
    downData.push_back(static_cast<unsigned char>((t >>  0) & 0xff));
    downData.push_back(0x00);

    if (!_port->write(downData))
        return false;

    _state = 1;
    if (!_port->read(upData1))
        return false;
    if (!_port->read(upData2))
        return false;
    value.resize(2088);
    for (int i = 0; i < 254; i++)
        value[i] = upData1[2 * i + 4] * 256 + upData1[2 * i + 4];
    for (int i = 0; i < 1834; i++)
        value[254 + i] = upData2[2 * i] * 256 + upData2[2 * i];
    _state = 2;
    return true;
}

bool HSpectrometerProtocol::clearState()
{
    _state = 0;
    return true;
}

bool HSpectrometerProtocol::queryState(int *value)
{
#ifndef H_THREAD_COMM
    if (_port->isReadyX())
        _state = 2;
#endif
    *value = _state;
    return true;
}

bool HSpectrometerProtocol::startSample(double integrationTime)
{
#ifdef USE_SPEC
    _downData[0] = 0x00;
    _downData[1] = 0x04;
    _downData[2] = 0x02;
    _downData[3] = 0x00;
#else
    unsigned int t = static_cast<unsigned int>(integrationTime * 1000);
    _downData[0] = 0x00;
    _downData[1] = 0x08;
    _downData[2] = 0x06;
    _downData[3] = static_cast<unsigned char>((t >> 24) & 0xff);
    _downData[4] = static_cast<unsigned char>((t >> 16) & 0xff);
    _downData[5] = static_cast<unsigned char>((t >>  8) & 0xff);
    _downData[6] = static_cast<unsigned char>((t >>  0) & 0xff);
    _downData[7] = 0x00;
#endif

#ifdef H_THREAD_COMM
    _state = 0;
    _condition.notify_one();
    return true;
#else
    if (_state == 1)
        return false;

    _state = 0;
    if (!_port->writeX(_downData, _upData))
    {
        _state = -1;
        return false;
    }
    _state = 1;
    return true;
#endif
}

bool HSpectrometerProtocol::getSpectrumT(vector<int> &value)
{
#ifdef H_THREAD_COMM
    value = _outdata;
#else
    if (_state != 2)
        return false;

    if (!_port->readX(_upData))
    {
        _state = -1;
        return false;
    }
    value.resize(2088);
    for (int i = 0; i < 2088; i++)
        value[i] = _upData[2 * i + 4] * 256 + _upData[2 * i + 4];
    return true;
#endif
    return true;
}

bool HSpectrometerProtocol::setData(unsigned char cmd, vector<unsigned char> value, int sleepTime)
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

bool HSpectrometerProtocol::getData(int size, unsigned char cmd, unsigned char block, vector<unsigned char> &value, int sleepTime)
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

bool HSpectrometerProtocol::transport(vector<unsigned char> downData, vector<unsigned char> &upData, int sleepTime)
{
    if (!_port->write(downData))
        return false;

    if (sleepTime > 10)
        Sleep(sleepTime);

    return _port->read(upData);
}

double HSpectrometerProtocol::simulateData(double v)
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
