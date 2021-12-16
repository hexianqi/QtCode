/***************************************************************************************************
**      2020-05-22  ILuminousCalibrateItem 光校准数据项接口。
***************************************************************************************************/

#pragma once

#include "IDataItem.h"

HE_BEGIN_NAMESPACE

class ILuminousCalibrateItem : public virtual IDataItem
{
public:
    // 设置总档位
    virtual void setTotalGears(int value) = 0;
    // 获取总档位
    virtual int totalGears() = 0;
    // 设置关联数据
    virtual void setRelation(int index, QPolygonF value) = 0;
    // 获取关联数据
    virtual QPolygonF relation(int index) = 0;
    // 转化成实际数据
    virtual double toReal(double value, int index) = 0;
};

HE_END_NAMESPACE
