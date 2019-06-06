#include "HCie.h"
#include "HLinearFit.h"
#include "HSpecHelper.h"
#include "HMath.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QtMath>

HE_ALGORITHM_BEGIN_NAMESPACE

HCieTc32::HCieTc32()
{
    readStandard();
}

int HCieTc32::size()
{
    return _stdData.size();
}

CIE_TC_32 HCieTc32::data(int i)
{
    return _stdData[i];
}

void HCieTc32::readStandard()
{
    int i,j,n;
    QString str;

    QFile file(":/dat/CIE_TC_32.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    _stdData.resize(n);
    str = in.readLine();
    str = in.readLine();

    for (i = 0; i < n; i++)
    {
        in >> _stdData[i].wave;
        for (j = 0; j < 15; j++)
            in >> _stdData[i].S[j];
    }
    file.close();
}

HCie1931::HCie1931()
{
    _cieTc32 = std::make_shared<HCieTc32>();
    readStandard();
}

QPointF HCie1931::calcCoordinateUv(QPolygonF spd)
{
    int i,j;
    double X,Y,Z;

    i = 0;
    j = 0;
    X = 0;
    Y = 0;
    Z = 0;
    while (i < spd.size() && j < _stdData.size())
    {
        if (qFabs(spd[i].x() - _stdData[j].wave) < 1e-6)
        {
            X += spd[i].y() * _stdData[j].X;
            Y += spd[i].y() * _stdData[j].Y;
            Z += spd[i].y() * _stdData[j].Z;
            i++;
            j++;
            continue;
        }
        if (spd[i].x() < _stdData[j].wave)
            i++;
        else
            j++;
    }
    Z = (X + 15 * Y + 3 * Z);
    return qFuzzyIsNull(Z) ? QPointF(0.0, 0.0) : QPointF(4 * X / Z, 6 * Y / Z);
}

double HCie1931::calcDuv(QPointF uv, double tc)
{
    auto uvt = calcIsoCoordinateUv(tc);
    return qSqrt(qPow(uvt.x() - uv.x(), 2) + qPow(uvt.y() - uv.y(), 2));
}

QList<double> HCie1931::calcDominantWavePurity(QPointF xy)
{
    int i;
    double xd,lx,ly,ls,rx,ry,rs;
    double wave,purity;

    auto slope = (xy.y() - 0.3333) / (xy.x() - 0.3333);
    auto left = xy.x() < 0.3333 ? slope <= _stdData.first().slope : slope < _stdData.last().slope;
    if (left)
    {
        i = 0;
        ls = _stdData[i].slope;
        lx = _stdData[i].x;
        ly = _stdData[i].y;
        while (1)
        {
            i++;
            rs = _stdData[i].slope;
            rx = _stdData[i].x;
            ry = _stdData[i].y;
            if ((slope <ls && slope > rs) || _stdData[i].wave > 554)
                break;
            ls = rs;
            lx = rx;
            ly = ry;
        }
        xd = (ly - 0.3333 + slope * 0.3333 - (ry -ly) * lx / (rx - lx)) / (slope - (ry -ly) / (rx -lx));
        wave = _stdData[i].wave - (xd - rx) / (lx - rx);
    }
    else
    {
        i = 470;
        rs = _stdData[i].slope;
        rx = _stdData[i].x;
        ry = _stdData[i].y;
        while (1)
        {
            i--;
            ls = _stdData[i].slope;
            lx = _stdData[i].x;
            ly = _stdData[i].y;
            if ((slope < ls && slope > rs) || _stdData[i].wave < 555)
                break;
            rs = ls;
            rx = lx;
            ry = ly;
        }
        xd = (ly - 0.3333 + slope * 0.3333 - (ry - ly) * lx / (rx - lx)) / (slope - (ry - ly) / (rx - lx));
        wave = _stdData[i].wave + (xd - lx) / (rx - lx);
    }
    purity = (xy.x() - 0.3333) / (xd - 0.3333);
    return QList<double>() << wave << purity;
}

void HCie1931::calcColorReflectance(QPolygonF spd, QVector<double> &ui, QVector<double> &vi, QVector<double> &Yi)
{
    int i,j,k,l;
    double sum;
    QVector<double> X(15);
    QVector<double> Y(15);
    QVector<double> Z(15);

    ui.resize(15);
    vi.resize(15);
    Yi.resize(15);

    i = 0;
    j = 0;
    k = 0;
    sum = 0;
    X.fill(0, 15);
    Y.fill(0, 15);
    Z.fill(0, 15);
    while (i < spd.size() && j < _stdData.size() && k < _cieTc32->size())
    {
        if (qFabs(spd[i].x() - _stdData[j].wave) < 1e-6 && qFabs(spd[i].x() - _cieTc32->data(k).wave) < 1e-6)
        {
            for (l = 0; l < 15; l++)
            {
                X[l] += spd[i].y() * _stdData[j].X * _cieTc32->data(k).S[l];
                Y[l] += spd[i].y() * _stdData[j].Y * _cieTc32->data(k).S[l];
                Z[l] += spd[i].y() * _stdData[j].Z * _cieTc32->data(k).S[l];
            }
            sum += spd[i].y() * _stdData[j].Y;
            i++;
            j++;
            k++;
            continue;
        }
        if (spd[i].x() < _stdData[j].wave || spd[i].x() < _cieTc32->data(k).wave)
        {
            i++;
            continue;
        }
        if (_stdData[j].wave < spd[i].x() || _stdData[j].wave < _cieTc32->data(k).wave)
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
}

QPointF HCie1931::calcIsoCoordinateUv(double tc)
{
    auto iso = calcIsotherm(tc);
    return QPointF(iso.u, iso.v);
}

QPointF HCie1931::calcIsoCoordinateXy(double tc)
{
    auto uv = calcIsoCoordinateUv(tc);
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
    for (i = 0; i < _stdData.size(); i++)
    {
        ubar = _stdData[i].X * 2 / 3;
        vbar = _stdData[i].Y;
        wbar = -0.5 * _stdData[i].X + 1.5 * _stdData[i].Y + 0.5 * _stdData[i].Z;
        P = HSpecHelper::planck(_stdData[i].wave, tc);
        U += P * ubar;
        V += P * vbar;
        W += P * wbar;
        Pprime = HSpecHelper::planckPrime(_stdData[i].wave, tc);
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

    auto uv = calcIsoCoordinateUv(tc);
    for (int i = 0; i < 11; i++)
        points.append(calcIsoCoordinateUv(tc + (i - 4) * 0.1));
    auto ca = HLinearFit::linear(points);
    return ISOTHERM { tc, uv.x(), uv.y(), -1.0 / ca[0] };
}

void HCie1931::readStandard()
{
    int i,n;
    QString str;

    QFile file(":/dat/CIE1931.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    _stdData.resize(n);
    str = in.readLine();
    str = in.readLine();

    for (i = 0; i < n; i++)
        in >> _stdData[i].wave >> _stdData[i].X >> _stdData[i].Y >> _stdData[i].Z >> _stdData[i].x >> _stdData[i].y >> _stdData[i].z >> _stdData[i].slope;
    file.close();
}

HCieDay::HCieDay()
{
    readStandard();
}

double HCieDay::calcRefSourceSpectrum(double tc, double wave)
{
    if (tc > 25000)
        return 0;

    if (tc <= 5000)
        return HSpecHelper::planck(wave, tc);

    int i;
    double xd;

    if (tc <= 7000)
        xd = -4.6070e9 / qPow(tc, 3) + 2.9678e6 / qPow(tc, 2) + 0.09911e3 / tc + 0.244063;
    else
        xd = -2.0064e9 / qPow(tc, 3) + 1.9018e6 / qPow(tc, 2) + 0.24748e3 / tc + 0.237040;
    auto yd = -3.000 * xd * xd + 2.870 * xd - 0.275;
    auto m1 = (-1.3515 - 1.7703 * xd + 5.9114 * yd) / (0.0241 + 0.2562 * xd - 0.7341 * yd);
    auto m2 = (0.0300 - 31.4424 * xd + 30.0717 * yd) / (0.0241 + 0.2562 * xd - 0.7341 * yd);

    for (i = 1; i < _stdData.size() - 1; i++)
        if (wave <= _stdData[i].wave)
            break;
    auto wave1 = _stdData[i-1].wave;
    auto wave2 = _stdData[i].wave;
    auto sp1 = _stdData[i-1].S[0] + m1 * _stdData[i-1].S[1] + m2 * _stdData[i-1].S[2];
    auto sp2 = _stdData[i].S[0] + m1 * _stdData[i].S[1] + m2 * _stdData[i].S[2];
    return qMax(0.0, HMath::interpolate(wave, wave1, wave2, sp1, sp2));
}

QPolygonF HCieDay::calcRefSourceSpectrum(double tc, QPointF wave, double interval)
{
    int i,n;
    double x,y;
    QPolygonF poly;

    n = qCeil((wave.y() - wave.x()) / interval + 1);
    for (i = 0; i < n; i++)
    {
        x = wave.x() + interval * i;
        y = calcRefSourceSpectrum(tc, x);
        poly.append(QPointF(x,y));
    }
    return poly;
}

void HCieDay::readStandard()
{
    int i,j,n;
    QString str;

    QFile file(":/dat/CIE_DAY.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    _stdData.resize(n);
    str = in.readLine();
    str = in.readLine();

    for (i = 0; i < n; i++)
    {
        in >> _stdData[i].wave;
        for (j = 0; j < 3; j++)
            in >> _stdData[i].S[j];
    }
    file.close();
}

HIsotherm::HIsotherm()
{
    readStandard();
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
    for (int i = 1; i < _stdData.size(); i++)
    {
        d2 = calcDistance(i, u, v);
        if ( d1/d2 < 0)
        {
            index = i;
            break;
        }
        d1 = d2;
    }
    return index == 0 ? 0 : 1/(1/_stdData[index-1].Tc + (1/_stdData[index].Tc - 1/_stdData[index-1].Tc) * d1 / (d1 - d2));
}

void HIsotherm::readStandard()
{
    int i,n;
    QString str;

    QFile file(":/dat/Isotherm.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    _stdData.resize(n);
    str = in.readLine();
    str = in.readLine();

    for (i = 0; i < n; i++)
        in >> _stdData[i].Tc >> _stdData[i].u >> _stdData[i].v >> _stdData[i].slope;
    file.close();
}

double HIsotherm::calcDistance(int i, double u, double v)
{
    return (v - _stdData[i].v - _stdData[i].slope * (u - _stdData[i].u)) / qSqrt(1 + _stdData[i].slope * _stdData[i].slope);
}

HCieUcs::HCieUcs()
{
    readStandard();
    readStandardP();
}

void HCieUcs::calcColorTemperature(QPointF uv, double &tc, double &duv)
{
    int i,n;
    double t,min;
    auto u = uv.x();
    auto v = uv.y();

    n = 0;
    min = (_cieUcs[0].urt - u) * (_cieUcs[0].urt - u) + (_cieUcs[0].vrt - v) * (_cieUcs[0].vrt - v);
    for (i = 1; i < _cieUcs.size(); i++)
    {
        t = (_cieUcs[i].urt - u) * (_cieUcs[i].urt - u) + (_cieUcs[i].vrt - v) * (_cieUcs[i].vrt - v);
        if (t < min)
        {
            min = t;
            n = i;
        }
    }
    if (n > 0)
    {
        duv = qSqrt(min);
        tc = _cieUcs[n].Tc;
        return;
    }

    min = (_cieUcsP[0].urt - u) * (_cieUcsP[0].urt - u) + (_cieUcsP[0].vrt - v) * (_cieUcsP[0].vrt - v);
    for (i = 1; i < _cieUcsP.size(); i++)
    {
        t = (_cieUcsP[i].urt - u) * (_cieUcsP[i].urt - u) + (_cieUcsP[i].vrt - v) * (_cieUcsP[i].vrt - v);
        if (t < min)
        {
            min = t;
            n = i;
        }
    }
    duv = qSqrt(min);
    tc = _cieUcsP[n].Tc;
}

CIE_UCS HCieUcs::getCieUcs(double tc)
{
    CIE_UCS ucs;
    if (tc < 2300 || tc > 25000)
        return ucs;

    for (int i = 0; i < _cieUcs.size() - 1; i++)
    {
        if (qFabs(tc - _cieUcs[i].Tc) < 1e-6 || (tc > _cieUcs[i].Tc && tc < _cieUcs[i+1].Tc))
            return _cieUcs[i];
    }
    return ucs;
}

void HCieUcs::readStandard()
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

void HCieUcs::readStandardP()
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

HE_ALGORITHM_END_NAMESPACE

