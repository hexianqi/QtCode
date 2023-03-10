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
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    virtual QVector<uchar> toBinaryData();
    virtual bool fromBinaryData(QVector<uchar> data, int &pos);

public:
    virtual void clear();
    virtual void setPoints(QPolygonF value);
    virtual QPolygonF points();
    virtual QPolygonF curve(double interval);
    virtual QVector<double> handle(QVector<double> value, bool abovezero = true);

protected:
    HSpecFitting(HSpecFittingPrivate &p);

protected:
    virtual void initStrategy();
    virtual double handle(double value, bool abovezero = true);
};

HE_END_NAMESPACE
