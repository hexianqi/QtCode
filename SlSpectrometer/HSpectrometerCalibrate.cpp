#include "HSpectrometerCalibrate.h"
#include "HSpectrometerHelper.h"
#include <math.h>

unsigned int readUInt16(vector<unsigned char> data, unsigned int &pos)
{
    auto v1 = data[pos++];
    auto v2 = data[pos++];
    return v1 * 256 + v2;
}

vector<unsigned char> writeUInt16(unsigned int data)
{
    vector<unsigned char> r;
    r.push_back(data / 256);
    r.push_back(data % 256);
    return r;
}

bool checkHead(vector<unsigned char> data, unsigned int &pos, unsigned int &version)
{
    if (data.size() < pos + 4)
        return false;
    auto size = readUInt16(data, pos);
    version = readUInt16(data, pos);
    return data.size() >= size + pos - 4;
}

HSpectrometerCalibrate::HSpectrometerCalibrate()
{
    _stdCurves.clear();
    reDefault();
}

HSpectrometerCalibrate::~HSpectrometerCalibrate()
{
}

void HSpectrometerCalibrate::reDefault()
{
    _reservePelsF = 15;
    _reservePelsT = 32;
    _smoothTimes = 2;
    _smoothRange = 2;
    _smoothFrame = 3;
    _stdColorTemperature = 2855.61;
    _fitCoefficients.clear();
    _pels.clear();
    _pels.push_back(460);
    _pels.push_back(585);
    _pels.push_back(1030);
    _pels.push_back(1388);
    _pels.push_back(1653);
    _pels.push_back(1878);
    _pels.push_back(1933);
    _waves.clear();
    _waves.push_back(404.7);
    _waves.push_back(435.8);
    _waves.push_back(546.1);
    _waves.push_back(632.8);
    _waves.push_back(696.5);
    _waves.push_back(750.4);
    _waves.push_back(763.5);
    _fitSamples.clear();
    _fitSamples.push_back(0);
    _fitSamples.push_back(65535);
    _fitValues.clear();
    _fitValues.push_back(1);
    _fitValues.push_back(1);
}

vector<double> HSpectrometerCalibrate::dealBotton(vector<double> value)
{
    int i;
    int size = value.size();
    double avgbase = 0.0;

    for (i = _reservePelsF; i <= _reservePelsT && i < size; i++)
        avgbase += value[i];
    avgbase /= _reservePelsT - _reservePelsF + 1.0;

    for (i = 0; i < size; i++)
        value[i] = value[i] - avgbase;

    return value;
}

vector<double> HSpectrometerCalibrate::fit(vector<double> value)
{
    vector<double> r;
    for (unsigned int i = 0; i < value.size(); i++)
        r.push_back(fit(value[i]));
    return r;
}

vector<double> HSpectrometerCalibrate::smooth(vector<double> value)
{
    int i, j, k, m, n, size;
    double avg = 0.0;;
    vector<double> temp;

    size = value.size();
    temp.resize(size);

    for (k = 0; k < _smoothTimes; k++)
    {
        for (i = 0; i < size; i++)
        {
            avg = value[i];
            for (j = 1; j <= _smoothRange; j++)
            {
                m = fmax(i - j, 0);
                n = fmin(i + j, size - 1);
                avg += value[m] + value[n];
            }
            temp[i] = avg / (2 * _smoothRange + 1);
        }
        value = temp;
    }
    return value;
}

vector<vector<double> > HSpectrometerCalibrate::calcWaveEnergy(vector<double> value)
{
    double x, y, r;
    vector<double> xa, ya;
    unsigned int size = fmin(value.size(), _stdCurves.size());
    if (size <= 0)
        return { xa, ya };

    for (unsigned int i = 0; i < size; i++)
    {
        if (value[i] < 50)
            r = 0.0;
        else if (_stdCurves[i] < 50)
            r = 1.0;
        else
            r = 1.0 * value[i] / _stdCurves[i];
        x = toWave(i);
        y = r * calcPlanck(x);
        xa.push_back(x);
        ya.push_back(y);
    }
    return HSpectrometerHelper::interpolate(xa, ya, 380.0, 780.0, 0.1);
}

bool HSpectrometerCalibrate::checkFrameOverflow(int size)
{
    return size >= _smoothFrame;
}

double HSpectrometerCalibrate::toWave(double value)
{
    return HSpectrometerHelper::interpolate(value, _pels, _waves);
}

double HSpectrometerCalibrate::fit(double value)
{
    if (value < 0 || value >= _fitCoefficients.size())
        return value;
    return value / _fitCoefficients[int(value)];
}

bool HSpectrometerCalibrate::setSmooth(int times, int range)
{
    if (times < 0 || times > 10 || range < 0 || range > 10)
        return false;
    _smoothTimes = times;
    _smoothRange = range;
    return true;
}

void HSpectrometerCalibrate::setStdCurve(vector<double> value)
{
    _stdCurves = value;
}

bool HSpectrometerCalibrate::setPackData(vector<unsigned char> value)
{
    unsigned int pos = 0;
    unsigned int version = 0;
    if (!checkHead(value, pos, version))
        return false;
    if (!unpackSetting(value, pos))
        return false;
    if (!unpackPelWave(value, pos))
        return false;
    //if (!unpackCurves(value, pos))
    //	return false;
    if (!unpackFit(value, pos))
        return false;
    calcFitCoefficients();
    return true;
}

vector<unsigned char> HSpectrometerCalibrate::getPackData()
{
    vector<unsigned char> v;
    vector<unsigned char> s = packSetting();
    vector<unsigned char> p = packPelWave();
//    vector<unsigned char> c = packCurves();
    vector<unsigned char> f = packFit();
    v.push_back(0x00);		// 大小
    v.push_back(0x00);
    v.push_back(0x00);		// 版本
    v.push_back(0x01);

    v.insert(v.end(), s.begin(), s.end());
    v.insert(v.end(), p.begin(), p.end());
//    v.insert(v.end(), c.begin(), c.end());
    v.insert(v.end(), f.begin(), f.end());
    v[0] = v.size() / 256;
    v[1] = v.size() % 256;
    return v;
}

double HSpectrometerCalibrate::calcPlanck(double value)
{
    return HSpectrometerHelper::planck(_stdColorTemperature, value);
}

void HSpectrometerCalibrate::calcFitCoefficients()
{
    _fitCoefficients.clear();
    auto s0 = _fitSamples.front();
    auto s1 = _fitSamples.back();
    auto v0 = _fitValues.front();
    auto v1 = _fitValues.back();
    auto c = 1.0;
    for (int i = 0; i < 65536; i++)
    {
        if (i < s0)
            c = v0;
        else if (i > s1)
            c = v1;
        else
            c = HSpectrometerHelper::interpolate(i, _fitSamples, _fitValues);
        _fitCoefficients.push_back(c);
    }
}

vector<unsigned char> HSpectrometerCalibrate::packSetting()
{
    vector<unsigned char> v;
    v.push_back(0x00);		// 大小
    v.push_back(0x00);
    v.push_back(0x00);		// 版本
    v.push_back(0x01);
    v.push_back(_reservePelsF / 256);
    v.push_back(_reservePelsF % 256);
    v.push_back(_reservePelsT / 256);
    v.push_back(_reservePelsT % 256);
    v.push_back(_smoothTimes / 256);
    v.push_back(_smoothTimes % 256);
    v.push_back(_smoothRange / 256);
    v.push_back(_smoothRange % 256);
    v.push_back(_smoothFrame / 256);
    v.push_back(_smoothFrame % 256);
    v.push_back(int(_stdColorTemperature * 10) / 256);
    v.push_back(int(_stdColorTemperature * 10) % 256);
    v[0] = v.size() / 256;
    v[1] = v.size() % 256;
    return v;
}

vector<unsigned char> HSpectrometerCalibrate::packPelWave()
{
    unsigned int i;
    vector<unsigned char> v;
    v.push_back(0x00);		// 大小
    v.push_back(0x00);
    v.push_back(0x00);		// 版本
    v.push_back(0x01);
    v.push_back(_pels.size() / 256);
    v.push_back(_pels.size() % 256);
    for (i = 0; i < _pels.size(); i++)
    {
        v.push_back(int(_pels[i]) / 256);
        v.push_back(int(_pels[i]) % 256);
        v.push_back(int(_waves[i] * 10) / 256);
        v.push_back(int(_waves[i] * 10) % 256);
    }
    v[0] = v.size() / 256;
    v[1] = v.size() % 256;
    return v;
}

vector<unsigned char> HSpectrometerCalibrate::packCurves()
{
    unsigned int i;
    int value;
    vector<unsigned char> v;
    v.push_back(0x00);		// 大小
    v.push_back(0x00);
    v.push_back(0x00);		// 版本
    v.push_back(0x01);
    v.push_back(_stdCurves.size() / 256);
    v.push_back(_stdCurves.size() % 256);
    for (i = 0; i < _stdCurves.size(); i++)
    {
        value = (int)_stdCurves[i];
        v.push_back(value / 256);
        v.push_back(value % 256);
    }
    v[0] = v.size() / 256;
    v[1] = v.size() % 256;
    return v;
}

vector<unsigned char> HSpectrometerCalibrate::packFit()
{
    unsigned int i;
    vector<unsigned char> v;
    v.push_back(0x00);		// 大小
    v.push_back(0x00);
    v.push_back(0x00);		// 版本
    v.push_back(0x01);
    v.push_back(_fitSamples.size() / 256);
    v.push_back(_fitSamples.size() % 256);
    for (i = 0; i < _fitSamples.size(); i++)
    {
        v.push_back(int(_fitSamples[i]) / 256);
        v.push_back(int(_fitSamples[i]) % 256);
        v.push_back(int(_fitValues[i] * 10000) / 256);
        v.push_back(int(_fitValues[i] * 10000) % 256);
    }
    v[0] = v.size() / 256;
    v[1] = v.size() % 256;
    return v;
}

bool HSpectrometerCalibrate::unpackSetting(vector<unsigned char> value, unsigned int &pos)
{
    unsigned int version = 0;
    if (!checkHead(value, pos, version))
        return false;

    _reservePelsF = readUInt16(value, pos);
    _reservePelsT = readUInt16(value, pos);
    _smoothTimes = readUInt16(value, pos);
    _smoothRange = readUInt16(value, pos);
    _smoothFrame = readUInt16(value, pos);
    _stdColorTemperature = readUInt16(value, pos) / 10.0;
    return true;
}

bool HSpectrometerCalibrate::unpackPelWave(vector<unsigned char> value, unsigned int &pos)
{
    unsigned int version = 0;
    if (!checkHead(value, pos, version))
        return false;

    _pels.clear();
    _waves.clear();
    int size = readUInt16(value, pos);
    for (int i = 0; i < size; i++)
    {
        _pels.push_back(readUInt16(value, pos));
        _waves.push_back(readUInt16(value, pos) / 10.0);
    }
    return true;
}

bool HSpectrometerCalibrate::unpackCurves(vector<unsigned char> value, unsigned int &pos)
{
    unsigned int version = 0;
    if (!checkHead(value, pos, version))
        return false;

    _stdCurves.clear();
    int size = readUInt16(value, pos);
    for (int i = 0; i < size; i++)
        _stdCurves.push_back(readUInt16(value, pos));
    return true;
}

bool HSpectrometerCalibrate::unpackFit(vector<unsigned char> value, unsigned int &pos)
{
    unsigned int version = 0;
    if (!checkHead(value, pos, version))
        return false;

    _fitSamples.clear();
    _fitValues.clear();
    int size = readUInt16(value, pos);
    for (int i = 0; i < size; i++)
    {
        _fitSamples.push_back(readUInt16(value, pos));
        _fitValues.push_back(readUInt16(value, pos) / 10000.0);
    }
    return true;
}
