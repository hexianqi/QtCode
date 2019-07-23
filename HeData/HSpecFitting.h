/***************************************************************************************************
**      2019-03-27  HSpecFitting 光谱拟合数据类。
***************************************************************************************************/

#ifndef HSPECFITTING_H
#define HSPECFITTING_H

#include "HAbstractDataItem.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecFittingPrivate;

class HE_DATA_EXPORT HSpecFitting : public HAbstractDataItem
{
    Q_DECLARE_PRIVATE(HSpecFitting)

public:
    explicit HSpecFitting();
    ~HSpecFitting() override;

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

HE_DATA_END_NAMESPACE

#endif // HSPECFITTING_H
