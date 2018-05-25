#ifndef HSPECSTDCURVE_H
#define HSPECSTDCURVE_H

#include "HDataGlobal.h"
#include <QScopedPointer>

HE_DATA_BEGIN_NAMESPACE

class HSpecStdCurvePrivate;

class HSpecStdCurve
{
public:
    explicit HSpecStdCurve();
    ~HSpecStdCurve();

public:
    void setData(QVector<double> value);
    QVector<double> data();

protected:
    HSpecStdCurve(HSpecStdCurvePrivate &p);

protected:
    QScopedPointer<HSpecStdCurvePrivate> d_ptr;

private:
    friend QDataStream &operator<<(QDataStream &, const HSpecStdCurve &);
    friend QDataStream &operator>>(QDataStream &, HSpecStdCurve &);
};

HE_DATA_END_NAMESPACE

#endif // HSPECSTDCURVE_H
