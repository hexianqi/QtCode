/***************************************************************************************************
**      2018-06-19  HSpecStdCurve 光谱标准曲线数据类。
***************************************************************************************************/

#ifndef HSPECSTDCURVE_H
#define HSPECSTDCURVE_H

#include "HAbstractCalibrateItem.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecStdCurvePrivate;

class HE_DATA_EXPORT HSpecStdCurve : public HAbstractCalibrateItem
{
    Q_DECLARE_PRIVATE(HSpecStdCurve)

public:
    explicit HSpecStdCurve();
    ~HSpecStdCurve() override;

public:
    QString typeName() override;
    void restoreDefault() override;
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void setCurve(QVector<double> value);
    QVector<double> curve();

protected:
    HSpecStdCurve(HSpecStdCurvePrivate &p);
};

HE_DATA_END_NAMESPACE

#endif // HSPECSTDCURVE_H
