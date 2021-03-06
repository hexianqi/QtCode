/***************************************************************************************************
**      2018-06-19  ITestSpec 测试光谱数据接口。
***************************************************************************************************/

#ifndef ITESTSPEC_H
#define ITESTSPEC_H

#include "HTestData.h"

HE_DATA_BEGIN_NAMESPACE

class ISpecCalibrate;

class ITestSpec : public HTestData
{
public:
    using HTestData::HTestData;

public:
    // 设置校准数据
    virtual void setCalibrate(ISpecCalibrate *) = 0;
    // 设置积分时间
    virtual void setIntegralTime(double value) = 0;
    // 自动调整积分时间
    virtual bool adjustIntegralTime() = 0;
    // 设置采样数据
    virtual bool setSample(QVector<double> value, bool avg = false) = 0;
    // 设置是否拟合
    virtual void setFitting(bool b) = 0;
    // 清空采样缓存
    virtual void clearCache() = 0;
    // 使用标准数据
    virtual void resetStdCurve() = 0;

public:
    // 光谱采样
    virtual double sample(int type, int pel) = 0;
    // 光谱采样
    virtual QVector<double> sample(int type) = 0;
    // 光谱采样
    virtual QPolygonF samplePoly(int type) = 0;
    // 光谱采样-[a,b]之间最大采样值
    virtual QPointF sampleMax(int type, double a, double b) = 0;
    // 光谱能量
    virtual QPolygonF energy() = 0;

public:
    // 像元转波长
    virtual double pelsToWave(double value) = 0;
    // 设置Ram
    virtual bool setRam(QVector<uchar> value) = 0;
    // 获取Ram
    virtual QVector<uchar> getRam() = 0;
};

HE_DATA_END_NAMESPACE

#endif // ITESTSPECTRUM_H
