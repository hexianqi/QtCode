/***************************************************************************************************
**      2018-06-19  HSpecFitting 光谱拟合数据类。
***************************************************************************************************/

#ifndef HSPECFITTING_H
#define HSPECFITTING_H

#include "HAbstractCalibrateItem.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecFittingPrivate;

class HSpecFitting : public HAbstractCalibrateItem
{
    Q_DECLARE_PRIVATE(HSpecFitting)

public:
    explicit HSpecFitting();
    ~HSpecFitting();

public:
    virtual void restoreDefault() override;

public:
    virtual void readContent(QDataStream &) override;
    virtual void writeContent(QDataStream &) override;

public:
    double handle(double value, bool abovezero = true);
    QVector<double> handle(QVector<double> value, bool abovezero = true);

protected:
    HSpecFitting(HSpecFittingPrivate &p);
};

HE_DATA_END_NAMESPACE

#endif // HSPECFITTING_H
