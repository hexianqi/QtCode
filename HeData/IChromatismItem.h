/***************************************************************************************************
**      2019-05-20  IChromatismItem 色容差数据项接口。
***************************************************************************************************/

#ifndef ICHROMATISMITEM_H
#define ICHROMATISMITEM_H

#include "IDataItem.h"

HE_DATA_BEGIN_NAMESPACE

class IChromatismItem : public IDataItem
{
public:
    // 计算色容差
    virtual double calcSdcm(QPointF xy) = 0;
    // 转成Json
    virtual QJsonObject toJson() = 0;
};

HE_DATA_END_NAMESPACE

#endif // ICHROMATISMITEM_H
