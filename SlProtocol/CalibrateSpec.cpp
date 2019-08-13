#include "CalibrateSpec.h"
#include "ProtocolHelper.h"
#include <algorithm>

unsigned int readUInt16(vector<unsigned char> data, size_t &pos)
{
    unsigned char v1 = data[pos++];
    unsigned char v2 = data[pos++];
    return v1 * 256 + v2;
}

vector<unsigned char> writeUInt16(unsigned int data)
{
    vector<unsigned char> r;
    r.push_back(data / 256);
    r.push_back(data % 256);
    return r;
}

bool checkHead(vector<unsigned char> data, size_t &pos, int &version)
{
    if (data.size() < pos + 4)
        return false;
    int size = readUInt16(data, pos);
    version = readUInt16(data, pos);
    return data.size() >= size + pos - 4;
}

CCalibrateSpec::CCalibrateSpec()
{
    _stdCurves.clear();
    reDefault();
}

CCalibrateSpec::~CCalibrateSpec()
{
}

void CCalibrateSpec::reDefault()
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
    _samples.clear();
    _samples.push_back(0);
    _samples.push_back(65535);
    _fits.clear();
    _fits.push_back(1);
    _fits.push_back(1);
}

vector<int> CCalibrateSpec::dealBotton(vector<int> value)
{
    int i;
    int avgbase = 0;
    int size = value.size();

    for (i = _reservePelsF; i <= _reservePelsT && i < size; i++)
        avgbase += value[i];
    avgbase /= _reservePelsT - _reservePelsF + 1;

    for (i = 0; i < size; i++)
        value[i] = value[i] - avgbase;

    return value;
}

vector<int> CCalibrateSpec::fit(vector<int> value)
{
    vector<int> r;
    for (int i = 0; i < value.size(); i++)
        r.push_back(fit(value[i]));
    return r;
}

vector<int> CCalibrateSpec::smooth(vector<int> value)
{
    int i, j, k, m, n;
    int size, avg;
    vector<int> temp;

    size = value.size();
    temp.resize(size);

    for (k = 0; k < _smoothTimes; k++)
    {
        for (i = 0; i < size; i++)
        {
            avg = value[i];
            for (j = 1; j <= _smoothRange; j++)
            {
                m = max(i - j, 0);
                n = min(i + j, size - 1);
                avg += value[m] + value[n];
            }
            temp[i] = avg / (2 * _smoothRange + 1);
        }
        value = temp;
    }
    return value;
}

vector<double> CCalibrateSpec::calcEnergy(vector<int> value)
{
    double x, y, r;
    vector<double> xa, ya;
    size_t size = value.size();
    if (size > _stdCurves.size())
        size = _stdCurves.size();
    if (size <= 0)
        return ya;

    for (size_t i = 0; i < size; i++)
    {
        if (value[i] < 50)
            r = 0;
        else if (_stdCurves[i] < 50)
            r = 1;
        else
            r = 1.0 * value[i] / _stdCurves[i];
        x = toWave(i);
        y = r * calcPlanck(x);
        xa.push_back(x);
        ya.push_back(y);
    }
    return ya;
//	return CProtocolHelper::interpolate(xa, ya, 380.0, 780.0, 0.1);
}

bool CCalibrateSpec::checkFrameOverflow(size_t size)
{
    return size >= _smoothFrame;
}

bool CCalibrateSpec::setSmooth(int times, int range)
{
    if (times < 0 || times > 10 || range < 0 || range > 10)
        return false;
    _smoothTimes = times;
    _smoothRange = range;
    return true;
}

bool CCalibrateSpec::setStdCurve(vector<double> value)
{
    _stdCurves.clear();
    for (size_t i = 0; i < value.size(); i++)
        _stdCurves.push_back(int(value[i]));
    return true;
}

bool CCalibrateSpec::setData(vector<unsigned char> value)
{
    size_t pos = 0;
    int version = 0;
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

vector<unsigned char> CCalibrateSpec::getData()
{
    vector<unsigned char> v;
    v.push_back(0x00);		// 大小
    v.push_back(0x00);
    v.push_back(0x00);		// 版本
    v.push_back(0x01);
    vector<unsigned char> s = packSetting();
    vector<unsigned char> p = packPelWave();
    vector<unsigned char> f = packFit();
    v.insert(v.end(), s.begin(), s.end());
    v.insert(v.end(), p.begin(), p.end());
    v.insert(v.end(), f.begin(), f.end());
    v[0] = v.size() / 256;
    v[1] = v.size() % 256;
    return v;
}

double CCalibrateSpec::toWave(int value)
{
    return CProtocolHelper::interpolate(_pels, _waves, value);
}

int CCalibrateSpec::fit(int value)
{
    if (value < 0 || value >= _fitCoefficients.size())
        return value;
    return value / _fitCoefficients[value];
}

double CCalibrateSpec::calcPlanck(double value)
{
    return CProtocolHelper::planck(value, _stdColorTemperature);
}

void CCalibrateSpec::calcFitCoefficients()
{
    _fitCoefficients.clear();
    double s = _samples[_samples.size() - 1];
    double f = _fits[_fits.size() - 1];
    double c = 1;

    for (int i = 0; i < 65536; i++)
    {
        //if (i < _samples[0])
        //	c = _fits[0];
        //else if (i > s)
        //	c = f;
        //else
            c = CProtocolHelper::interpolate(_samples, _fits, i);
        _fitCoefficients.push_back(c);
    }
}

vector<unsigned char> CCalibrateSpec::packSetting()
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

vector<unsigned char> CCalibrateSpec::packPelWave()
{
    size_t i;
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

vector<unsigned char> CCalibrateSpec::packCurves()
{
    size_t i;
    vector<unsigned char> v;
    v.push_back(0x00);		// 大小
    v.push_back(0x00);
    v.push_back(0x00);		// 版本
    v.push_back(0x01);
    v.push_back(_stdCurves.size() / 256);
    v.push_back(_stdCurves.size() % 256);
    for (i = 0; i < _stdCurves.size(); i++)
    {
        v.push_back(_stdCurves[i] / 256);
        v.push_back(_stdCurves[i] % 256);
    }
    v[0] = v.size() / 256;
    v[1] = v.size() % 256;
    return v;
}

vector<unsigned char> CCalibrateSpec::packFit()
{
    size_t i;
    vector<unsigned char> v;
    v.push_back(0x00);		// 大小
    v.push_back(0x00);
    v.push_back(0x00);		// 版本
    v.push_back(0x01);
    v.push_back(_samples.size() / 256);
    v.push_back(_samples.size() % 256);
    for (i = 0; i < _samples.size(); i++)
    {
        v.push_back(int(_samples[i]) / 256);
        v.push_back(int(_samples[i]) % 256);
        v.push_back(int(_fits[i] * 10000) / 256);
        v.push_back(int(_fits[i] * 10000) % 256);
    }
    v[0] = v.size() / 256;
    v[1] = v.size() % 256;
    return v;
}

bool CCalibrateSpec::unpackSetting(vector<unsigned char> value, size_t &pos)
{
    int version = 0;
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

bool CCalibrateSpec::unpackPelWave(vector<unsigned char> value, size_t &pos)
{
    int version = 0;
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

bool CCalibrateSpec::unpackCurves(vector<unsigned char> value, size_t &pos)
{
    int version = 0;
    if (!checkHead(value, pos, version))
        return false;

    _stdCurves.clear();
    int size = readUInt16(value, pos);
    for (int i = 0; i < size; i++)
        _stdCurves.push_back(readUInt16(value, pos));
    return true;
}

bool CCalibrateSpec::unpackFit(vector<unsigned char> value, size_t &pos)
{
    int version = 0;
    if (!checkHead(value, pos, version))
        return false;

    _samples.clear();
    _fits.clear();
    int size = readUInt16(value, pos);
    for (int i = 0; i < size; i++)
    {
        _samples.push_back(readUInt16(value, pos));
        _fits.push_back(readUInt16(value, pos) / 10000.0);
    }
    return true;
}
