/***************************************************************************************************
**      2022-01-26  ILocation 布局数据接口。
***************************************************************************************************/


#pragma once

#include "IDataItem.h"

HE_BEGIN_NAMESPACE

class ILocation : public virtual IDataItem
{
public:
    // 形状
    virtual QPolygon polygon() = 0;
    // 布局
    virtual QVector<QVector<int>> layout() = 0;
    virtual void setLayout(QVector<QVector<int>>) = 0;
};

HE_END_NAMESPACE
