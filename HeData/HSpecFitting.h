/***************************************************************************************************
**      2019-03-27  HSpecFitting 光谱拟合数据类。
***************************************************************************************************/

#pragma once

#include "HAbstractDataItem.h"

HE_BEGIN_NAMESPACE

class HSpecFittingPrivate;

class HSpecFitting : public HAbstractDataItem
{
    Q_DECLARE_PRIVATE(HSpecFitting)

public:
    explicit HSpecFitting();

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;
    virtual QVector<uchar> toBinaryData() = 0;
    virtual bool fromBinaryData(QVector<uchar> data, int &pos) = 0;

public:
    virtual void clear();
    virtual void setFittingPoints(QPolygonF value);
    virtual QVector<double> handle(QVector<double> value, bool abovezero = true);
    virtual QPolygonF fittingPoints();
    virtual QPolygonF fittingCurve(double interval);

protected:
    HSpecFitting(HSpecFittingPrivate &p);

protected:
    virtual void init();
    virtual double handle(double value, bool abovezero = true);
    virtual double calcRate(double value);
};

HE_END_NAMESPACE
