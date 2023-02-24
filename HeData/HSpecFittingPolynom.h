/***************************************************************************************************
**      2019-03-27  HSpecFittingPolynom 光谱拟合数据类（多项式）。
***************************************************************************************************/

#pragma once

#include "HSpecFitting.h"

HE_BEGIN_NAMESPACE

class HSpecFittingPolynomPrivate;

class HSpecFittingPolynom : public HSpecFitting
{
    Q_DECLARE_PRIVATE(HSpecFittingPolynom)

public:
    explicit HSpecFittingPolynom();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;
    QVector<uchar> toBinaryData() override;
    bool fromBinaryData(QVector<uchar> data, int &pos) override;

public:
    void clear() override;
    void setPoints(QPolygonF value) override;

protected:
    HSpecFittingPolynom(HSpecFittingPolynomPrivate &p);

protected:
    void init() override;
    double calcRate(double value) override;
    void linear();
    double linearEst(double value);
};

HE_END_NAMESPACE
