/***************************************************************************************************
**      2023-03-09  HPolynomStrategy
***************************************************************************************************/

#pragma once

#include "HAbstractLinearStrategy.h"

HE_BEGIN_NAMESPACE

class HPolynomStrategyPrivate;

class HPolynomStrategy : public HAbstractLinearStrategy
{
    Q_DECLARE_PRIVATE(HPolynomStrategy)

public:
    explicit HPolynomStrategy();

public:
    QString typeName() override;

public:
    void setData(QPolygonF, QVariantMap param = QVariantMap()) override;
    double estimate(double) override;

protected:
    void linear();
    double linearEst(double);

protected:
    HPolynomStrategy(HPolynomStrategyPrivate &);
};

HE_END_NAMESPACE

