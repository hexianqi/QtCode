/***************************************************************************************************
**      2023-03-09  HAbstractLinearStrategy
***************************************************************************************************/

#pragma once

#include "ILinearStrategy.h"

HE_BEGIN_NAMESPACE

class HAbstractLinearStrategyPrivate;

class HAbstractLinearStrategy : public ILinearStrategy
{
public:
    explicit HAbstractLinearStrategy();
    ~HAbstractLinearStrategy();

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    void setData(QPolygonF, QVariantMap param = QVariantMap()) override;

protected:
    HAbstractLinearStrategy(HAbstractLinearStrategyPrivate &);

protected:
    QScopedPointer<HAbstractLinearStrategyPrivate> d_ptr;
};

HE_END_NAMESPACE

