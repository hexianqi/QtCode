#include "HCie.h"
#include "HSpectrometerHelper.h"
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

HCie1931::HCie1931()
{
    read1931();
    readTc32();
}

vector<double> HCie1931::calcCoordinate(vector<double> wave, vector<double> energy)
{
    unsigned int i = 0;
    unsigned int j = 0;
    double X = 0;
    double Y = 0;
    double Z = 0;
    while (i < wave.size() && j < _cie1931.size())
    {
        if (fabs(wave[i] - _cie1931[j].wave) < 1e-6)
        {
            X += energy[i] * _cie1931[j].X;
            Y += energy[i] * _cie1931[j].Y;
            Z += energy[i] * _cie1931[j].Z;
            i++;
            j++;
            continue;
        }
        if (wave[i] < _cie1931[j].wave)
            i++;
        else
            j++;
    }
    Z = X + 15 * Y + 3 * Z;

    auto u = 4 * X / Z;
    auto v = 6 * Y / Z;
    auto xy = HSpectrometerHelper::uv2xy(u, v);
    auto uvp = HSpectrometerHelper::uv2uvp(u, v);
    auto cd = HSpectrometerHelper::uv2cd(u, v);
    return { u, v, xy[0], xy[1], uvp[0], uvp[1], cd[0], cd[1] };
}

vector<double> HCie1931::calcWaveDominantPurity(double x, double y)
{
    int i;
    double xd,lx,ly,ls,rx,ry,rs;
    double wave,purity;
    auto slope = (y - 0.3333) / (x - 0.3333);
    auto left = x < 0.3333 ? slope <= _cie1931.front().slope : slope < _cie1931.back().slope;
    if (left)
    {
        i = 0;
        ls = _cie1931[i].slope;
        lx = _cie1931[i].x;
        ly = _cie1931[i].y;
        while (true)
        {
            i++;
            rs = _cie1931[i].slope;
            rx = _cie1931[i].x;
            ry = _cie1931[i].y;
            if ((slope <ls && slope > rs) || _cie1931[i].wave > 554)
                break;
            ls = rs;
            lx = rx;
            ly = ry;
        }
        xd = (ly - 0.3333 + slope * 0.3333 - (ry -ly) * lx / (rx - lx)) / (slope - (ry -ly) / (rx -lx));
        wave = _cie1931[i].wave + (xd - rx) / (rx - lx);
    }
    else
    {
        i = 470;
        rs = _cie1931[i].slope;
        rx = _cie1931[i].x;
        ry = _cie1931[i].y;
        while (true)
        {
            i--;
            ls = _cie1931[i].slope;
            lx = _cie1931[i].x;
            ly = _cie1931[i].y;
            if ((slope < ls && slope > rs) || _cie1931[i].wave < 555)
                break;
            rs = ls;
            rx = lx;
            ry = ly;
        }
        xd = (ly - 0.3333 + slope * 0.3333 - (ry - ly) * lx / (rx - lx)) / (slope - (ry - ly) / (rx - lx));
        wave = _cie1931[i].wave + (xd - lx) / (rx - lx);
    }
    purity = (x - 0.3333) / (xd - 0.3333);
    return { wave, purity };
}

vector<vector<double> > HCie1931::calcColorReflectance(vector<double> wave, vector<double> energy)
{
    unsigned int i, j, k, l;
    double sum = 0.0;
    vector<double> X(15, 0), Y(15, 0), Z(15, 0);
    vector<double> ui(15, 0), vi(15, 0), Yi(15, 0);

    i = 0;
    j = 0;
    k = 0;
    while (i < wave.size() && j < _cie1931.size() && k < _cieTc32.size())
    {
        if (fabs(wave[i] - _cie1931[j].wave) < 1e-6 && fabs(wave[i] - _cieTc32[k].wave) < 1e-6)
        {
            for (l = 0; l < 15; l++)
            {
                X[l] += energy[i] * _cie1931[j].X * _cieTc32[k].S[l];
                Y[l] += energy[i] * _cie1931[j].Y * _cieTc32[k].S[l];
                Z[l] += energy[i] * _cie1931[j].Z * _cieTc32[k].S[l];
            }
            sum += energy[i] * _cie1931[j].Y;
            i++;
            j++;
            k++;
            continue;
        }
        if (wave[i] < _cie1931[j].wave || wave[i] < _cieTc32[k].wave)
        {
            i++;
            continue;
        }
        if (_cie1931[j].wave < wave[i] || _cie1931[j].wave < _cieTc32[k].wave)
        {
            j++;
            continue;
        }
        k++;
    }
    sum = 100 / sum;
    for (i = 0; i < 15; i++)
    {
        Yi[i] = Y[i] * sum;
        ui[i] = 4 * X[i] / (X[i] + 15 * Y[i] + 3 * Z[i]);
        vi[i] = 6 * Y[i] / (X[i] + 15 * Y[i] + 3 * Z[i]);
    }
    return {ui, vi, Yi};
}

ISOTHERM HCie1931::calcIsotherm(double tc)
{
    double ubar,vbar,wbar;
    double P,U,V,W,R;
    double Pprime,Uprime,Vprime,Wprime,Rprime;

    U = 0;
    V = 0;
    W = 0;
    Uprime = 0;
    Vprime = 0;
    Wprime = 0;
    for (unsigned i = 0; i < _cie1931.size(); i++)
    {
        ubar = _cie1931[i].X * 2 / 3;
        vbar = _cie1931[i].Y;
        wbar = -0.5 * _cie1931[i].X + 1.5 * _cie1931[i].Y + 0.5 * _cie1931[i].Z;
        P = HSpectrometerHelper::planck(tc, _cie1931[i].wave);
        U += P * ubar;
        V += P * vbar;
        W += P * wbar;
        Pprime = HSpectrometerHelper::planckPrime(tc, _cie1931[i].wave);
        Uprime += Pprime * ubar;
        Vprime += Pprime * vbar;
        Wprime += Pprime * wbar;
    }
    R = U + V + W;
    Rprime = Uprime + Vprime + Wprime;
    return ISOTHERM { tc, U / R, V / R, -1.0 * (Uprime * R - U * Rprime) / (Vprime * R - V * Rprime) };
}

vector<double> HCie1931::calcIsoCoordinate(double tc)
{
    auto iso = calcIsotherm(tc);
    auto xy = HSpectrometerHelper::uv2xy(iso.u, iso.v);
    return {iso.u, iso.v, xy[0], xy[1]};
}

void HCie1931::read1931()
{
    int i, n;
    string str, line;
    fstream fin("Dat\\CIE1931.dat");

    if (getline(fin, line))
    {
        stringstream ss(line);
        ss >> str >> n;
    }
    else
        return;

    getline(fin, line);
    getline(fin, line);
    _cie1931.resize(n);
    i = 0;
    while (getline(fin, line) && i < n)
    {
        istringstream ss(line);
        ss >> _cie1931[i].wave >> _cie1931[i].X >> _cie1931[i].Y >> _cie1931[i].Z >> _cie1931[i].x >> _cie1931[i].y >> _cie1931[i].z >> _cie1931[i].slope;
        i++;
    }
    fin.close();
}

void HCie1931::readTc32()
{
    int i, j, n;
    string str, line;
    fstream fin("Dat\\CIE_TC_32.dat");

    if (getline(fin, line))
    {
        stringstream ss(line);
        ss >> str >> n;
    }
    else
        return;

    getline(fin, line);
    getline(fin, line);
    _cieTc32.resize(n);
    i = 0;
    while (getline(fin, line) && i < n)
    {
        istringstream ss(line);
        ss >> _cieTc32[i].wave;
        for (j = 0; j < 15; j++)
            ss >> _cieTc32[i].S[j];
        i++;
    }
    fin.close();
}

HCieUcs::HCieUcs()
{
    read();
    readP();
}

vector<double> HCieUcs::calcColorTemperatureDuv(double u, double v)
{
    unsigned int i,n;
    double sign,t,min;

    n = 0;
    min = pow(_cieUcs[0].urt - u, 2) + pow(_cieUcs[0].vrt - v, 2);
    for (i = 1; i < _cieUcs.size(); i++)
    {
        t = pow(_cieUcs[i].urt - u, 2) + pow(_cieUcs[i].vrt - v, 2);
        if (t < min)
        {
            min = t;
            n = i;
            sign = _cieUcs[i].vrt > v ? -1.0 : 1.0;
        }
    }
    if (n > 0)
        return { _cieUcs[n].Tc, sign * sqrt(min) };

    min = pow(_cieUcsP[0].urt - u, 2) + pow(_cieUcsP[0].vrt - v, 2);
    for (i = 1; i < _cieUcsP.size(); i++)
    {
        t = pow(_cieUcsP[i].urt - u, 2) + pow(_cieUcsP[i].vrt - v, 2);
        if (t < min)
        {
            min = t;
            n = i;
            sign = _cieUcsP[i].vrt > v ? -1.0 : 1.0;
        }
    }
    return { _cieUcsP[n].Tc, sign * sqrt(min) };
}

CIE_UCS HCieUcs::findCieUcs(double tc)
{
    if (tc >= 2300 && tc <= 25000)
    {
        for (unsigned int i = 0; i < _cieUcs.size() - 1; i++)
        {
            if (fabs(tc - _cieUcs[i].Tc) < 1e-6 || (tc > _cieUcs[i].Tc && tc < _cieUcs[i + 1].Tc))
                return _cieUcs[i];
        }
    }
    return {};
}

void HCieUcs::read()
{
    int i, j, n;
    string str, line;
    fstream fin("Dat\\CIE_UCS.dat");

    if (getline(fin, line))
    {
        stringstream ss(line);
        ss >> str >> n;
    }
    else
        return;

    getline(fin, line);
    getline(fin, line);
    _cieUcs.resize(n);
    i = 0;
    while (getline(fin, line) && i < n)
    {
        istringstream ss(line);
        ss >> _cieUcs[i].Tc >> _cieUcs[i].urt >> _cieUcs[i].vrt >> _cieUcs[i].xt >> _cieUcs[i].yt >> _cieUcs[i].ur >> _cieUcs[i].vr >> _cieUcs[i].cr >> _cieUcs[i].dr;
        for (j = 0; j < 15; j++)
            ss >> _cieUcs[i].Ur[j];
        for (j = 0; j < 15; j++)
            ss >> _cieUcs[i].Vr[j];
        for (j = 0; j < 15; j++)
            ss >> _cieUcs[i].Wr[j];
        i++;
    }
    fin.close();
}

void HCieUcs::readP()
{
    int i, n;
    string str, line;
    fstream fin("Dat\\CIE_UCS_P.dat");

    if (getline(fin, line))
    {
        stringstream ss(line);
        ss >> str >> n;
    }
    else
        return;

    getline(fin, line);
    getline(fin, line);
    _cieUcsP.resize(n);
    i = 0;
    while (getline(fin, line) && i < n)
    {
        istringstream ss(line);
        ss >> _cieUcsP[i].Tc >> _cieUcsP[i].urt >> _cieUcsP[i].vrt;
        i++;
    }
    fin.close();
}

HCieDaylight::HCieDaylight()
{
    read();
}

vector<double> HCieDaylight::calcRefSourceSpectrum(double tc, vector<double> wave)
{
    vector<double> result;
    for (unsigned int i = 0; i < wave.size(); i++)
        result.push_back(calcRefSpectrum(tc, wave[i]));
    return result;
}

void HCieDaylight::read()
{
    int i, j, n;
    string str, line;
    fstream fin("Dat\\CIE_DAY.dat");

    if (getline(fin, line))
    {
        stringstream ss(line);
        ss >> str >> n;
    }
    else
        return;

    getline(fin, line);
    getline(fin, line);
    _cieDaylight.resize(n);
    i = 0;
    while (getline(fin, line) && i < n)
    {
        istringstream ss(line);
        ss >> _cieDaylight[i].wave;
        for (j = 0; j < 3; j++)
            ss >> _cieDaylight[i].S[j];
        i++;
    }
    fin.close();
}

double HCieDaylight::calcRefSpectrum(double tc, double wave)
{
    if (tc <= 4000)
        return calcRefSpectrumP(tc, wave);
    if (tc >= 5000)
        return calcRefSpectrumD(tc, wave);
    return calcRefSpectrumM(tc, wave);
}

double HCieDaylight::calcRefSpectrumP(double tc, double wave)
{
    return HSpectrometerHelper::planck(tc, wave);
}

double HCieDaylight::calcRefSpectrumD(double tc, double wave)
{
    unsigned int i;
    double xd;

    if (tc <= 7000)
        xd = -4.6070e9 / pow(tc, 3) + 2.9678e6 / pow(tc, 2) + 0.09911e3 / tc + 0.244063;
    else
        xd = -2.0064e9 / pow(tc, 3) + 1.9018e6 / pow(tc, 2) + 0.24748e3 / tc + 0.237040;
    auto yd = -3.000 * xd * xd + 2.870 * xd - 0.275;
    auto m1 = (-1.3515 - 1.7703 * xd + 5.9114 * yd) / (0.0241 + 0.2562 * xd - 0.7341 * yd);
    auto m2 = (0.0300 - 31.4424 * xd + 30.0717 * yd) / (0.0241 + 0.2562 * xd - 0.7341 * yd);

    for (i = 1; i < _cieDaylight.size() - 1; i++)
        if (wave <= _cieDaylight[i].wave)
            break;
    auto wave1 = _cieDaylight[i-1].wave;
    auto wave2 = _cieDaylight[i].wave;
    auto sp1 = _cieDaylight[i-1].S[0] + m1 * _cieDaylight[i-1].S[1] + m2 * _cieDaylight[i-1].S[2];
    auto sp2 = _cieDaylight[i].S[0] + m1 * _cieDaylight[i].S[1] + m2 * _cieDaylight[i].S[2];
    return max(0.0, HSpectrometerHelper::interpolate(wave, wave1, sp1, wave2, sp2));
}

double HCieDaylight::calcRefSpectrumM(double tc, double wave)
{
    auto sp = calcRefSpectrumP(tc, wave);
    auto sd = calcRefSpectrumD(tc, wave);
    return sp * (5000 - tc) / 1000 + sd * (tc - 4000) / 1000;
}

HPhotopicVision::HPhotopicVision()
{
    read();
}

vector<double> HPhotopicVision::calcPhotopic(vector<double> wave, vector<double> energy)
{
    unsigned int i,j;
    double r,g,b,t;
    double sum1,sum2;

    i = 0;
    j = 0;
    r = 0;
    g = 0;
    b = 0;
    sum1 = 0.0;
    sum2 = 0.0;
    while (i < wave.size() && j < _wave.size())
    {
        if (fabs(wave[i] - _wave[j]) < 1e-6)
        {
            t = energy[i] * _ratio[j];
            sum1 += energy[i];
            sum2 += t;
            if (wave[i] >= 380 && wave[i] < 500)
                b += t;
            if (wave[i] >= 500 && wave[i] < 600)
                g += t;
            if (wave[i] >= 600 && wave[i] < 780)
                r += t;
            i++;
            j++;
        }
        else if (wave[i] < _wave[j])
            i++;
        else
            j++;
    }
    if (sum1 < 1e-9)
        return {0.0, 0.0, 0.0, 0.0, 0.0};

    auto rgb = r + g + b;
    auto visionFlux = 683 * sum2;              // lm
    auto visionEfficien = 683 * sum2 / sum1;   // lm/W
    auto ratioRed = 100 * r / rgb;
    auto ratioGreen = 100 * g / rgb;
    auto ratioBlue = 100 * b / rgb;
    return {visionFlux, visionEfficien, ratioRed, ratioGreen, ratioBlue};
}

void HPhotopicVision::read()
{
    unsigned int i, n;
    string str, line;
    vector<double> wave, ratio;
    fstream fin("Dat\\PhotopicVision.dat");

    if (getline(fin, line))
    {
        stringstream ss(line);
        ss >> str >> n;
    }
    else
        return;

    getline(fin, line);
    getline(fin, line);
    wave.resize(n);
    ratio.resize(n);
    i = 0;
    while (getline(fin, line) && i < n)
    {
        istringstream ss(line);
        ss >> wave[i] >> ratio[i];
        i++;
    }
    fin.close();

    if (wave.size() < 2)
        return;

    auto r = HSpectrometerHelper::interpolate(wave, ratio, wave.front(), wave.back(), 0.1);
    _wave = r[0];
    _ratio = r[1];
}

// data.h
// extern const char *gdat;

// data.cpp
//#include "data.h"
//const char *gdat = "16\n"
//                   "0.0950125098376374401853193354250\n"
//                   "0.281603550779258913230460501460\n"
//                   "0.458016777657227386342419442983\n"
//                   "0.617876244402643748446671764049\n"
//                   "0.755404408355003033895101194847\n"
//                   "0.865631202387831743880467897713\n"
//                   "0.944575023073232576077988415535\n"
//                   "0.989400934991649932596154173450\n"
//                   "0.189450610455068496285396723209\n"
//                   "0.182603415044923588866763667977\n"
//                   "0.169156519395002538189312079058\n"
//                   "0.149595988816576732081501730116\n"
//                   "0.124628971255533872052476277863\n"
//                   "0.0951585116824927848099251053810\n"
//                   "0.0622535239386478928628438391746\n"
//                   "0.0271524594117540948517805723700\n";

// main.cpp
//#include <iostream>
//#include <sstream>
//#include <vector>
//#include "data.h"
//using namespace std;
//int main()
//{
//    int n;
//    vector<double> value;
//    stringstream ss(gdat);

//    ss >> n;
//    value.resize(n);

//    for (int i = 0; i < n ; i++)
//        ss >> value[i];

//    for (size_t i = 0; i < value.size(); i++)
//        cout << i << " : " << value[i] << endl;
//    return 0;
//}




