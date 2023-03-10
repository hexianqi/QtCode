/***************************************************************************************************
**      2023-03-09  ILinearStrategy 线性处理接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class ILinearStrategy : public IInitializeable
{
public:
    // 设置数据
    virtual void setData(QPolygonF, QVariantMap param = QVariantMap()) = 0;
    // 估算结果
    virtual double estimate(double) = 0;
};

HE_END_NAMESPACE

