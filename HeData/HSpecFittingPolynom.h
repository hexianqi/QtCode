/***************************************************************************************************
**      2019-03-27  HSpecFittingPolynom 光谱拟合数据类（多项式）。
***************************************************************************************************/

#ifndef HSPECFITTINGPOLYNOM_H
#define HSPECFITTINGPOLYNOM_H

#include "HSpecFitting.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecFittingPolynomPrivate;

class HSpecFittingPolynom : public HSpecFitting
{
    Q_DECLARE_PRIVATE(HSpecFittingPolynom)

public:
    explicit HSpecFittingPolynom();
    ~HSpecFittingPolynom() override;

public:
    QString typeName() override;
    void restoreDefault() override;
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

protected:
    HSpecFittingPolynom(HSpecFittingPolynomPrivate &p);

protected:
    double calcRate(double value) override;
    double calcPolynom(double value);
};

HE_DATA_END_NAMESPACE

#endif // HSPECFITTINGPOLYNOM_H
