/***************************************************************************************************
**      2019-10-16  IElecCalibrateItem 电参数校准子项接口。
***************************************************************************************************/

#pragma once

#include "IDataItem.h"

HE_DATA_BEGIN_NAMESPACE

class IElecCalibrateItem : public virtual IDataItem
{
public:
    // 还原默认
    virtual void restoreDefault() = 0;
    // 设置关联数据
    virtual void setRelation(QPolygonF value) = 0;
    // 获取关联数据
    virtual QPolygonF relation() = 0;
    // 转化成虚拟数据
    virtual double toFiction(double value) = 0;
    // 转化成实际数据
    virtual double toReal(double value) = 0;
};

HE_DATA_END_NAMESPACE
