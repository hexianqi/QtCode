/***************************************************************************************************
**      2018-06-19  HSpecStdCurve 光谱标准曲线数据类。
***************************************************************************************************/

#ifndef HSPECSTDCURVE_H
#define HSPECSTDCURVE_H

#include "HAbstractCalibrateItem.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecStdCurvePrivate;

class HSpecStdCurve : public HAbstractCalibrateItem
{
    Q_DECLARE_PRIVATE(HSpecStdCurve)

public:
    explicit HSpecStdCurve();
    ~HSpecStdCurve();

public:
    virtual void restoreDefault() override;

public:
    virtual void readContent(QDataStream &) override;
    virtual void writeContent(QDataStream &) override;

public:
    void setData(QVector<double> value);
    QVector<double> data();

protected:
    HSpecStdCurve(HSpecStdCurvePrivate &p);
};

HE_DATA_END_NAMESPACE

#endif // HSPECSTDCURVE_H
