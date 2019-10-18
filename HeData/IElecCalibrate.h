/***************************************************************************************************
**      2019-10-15  IElecCalibrate 电参数校准数据接口。
***************************************************************************************************/

#ifndef IELECCALIBRATE_H
#define IELECCALIBRATE_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IElecCalibrateItem;
class IElecCalibrateItemCollection;

class IElecCalibrate : public IInitializeable
{
public:
    enum ElecType
    {
        SourceVoltage,
        ReverseVoltage,
        ForwardCurrent,
        ForwardVoltage,
        ReverseCurrent,
        FeedbackCurrent
    };

public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;

public:
    // 设置子项集
    virtual void setItemCollection(ElecType type, IElecCalibrateItemCollection *) = 0;
    // 获取子项集
    virtual IElecCalibrateItemCollection *itemCollection(ElecType type) = 0;
    // 数据子项
    virtual IElecCalibrateItem *item(ElecType type, int index = 0) = 0;
    // 转化成虚拟数据
    virtual double toFiction(double value, ElecType type, int index = 0) = 0;
    // 转化成实际数据
    virtual double toReal(double value, ElecType type, int index = 0) = 0;
    // 转化成字符串
    virtual QString toString(ElecType type) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IELECCALIBRATE_H
