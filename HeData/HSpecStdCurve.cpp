#include "HSpecStdCurve_p.h"
#include <QDataStream>

HE_DATA_BEGIN_NAMESPACE

HSpecStdCurve::HSpecStdCurve()
    : d_ptr(new HSpecStdCurvePrivate)
{
}

HSpecStdCurve::HSpecStdCurve(HSpecStdCurvePrivate &p)
    : d_ptr(&p)
{
}

HSpecStdCurve::~HSpecStdCurve()
{
}

void HSpecStdCurve::setData(QVector<double> value)
{
    d_ptr->datas = value;
}

QVector<double> HSpecStdCurve::data()
{
    return d_ptr->datas;
}

QDataStream &operator>>(QDataStream &s, HSpecStdCurve &spec)
{
    quint32 version;
    s >> version;
    s >> spec.d_ptr->datas;
    return s;
}

QDataStream &operator<<(QDataStream &s, const HSpecStdCurve &spec)
{
    s << quint32(1);
    s << spec.d_ptr->datas;
    return s;
}

HE_DATA_END_NAMESPACE
