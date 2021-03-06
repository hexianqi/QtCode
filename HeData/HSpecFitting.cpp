#include "HSpecFitting_p.h"
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HSpecFitting::HSpecFitting() :
    HAbstractDataItem(*new HSpecFittingPrivate)
{
    init();
}

HSpecFitting::HSpecFitting(HSpecFittingPrivate &p) :
    HAbstractDataItem(p)
{
}

HSpecFitting::~HSpecFitting()
{
}

void HSpecFitting::readContent(QDataStream &s)
{
    Q_D(HSpecFitting);
    quint32 version;
    s >> version;
    s >> d->datas;
    s >> d->fittingPoints;
}

void HSpecFitting::writeContent(QDataStream &s)
{
    Q_D(HSpecFitting);
    s << quint32(1);
    s << d->datas;
    s << d->fittingPoints;
}

QVector<uchar> HSpecFitting::toBinaryData()
{
    return QVector<uchar>();
}

bool HSpecFitting::fromBinaryData(QVector<uchar> /*data*/, int &/*pos*/)
{
    return true;
}

void HSpecFitting::clear()
{
    Q_D(HSpecFitting);
    d->fittingPoints.clear();
}

void HSpecFitting::setFittingPoints(QPolygonF value)
{
    Q_D(HSpecFitting);
    setData("[光谱拟合取样次数]", value.size());
    setData("[光谱拟合积分时间范围]", QPointF(value.first().y(), value.last().y()));
    setData("[光谱拟合有效范围]", QPointF(value.first().x(), value.last().x()));

    int i;
    double t = 0.0;
    QVector<double> y;

    for (i = 0; i < value.size(); i++)
    {
        y << value[i].x() / value[i].y();
        t = qMax(t, y[i]);
    }
    for (i = 0; i < value.size(); i++)
        value[i].setY(y[i] / t);
    d->fittingPoints = value;
}

double HSpecFitting::handle(double value, bool abovezero)
{
    auto rate = calcRate(value);
    value = value / rate;
    if (abovezero)
        value = qMax(0.0, value);
    return value;
}

QPolygonF HSpecFitting::fittingPoints()
{
    Q_D(HSpecFitting);
    return d->fittingPoints;
}

void HSpecFitting::init()
{
    Q_D(HSpecFitting);
    setData("[光谱拟合基准像元]", 1000);
    setData("[光谱拟合取样次数]", 100);
    setData("[光谱拟合积分时间范围]", QPointF(10, 100));
    setData("[光谱拟合有效范围]", QPointF(0, 65535));
    d->fittingPoints.clear();
}

double HSpecFitting::calcRate(double /*value*/)
{
    return 1.0;
}

QVector<double> HSpecFitting::handle(QVector<double> value, bool abovezero)
{
    QVector<double> r;
    for (auto v : value)
        r << handle(v, abovezero);
    return r;
}

HE_DATA_END_NAMESPACE
