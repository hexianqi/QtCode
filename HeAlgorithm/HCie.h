/***************************************************************************************************
**      2018-06-19  标准的CIE数据格式及计算。
**                  CIE1931         CIE1931数据。
**                  CIE_DAYLIGHT    CIE日光色数据。
**                  CIE_TC_32       14种彩色测试样品的光谱反射数据。
**                  CIE_UCS         CIE_UCS数据。
**                  ISOTHERM        等温线数据。
**                  HCie1931        CIE1931数据计算类。
**                  HCieDaylight    CIE日光色数据计算类。
**                  HCieUcs         CIE_UCS数据计算类。
**                  HIsotherm       等温线数据计算类。
***************************************************************************************************/

#pragma once

#include "HAlgorithmGlobal.h"
#include <QtGui/QPolygonF>
#include <memory>

HE_ALGORITHM_BEGIN_NAMESPACE

// CMF(color matching function) = 2
struct CIE1931
{
    double wave;
    double X;
    double Y;
    double Z;
    double x;
    double y;
    double z;
    double slope;
};

struct CIE_DAYLIGHT
{
    double wave;
    double S[3];
};

struct CIE_TC_32
{
    double wave;
    double S[15];
};

struct CIE_UCS
{
    double Tc;
    double urt;
    double vrt;
    double xt;
    double yt;
    double ur;
    double vr;
    double cr;
    double dr;
    double Ur[15];
    double Vr[15];
    double Wr[15];
};

struct CIE_UCS_P
{
    double Tc;
    double urt;
    double vrt;
};

struct ISOTHERM
{
    double Tc;
    double u;
    double v;
    double slope;
};

class HCie1931
{
public:
    HCie1931();

public:
    // 计算色坐标
    QPointF calcCoordinateUV(const QPolygonF &spd);
    // 计算Duv
    double calcDuv(QPointF uv, double tc);
    // 计算主波长，色纯度
    QList<double> calcWaveDominantPurity(QPointF xy);
    // 计算15种颜色样品的光谱反射数据
    QList<QVector<double>> calcColorReflectance(QPolygonF spd);
    // 计算黑体轨迹色坐标
    QPointF calcIsoCoordinateUV(double tc);
    QPointF calcIsoCoordinateXY(double tc);
    // 计算等温线
    ISOTHERM calcIsotherm(double tc);
    // 计算等温线(拟合方式)
    ISOTHERM calcIsothermFit(double tc);
    // 标准化(Y = 100)
    QPolygonF normalizedY100(const QPolygonF &spd);

protected:
    void read1931();
    void readTc32();

protected:
    QVector<CIE1931> _cie1931;
    QVector<CIE_TC_32> _cieTc32;
};

class Q_DECL_EXPORT HCieDaylight
{
public:
    HCieDaylight();

public:
    // 计算参考源光谱能量
    QPolygonF calcRefSourceSpectrum(double tc, QPointF wave = QPointF(380, 780), double interval = 1.0);

protected:
    void read();
    double calcRefSpectrum(double tc, double wave);
    double calcRefSpectrumP(double tc, double wave);
    double calcRefSpectrumD(double tc, double wave);
    double calcRefSpectrumM(double tc, double wave);

protected:
    QVector<CIE_DAYLIGHT> _data;
};

class HCieUcs
{
public:
    HCieUcs();

public:
    // 计算色温Duv
    QList<double> calcColorTemperatureDuv(QPointF uv);
    // 获取CIE_UCS
    CIE_UCS findCieUcs(double tc);

protected:
    void read();
    void readP();

protected:
    QVector<CIE_UCS> _cieUcs;
    QVector<CIE_UCS_P> _cieUcsP;
};

class HIsotherm
{
public:
    HIsotherm();

public:
    // 计算色温
    double calcColorTemperature(QPointF uv);
    double calcColorTemperature(double u, double v);

protected:
    void read();
    double calcDistance(int i, double u, double v);

protected:
    QVector<ISOTHERM> _data;
};

HE_ALGORITHM_END_NAMESPACE
