/***************************************************************************************************
**      2019-03-27  HSpecFittingLinear 光谱拟合数据类（线性）。
***************************************************************************************************/

#ifndef HSPECFITTINGLINEAR_H
#define HSPECFITTINGLINEAR_H

#include "HSpecFitting.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecFittingLinearPrivate;

class HSpecFittingLinear : public HSpecFitting
{
    Q_DECLARE_PRIVATE(HSpecFittingLinear)

public:
    explicit HSpecFittingLinear();
    ~HSpecFittingLinear() override;

public:
    QString typeName() override;

protected:
    HSpecFittingLinear(HSpecFittingLinearPrivate &p);

protected:
    double calcRate(double value) override;
};

HE_DATA_END_NAMESPACE

#endif // HSPECFITTINGLINEAR_H
