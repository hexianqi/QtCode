/***************************************************************************************************
**      2018-06-19  ITestSpec 测试光谱数据接口。
***************************************************************************************************/

#pragma once

#include "HTestData.h"

HE_DATA_BEGIN_NAMESPACE

class ISpecCalibrate;

class ITestSpec : public HTestData
{
public:
    using HTestData::HTestData;

public:
    // 设置采样数据
    virtual bool setSample(QVector<double> value, bool avg = false) = 0;
    // 设置是否拟合
    virtual void setFitting(bool b) = 0;

public:
    // 光谱采样值
    virtual double sample(int type, int pel) = 0;
    // 光谱采样值
    virtual QVector<double> sample(int type) = 0;
    // 光谱采样值
    virtual QPolygonF samplePoly(int type) = 0;
    // 光谱采样值 - [a,b]之间最大采样值
    virtual QPointF sampleMax(int type, double a, double b) = 0;

public:
    // 像元转波长
    virtual double pelsToWave(double value) = 0;
    // 设置Ram
    virtual bool setRam(QVector<uchar> value) = 0;
    // 获取Ram
    virtual QVector<uchar> getRam() = 0;
};

HE_DATA_END_NAMESPACE
