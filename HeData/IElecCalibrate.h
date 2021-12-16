/***************************************************************************************************
**      2019-10-15  IElecCalibrate 电参数校准数据接口。
***************************************************************************************************/

#pragma once

#include "HDataType.h"
#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class IElecCalibrateItem;
class IElecCalibrateItemCollection;

class IElecCalibrate : public IInitializeable
{
public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;

public:
    // 设置子项集
    virtual void setItemCollection(HElecType type, IElecCalibrateItemCollection *) = 0;
    // 获取子项集
    virtual IElecCalibrateItemCollection *itemCollection(HElecType type) = 0;
    // 数据子项
    virtual IElecCalibrateItem *item(HElecType type, int index = 0) = 0;
    // 转化成虚拟数据
    virtual double toFiction(double value, HElecType type, int index = 0) = 0;
    // 转化成实际数据
    virtual double toReal(double value, HElecType type, int index = 0) = 0;
    // 转化成字符串
    virtual QString toString(HElecType type) = 0;
};

HE_END_NAMESPACE
