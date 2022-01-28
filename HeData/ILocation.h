/***************************************************************************************************
**      2022-01-26  ILocation 定位数据接口。
***************************************************************************************************/


#pragma once

#include "IDataItem.h"

HE_BEGIN_NAMESPACE

class ILocation : public virtual IDataItem
{
public:
    // 边框
    virtual QRect boundingRect() = 0;
    // 形状
    virtual QPolygon polygon() = 0;
};

HE_END_NAMESPACE
