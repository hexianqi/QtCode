/***************************************************************************************************
**      2019-03-27  HSpecFitting 光谱拟合数据类。
***************************************************************************************************/

#ifndef HSPECFITTING_H
#define HSPECFITTING_H

#include "HAbstractCalibrateItem.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecFittingPrivate;

class HE_DATA_EXPORT HSpecFitting : public HAbstractCalibrateItem
{
    Q_DECLARE_PRIVATE(HSpecFitting)

public:
    explicit HSpecFitting();
    ~HSpecFitting() override;

public:
    void restoreDefault() override;
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;
    virtual void setFittingPoints(QPolygonF value);

public:
    double handle(double value, bool abovezero = true);
    QVector<double> handle(QVector<double> value, bool abovezero = true);
    QPolygonF fittingPoints();

protected:
    HSpecFitting(HSpecFittingPrivate &p);

protected:
    virtual double calcRate(double value) = 0;
};

HE_DATA_END_NAMESPACE

#endif // HSPECFITTING_H
