/***************************************************************************************************
**      2019-05-20  IChromatismItem 色容差数据项接口。
***************************************************************************************************/

#pragma once

#include "HAbstractDataItem.h"

HE_DATA_BEGIN_NAMESPACE

class IChromatismItem : public HAbstractDataItem
{
public:
    using HAbstractDataItem::HAbstractDataItem;

public:
    // 计算色容差
    virtual double calcSdcm(QPointF xy) = 0;
};

HE_DATA_END_NAMESPACE
