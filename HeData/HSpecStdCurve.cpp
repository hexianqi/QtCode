#include "HSpecStdCurve_p.h"
#include <QtCore/QDataStream>

HE_BEGIN_NAMESPACE

HSpecStdCurve::HSpecStdCurve() :
    HAbstractDataItem(*new HSpecStdCurvePrivate)
{
    restoreDefault();
}

HSpecStdCurve::HSpecStdCurve(HSpecStdCurvePrivate &p) :
    HAbstractDataItem(p)
{
}

QString HSpecStdCurve::typeName()
{
    return "HSpecStdCurve";
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

void HSpecStdCurve::restoreDefault()
{
    Q_D(HSpecStdCurve);
    d->curve.clear();
}

void HSpecStdCurve::setCurve(const QVector<double> &value)
{
    Q_D(HSpecStdCurve);
    d->curve = value;
}

QVector<double> HSpecStdCurve::curve()
{
    Q_D(HSpecStdCurve);
    return d->curve;
}

HE_END_NAMESPACE
