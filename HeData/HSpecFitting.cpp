#include "HSpecFitting_p.h"
#include <QVector>
#include <QPointF>
#include <QtMath>
#include <QDataStream>

HE_DATA_BEGIN_NAMESPACE

HSpecFitting::HSpecFitting()
    : d_ptr(new HSpecFittingPrivate)
{
    restoreDefault();
}

HSpecFitting::HSpecFitting(HSpecFittingPrivate &p)
    : d_ptr(&p)
{
    restoreDefault();
}

HSpecFitting::~HSpecFitting()
{
}

void HSpecFitting::restoreDefault()
{
    setData("[光谱拟合范围]", QPointF(0, 65535));
    d_ptr->coefficients = QList<double>() << 1.0 << 0.0;
}

void HSpecFitting::setData(QString name, QVariant value)
{
    d_ptr->datas.insert(name, value);
}

QVariant HSpecFitting::data(QString name)
{
    return d_ptr->datas.value(name);
}

double HSpecFitting::handle(double value, bool abovezero)
{
    auto range = data("[光谱拟合范围]").toPointF();
    auto temp = qBound(range.x(), value, range.y());
    auto rate = 0.0;
    for (int i = 0; i < d_ptr->coefficients.size(); i++)
        rate += d_ptr->coefficients[i] * qPow(temp, i);
    value = value / rate;
    if (abovezero)
        value = qMax(0.0, value);
    return value;
}

QVector<double> HSpecFitting::handle(QVector<double> value, bool abovezero)
{
    for (int i = 0; i < value.size(); i++)
        value[i] = handle(value[i], abovezero);
    return value;
}

QDataStream &operator>>(QDataStream &s, HSpecFitting &spec)
{
    quint32 version;
    s >> version;
    s >> spec.d_ptr->datas;
    s >> spec.d_ptr->coefficients;
    return s;
}

QDataStream &operator<<(QDataStream &s, const HSpecFitting &spec)
{
    s << quint32(1);
    s << spec.d_ptr->datas;
    s << spec.d_ptr->coefficients;
    return s;
}

HE_DATA_END_NAMESPACE
