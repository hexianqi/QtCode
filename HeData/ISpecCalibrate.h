/***************************************************************************************************
**      2018-06-19  ISpecCalibrate 光谱校准接口。
***************************************************************************************************/

#ifndef ISPECCALIBRATE_H
#define ISPECCALIBRATE_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class ISpecCalibrate : public IInitializeable
{
public:
    // 测量参数
    virtual QVariantMap testParam() = 0;

public:
    // 预处理
    virtual QVector<double> preprocess(QVector<double> value, bool fitting = true) = 0;
    // 计算光谱能量
    virtual QPolygonF calcEnergy(QVector<double> value) = 0;
    // 计算光通量
    virtual double calcLuminous(double value) = 0;
    // 计算通讯等待时间
    virtual int calcCommWaitTime(double &value) = 0;
    // 检查帧溢出
    virtual bool checkFrameOverflow(int size) = 0;
    // 检查数据溢出
    virtual int checkEnergyOverflow(double value) = 0;

public:
    virtual void readContent(QDataStream &) = 0;
    virtual void writeContent(QDataStream &) = 0;
};

HE_DATA_END_NAMESPACE

#endif // ISPECCALIBRATE_H
