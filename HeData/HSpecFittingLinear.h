/***************************************************************************************************
**      2019-03-27  HSpecFittingLinear 光谱拟合数据类（线性）。
***************************************************************************************************/

#pragma once

#include "HSpecFitting.h"

HE_BEGIN_NAMESPACE

class HSpecFittingLinearPrivate;

class HSpecFittingLinear : public HSpecFitting
{
    Q_DECLARE_PRIVATE(HSpecFittingLinear)

public:
    explicit HSpecFittingLinear();

public:
    QString typeName() override;

public:
    QVector<uchar> toBinaryData() override;
    bool fromBinaryData(QVector<uchar> data, int &pos) override;

protected:
    HSpecFittingLinear(HSpecFittingLinearPrivate &p);

protected:
    double calcRate(double value) override;
};

HE_END_NAMESPACE
