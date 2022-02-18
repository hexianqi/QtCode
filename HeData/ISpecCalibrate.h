/***************************************************************************************************
**      2018-06-19  ISpecCalibrate 光谱校准数据接口。
***************************************************************************************************/

#pragma once

#include "HDataType.h"
#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class IDataItem;
class HSpecFitting;

class ISpecCalibrate : public IInitializeable
{
public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;
    // 转换
    virtual QVector<uchar> toBinaryData() = 0;
    virtual bool fromBinaryData(QVector<uchar> data) = 0;

public:
    // 设置拟合
    virtual void setFitting(HSpecFitting *) = 0;

public:
    // 校准子项
    virtual IDataItem *item(HSpecType type) = 0;
    // 测量参数
    virtual QVariantMap testParam() = 0;

public:
    // 预处理
    virtual QVector<double> preprocess(QVector<double> value, bool fitting = true) = 0;
    // 计算光谱能量
    virtual QPolygonF calcEnergy(QVector<double> value, double offset) = 0;
    // 计算光合数据
    virtual QVariantMap calcSynthetic(QPolygonF energy, double time) = 0;
    // 计算光通量
    virtual double calcLuminous(double value) = 0;
    // 计算通讯等待时间
    virtual int calcCommWaitTime(double &value) = 0;
    // 检查积分时间溢出
    virtual int checkIntegralTime(double value) = 0;
    // 检查帧溢出
    virtual int checkFrameOverflow(int size) = 0;
    // 检查采样溢出
    virtual int checkSampleOverflow(double value) = 0;
    // 像元转波长
    virtual double pelsToWave(double value) = 0;
    // 标准数据
    virtual QVector<double> stdCurve() = 0;
    // 设置标准数据
    virtual void setStdCurve(QVector<double> value) = 0;
};

HE_END_NAMESPACE
