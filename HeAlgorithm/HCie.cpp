#include "HCie.h"
#include "HSpecHelper.h"
#include "HLinearFit.h"
#include "HMath.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QDebug>

HE_BEGIN_NAMESPACE

HCie1931::HCie1931()
{
    read1931();
    readTc32();
}

QPointF HCie1931::calcCoordinateUV(const QPolygonF &spd)
{
    int i = 0;
    int j = 0;
    double X = 0;
    double Y = 0;
    double Z = 0;
    while (i < spd.size() && j < _cie1931.size())
    {
        if (fabs(spd.at(i).x() - _cie1931[j].wave) < 1e-6)
        {
            X += spd.at(i).y() * _cie1931[j].X;
            Y += spd.at(i).y() * _cie1931[j].Y;
            Z += spd.at(i).y() * _cie1931[j].Z;
            i++;
            j++;
            continue;
        }
        if (spd.at(i).x() < _cie1931[j].wave)
            i++;
        else
            j++;
    }
    Z = X + 15 * Y + 3 * Z;
    return qFuzzyIsNull(Z) ? QPointF(0.0, 0.0) : QPointF(4 * X / Z, 6 * Y / Z);
}

double HCie1931::calcDuv(QPointF uv, double tc)
{
    auto uvt = calcIsoCoordinateUV(tc);
    auto sign = uvt.y() > uv.y() ? -1.0 : 1.0;
    return sign * sqrt(pow(uvt.x() - uv.x(), 2) + pow(uvt.y() - uv.y(), 2));
}

QList<double> HCie1931::calcWaveDominantPurity(QPointF xy)
{
    int i;
    double xd,lx,ly,ls,rx,ry,rs;
    double wave,purity;

    auto slope = (xy.y() - 0.3333) / (xy.x() - 0.3333);
    auto left = xy.x() < 0.3333 ? slope <= _cie1931.first().slope : slope < _cie1931.last().slope;
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
    purity = (xy.x() - 0.3333) / (xd - 0.3333);
    return QList<double>() << wave << purity;
}

QList<QVector<double>> HCie1931::calcColorReflectance(QPolygonF spd)
{
    int i,j,k,l;
    double sum;
    QVector<double> X(15), Y(15), Z(15);
    QVector<double> ui(15), vi(15), Yi(15);

    i = 0;
    j = 0;
    k = 0;
    sum = 0;
    X.fill(0, 15);
    Y.fill(0, 15);
    Z.fill(0, 15);
    while (i < spd.size() && j < _cie1931.size() && k < _cieTc32.size())
    {
        if (fabs(spd[i].x() - _cie1931[j].wave) < 1e-6 && fabs(spd[i].x() - _cieTc32[k].wave) < 1e-6)
        {
            for (l = 0; l < 15; l++)
            {
                X[l] += spd[i].y() * _cie1931[j].X * _cieTc32[k].S[l];
                Y[l] += spd[i].y() * _cie1931[j].Y * _cieTc32[k].S[l];
                Z[l] += spd[i].y() * _cie1931[j].Z * _cieTc32[k].S[l];
            }
            sum += spd[i].y() * _cie1931[j].Y;
            i++;
            j++;
            k++;
            continue;
        }
        if (spd[i].x() < _cie1931[j].wave || spd[i].x() < _cieTc32[k].wave)
        {
            i++;
            continue;
        }
        if (_cie1931[j].wave < spd[i].x() || _cie1931[j].wave < _cieTc32[k].wave)
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

QPointF HCie1931::calcIsoCoordinateUV(double tc)
{
    auto iso = calcIsotherm(tc);
    return {iso.u, iso.v};
}

QPointF HCie1931::calcIsoCoordinateXY(double tc)
{
    auto uv = calcIsoCoordinateUV(tc);
    return HSpecHelper::uv2xy(uv);
}

ISOTHERM HCie1931::calcIsotherm(double tc)
{
    int i;
    double ubar,vbar,wbar;
    double P,U,V,W,R;
    double Pprime,Uprime,Vprime,Wprime,Rprime;

    U = 0;
    V = 0;
    W = 0;
    Uprime = 0;
    Vprime = 0;
    Wprime = 0;
    for (i = 0; i < _cie1931.size(); i++)
    {
        ubar = _cie1931[i].X * 2 / 3;
        vbar = _cie1931[i].Y;
        wbar = -0.5 * _cie1931[i].X + 1.5 * _cie1931[i].Y + 0.5 * _cie1931[i].Z;
        P = HSpecHelper::planck(tc, _cie1931[i].wave);
        U += P * ubar;
        V += P * vbar;
        W += P * wbar;
        Pprime = HSpecHelper::planckPrime(tc, _cie1931[i].wave);
        Uprime += Pprime * ubar;
        Vprime += Pprime * vbar;
        Wprime += Pprime * wbar;
    }
    R = U + V + W;
    Rprime = Uprime + Vprime + Wprime;
    return ISOTHERM { tc, U / R, V / R, -1.0 * (Uprime * R - U * Rprime) / (Vprime * R - V * Rprime) };
}

ISOTHERM HCie1931::calcIsothermFit(double tc)
{
    QVector<QPointF> points;

    auto uv = calcIsoCoordinateUV(tc);
    for (int i = 0; i < 11; i++)
        points.append(calcIsoCoordinateUV(tc + (i - 4) * 0.1));
    auto ca = HLinearFit::linear(points);
    return ISOTHERM { tc, uv.x(), uv.y(), -1.0 / ca[0] };
}

QPolygonF HCie1931::normalizedY100(const QPolygonF &spd)
{
    int i = 0;
    int j = 0;

    QPolygonF result;
    double sum = 0.0;
    while (i < spd.size() && j < _cie1931.size())
    {
        if (fabs(spd.at(i).x() - _cie1931[j].wave) < 1e-6)
        {
            sum += spd.at(i).y() * _cie1931[j].Y;
            continue;
        }
        if (spd.at(i).x() < _cie1931[j].wave)
            i++;
        else
            j++;
    }
    if (qFuzzyIsNull(sum))
        return spd;
    for (auto p : spd)
        result << QPointF(p.x(), 100 * p.y() / sum);
    return result;
}

void HCie1931::read1931()
{
    int i,n;
    QString str;

    QFile file(":/dat/CIE1931.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    _cie1931.resize(n);
    str = in.readLine();
    str = in.readLine();
    for (i = 0; i < n; i++)
        in >> _cie1931[i].wave >> _cie1931[i].X >> _cie1931[i].Y >> _cie1931[i].Z >> _cie1931[i].x >> _cie1931[i].y >> _cie1931[i].z >> _cie1931[i].slope;
    file.close();
}

void HCie1931::readTc32()
{
    int i,j,n;
    QString str;

    QFile file(":/dat/CIE_TC_32.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    _cieTc32.resize(n);
    str = in.readLine();
    str = in.readLine();
    for (i = 0; i < n; i++)
    {
        in >> _cieTc32[i].wave;
        for (j = 0; j < 15; j++)
            in >> _cieTc32[i].S[j];
    }
    file.close();
}

HCieDaylight::HCieDaylight()
{
    read();
}

QPolygonF HCieDaylight::calcRefSourceSpectrum(double tc, QPointF wave, double interval)
{
    int i,n;
    double x,y;
    QPolygonF poly;

    n = ceil((wave.y() - wave.x()) / interval + 1);
    for (i = 0; i < n; i++)
    {
        x = wave.x() + interval * i;
        y = calcRefSpectrum(tc, x);
        poly << QPointF(x, y);
    }
    return poly;
}

void HCieDaylight::read()
{
    int i,j,n;
    QString str;

    QFile file(":/dat/CIE_DAY.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    _data.resize(n);
    str = in.readLine();
    str = in.readLine();
    for (i = 0; i < n; i++)
    {
        in >> _data[i].wave;
        for (j = 0; j < 3; j++)
            in >> _data[i].S[j];
    }
    file.close();
}

double HCieDaylight::calcRefSpectrum(double tc, double wave)
{
//    if (tc <= 5000)
//        return calcRefSpectrumP(wave, tc);
//    return calcRefSpectrumD(wave, tc);

    if (tc <= 4000)
        return calcRefSpectrumP(tc, wave);
    if (tc >= 5000)
        return calcRefSpectrumD(tc, wave);
    return calcRefSpectrumM(tc, wave);
}

double HCieDaylight::calcRefSpectrumP(double tc, double wave)
{
    return HSpecHelper::planck(tc, wave);
}

double HCieDaylight::calcRefSpectrumD(double tc, double wave)
{
    int i;
    double xd;

    if (tc <= 7000)
        xd = -4.6070e9 / pow(tc, 3) + 2.9678e6 / pow(tc, 2) + 0.09911e3 / tc + 0.244063;
    else
        xd = -2.0064e9 / pow(tc, 3) + 1.9018e6 / pow(tc, 2) + 0.24748e3 / tc + 0.237040;
    auto yd = -3.000 * xd * xd + 2.870 * xd - 0.275;
    auto m1 = (-1.3515 - 1.7703 * xd + 5.9114 * yd) / (0.0241 + 0.2562 * xd - 0.7341 * yd);
    auto m2 = (0.0300 - 31.4424 * xd + 30.0717 * yd) / (0.0241 + 0.2562 * xd - 0.7341 * yd);

    for (i = 1; i < _data.size() - 1; i++)
        if (wave <= _data[i].wave)
            break;
    auto wave1 = _data[i-1].wave;
    auto wave2 = _data[i].wave;
    auto sp1 = _data[i-1].S[0] + m1 * _data[i-1].S[1] + m2 * _data[i-1].S[2];
    auto sp2 = _data[i].S[0] + m1 * _data[i].S[1] + m2 * _data[i].S[2];
    return qMax(0.0, HMath::interpolate(wave, wave1, sp1, wave2, sp2));
}

double HCieDaylight::calcRefSpectrumM(double tc, double wave)
{
    auto sp = calcRefSpectrumP(tc, wave);
    auto sd = calcRefSpectrumD(tc, wave);
    return sp * (5000 - tc) / 1000 + sd * (tc - 4000) / 1000;
}

HCieUcs::HCieUcs()
{
    read();
    readP();
}

QList<double> HCieUcs::calcColorTemperatureDuv(QPointF uv)
{
    int i,n;
    double sign,t,min;
    auto u = uv.x();
    auto v = uv.y();

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
        return QList<double>() << _cieUcs[n].Tc << sign * sqrt(min);

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
    return QList<double>() << _cieUcsP[n].Tc << sign * sqrt(min);
}

CIE_UCS HCieUcs::findCieUcs(double tc)
{
    if (tc >= 2300 && tc <= 25000)
    {
        for (int i = 0; i < _cieUcs.size() - 1; i++)
        {
            if (fabs(tc - _cieUcs[i].Tc) < 1e-6 || (tc > _cieUcs[i].Tc && tc < _cieUcs[i+1].Tc))
                return _cieUcs[i];
        }
    }
    return {};
}

void HCieUcs::read()
{
    int i,j,n;
    QString str;

    QFile file(":/dat/CIE_UCS.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    _cieUcs.resize(n);
    str = in.readLine();
    str = in.readLine();
    for (i = 0; i < n; i++)
    {
        in >> _cieUcs[i].Tc >> _cieUcs[i].urt >> _cieUcs[i].vrt >> _cieUcs[i].xt >> _cieUcs[i].yt >> _cieUcs[i].ur >> _cieUcs[i].vr >> _cieUcs[i].cr >> _cieUcs[i].dr;
        for (j = 0; j < 15; j++)
            in >> _cieUcs[i].Ur[j];
        for (j = 0; j < 15; j++)
            in >> _cieUcs[i].Vr[j];
        for (j = 0; j < 15; j++)
            in >> _cieUcs[i].Wr[j];
    }
    file.close();
}

void HCieUcs::readP()
{
    int i,n;
    QString str;

    QFile file(":/dat/CIE_UCS_P.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    _cieUcsP.resize(n);
    str = in.readLine();
    str = in.readLine();
    for (i = 0; i < n; i++)
        in >> _cieUcsP[i].Tc >> _cieUcsP[i].urt >> _cieUcsP[i].vrt;
    file.close();
}

HIsotherm::HIsotherm()
{
    read();
}

double HIsotherm::calcColorTemperature(QPointF uv)
{
    return calcColorTemperature(uv.x(), uv.y());
}

double HIsotherm::calcColorTemperature(double u, double v)
{
    auto index = 0;
    auto d2 = 0.0;
    auto d1 = calcDistance(0, u, v);
    for (int i = 1; i < _data.size(); i++)
    {
        d2 = calcDistance(i, u, v);
        if (d1 / d2 < 0)
        {
            index = i;
            break;
        }
        d1 = d2;
    }
    return index == 0 ? 0 : 1/(1/_data[index-1].Tc + (1/_data[index].Tc - 1/_data[index-1].Tc) * d1 / (d1 - d2));
}

void HIsotherm::read()
{
    int i,n;
    QString str;

    QFile file(":/dat/Isotherm.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    _data.resize(n);
    str = in.readLine();
    str = in.readLine();
    for (i = 0; i < n; i++)
        in >> _data[i].Tc >> _data[i].u >> _data[i].v >> _data[i].slope;
    file.close();
}

double HIsotherm::calcDistance(int i, double u, double v)
{
    return (v - _data[i].v - _data[i].slope * (u - _data[i].u)) / sqrt(1 + _data[i].slope * _data[i].slope);
}

HE_END_NAMESPACE

