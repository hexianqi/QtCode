/***************************************************************************************************
**      2018-06-19  标准的CIE数据格式及计算。
**                  HCieTc32    14种彩色测试样品的光谱反射数据。
**                  HCie1931    CIE1931数据计算类。
**                  HCieDay     CIE日光色数据计算类。
**                  HCieUcs     CIE_UCS数据计算类。
**                  HIsotherm   等温线数据计算类。
***************************************************************************************************/

#ifndef HCIE1931_H
#define HCIE1931_H

#include "HAlgorithmGlobal.h"
#include <QPolygonF>
#include <memory>

HE_ALGORITHM_BEGIN_NAMESPACE

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

struct CIE_DAY
{
    double wave;
    double S[3];
};

struct CIE_TC_32
{
    double wave;
    double S[14];
};

struct ISOTHERM
{
    double Tc;
    double u;
    double v;
    double slope;
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
    double Ur[14];
    double Vr[14];
    double Wr[14];
};

struct CIE_UCS_P
{
    double Tc;
    double urt;
    double vrt;
};

class HCieTc32
{
public:
    HCieTc32();

public:
    int size() { return _stdData.size(); }
    CIE_TC_32 data(int i);

protected:
    void readStandard();

protected:
    QVector<CIE_TC_32> _stdData;
};

class HCie1931
{
public:
    HCie1931();

public:
    // 计算色坐标
    QPointF calcCoordinateUv(QPolygonF spd);
    // 计算Duv
    double calcDuv(QPointF uv, double tc);
    // 计算主波长，色纯度
    void calcDominantWave(QPointF xy, double &wave, double &purity);
    // 计算14种颜色样品的光谱反射数据
    void calcColorReflectance(QPolygonF spd, QVector<double> &ui, QVector<double> &vi, QVector<double> &Yi);
    // 计算黑体轨迹色坐标
    QPointF calcIsoCoordinateUv(double tc);
    QPointF calcIsoCoordinateXy(double tc);
    //计算等温线
    ISOTHERM calcIsotherm(double tc);
    //计算等温线(拟合方式)
    ISOTHERM calcIsothermFit(double tc);

protected:
    void readStandard();

protected:
    QVector<CIE1931> _stdData;
    std::shared_ptr<HCieTc32> _cieTc32;
};

class HCieDay
{
public:
    HCieDay();

public:
    //计算参考源光谱能量
    double calcRefSourceSpectrum(double tc, double wave);
    QPolygonF calcRefSourceSpectrum(double tc, QPointF wave, double interval = 1.0);

protected:
    void readStandard();

protected:
    QVector<CIE_DAY> _stdData;
};

class HIsotherm
{
public:
    HIsotherm();

public:
    // 计算色温
    double calcColorTemperature(QPointF uv);                                                                                    //计算色温
    double calcColorTemperature(double u, double v);

protected:
    void readStandard();
    double calcDistance(int i, double u, double v);

protected:
    QVector<ISOTHERM> _stdData;
};

class HCieUcs
{
public:
    HCieUcs();

public:
    // 计算色温
    void calcColorTemperature(QPointF uv, double &tc, double &duv);
    // 获取CIE_UCS
    CIE_UCS getCieUcs(double tc);

protected:
    void readStandard();
    void readStandardP();

protected:
    QVector<CIE_UCS> _cieUcs;
    QVector<CIE_UCS_P> _cieUcsP;
};

HE_ALGORITHM_END_NAMESPACE

#endif // HCIE1931_H
