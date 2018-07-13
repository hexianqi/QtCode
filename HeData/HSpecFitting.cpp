#include "HSpecFitting_p.h"
#include <QVector>
#include <QPointF>
#include <QtMath>
#include <QDataStream>

HE_DATA_BEGIN_NAMESPACE

HSpecFitting::HSpecFitting()
    : HAbstractCalibrateItem(*new HSpecFittingPrivate)
{
    restoreDefault();
}

HSpecFitting::HSpecFitting(HSpecFittingPrivate &p)
    : HAbstractCalibrateItem(p)
{
    restoreDefault();
}

HSpecFitting::~HSpecFitting()
{
}

void HSpecFitting::restoreDefault()
{
    Q_D(HSpecFitting);
    setData("[光谱拟合范围]", QPointF(0, 65535));
    d->coefficients = QList<double>() << 1.0 << 0.0;
}

void HSpecFitting::readContent(QDataStream &s)
{
    Q_D(HSpecFitting);
    quint32 version;
    s >> version;
    s >> d->datas;
    s >> d->coefficients;
}

void HSpecFitting::writeContent(QDataStream &s)
{
    Q_D(HSpecFitting);
    s << quint32(1);
    s << d->datas;
    s << d->coefficients;
}

double HSpecFitting::handle(double value, bool abovezero)
{
    Q_D(HSpecFitting);
    auto range = data("[光谱拟合范围]").toPointF();
    auto temp = qBound(range.x(), value, range.y());
    auto rate = 0.0;
    for (int i = 0; i < d->coefficients.size(); i++)
        rate += d->coefficients[i] * qPow(temp, i);
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

HE_DATA_END_NAMESPACE
