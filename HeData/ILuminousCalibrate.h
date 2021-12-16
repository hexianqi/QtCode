/***************************************************************************************************
**      2020-05-22  ILuminousCalibrate 光校准数据接口。
***************************************************************************************************/

#pragma once

#include "HeCore/HCollection.h"

HE_BEGIN_NAMESPACE

class ILuminousCalibrateItem;

class ILuminousCalibrate : public HCollection<ILuminousCalibrateItem>
{
public:
    using HCollection::HCollection;

public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;

public:
    // 设置总档位
    virtual void setTotalGears(int value) = 0;
    // 获取总档位
    virtual int totalGears() = 0;
    // 转化成实际数据
    virtual double toReal(double value, QString type, int index = 0) = 0;
};

HE_END_NAMESPACE

