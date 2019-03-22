#include "HSpecStdCurve_p.h"
#include <QDataStream>

HE_DATA_BEGIN_NAMESPACE

HSpecStdCurve::HSpecStdCurve()
    : HAbstractCalibrateItem(*new HSpecStdCurvePrivate)
{
}

HSpecStdCurve::HSpecStdCurve(HSpecStdCurvePrivate &p)
    : HAbstractCalibrateItem(p)
{
    restoreDefault();
}

HSpecStdCurve::~HSpecStdCurve()
{
    restoreDefault();
}

void HSpecStdCurve::restoreDefault()
{
    Q_D(HSpecStdCurve);
    d->curve.clear();
}

void HSpecStdCurve::readContent(QDataStream &s)
{
    Q_D(HSpecStdCurve);
    quint32 version;
    s >> version;
    s >> d->datas;
    s >> d->curve;
}

void HSpecStdCurve::writeContent(QDataStream &s)
{
    Q_D(HSpecStdCurve);
    s << quint32(1);
    s << d->datas;
    s << d->curve;
}

void HSpecStdCurve::setCurve(QVector<double> value)
{
    Q_D(HSpecStdCurve);
    d->curve = value;
}

QVector<double> HSpecStdCurve::curve()
{
    Q_D(HSpecStdCurve);
    return d->curve;
}

HE_DATA_END_NAMESPACE
