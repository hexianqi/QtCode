#include "HSpecFittingPolynom_p.h"
#include "HDataHelper.h"
#include "HeAlgorithm/HMath.h"
#include "HeAlgorithm/HMultiFit.h"
#include <QtCore/QDataStream>

HE_BEGIN_NAMESPACE

HSpecFittingPolynom::HSpecFittingPolynom() :
    HSpecFitting(*new HSpecFittingPolynomPrivate)
{
    init();
}

HSpecFittingPolynom::HSpecFittingPolynom(HSpecFittingPolynomPrivate &p) :
    HSpecFitting(p)
{
}

QString HSpecFittingPolynom::typeName()
{
    return "HSpecFittingPolynom";
}

void HSpecFittingPolynom::readContent(QDataStream &s)
{
    Q_D(HSpecFittingPolynom);
    quint32 version;
    s >> version;
    s >> d->datas;
    s >> d->points;
    s >> d->ca;
    s >> d->cova;
}

void HSpecFittingPolynom::writeContent(QDataStream &s)
{
    Q_D(HSpecFittingPolynom);
    s << quint32(1);
    s << d->datas;
    s << d->points;
    s << d->ca;
    s << d->cova;
}
/***************************************************************************************************
**      2022-10-07  版本02    增加 [光谱拟合多项式项数]
***************************************************************************************************/

QVector<uchar> HSpecFittingPolynom::toBinaryData()
{
    Q_D(HSpecFittingPolynom);
    auto r =  QVector<uchar>() << HDataHelper::writeUInt16(0)   // 大小
                               << HDataHelper::writeUInt16(2);  // 版本
    r << HDataHelper::writeUInt16(static_cast<quint16>(d->points.size()));
    for (auto p : d->points)
        r << HDataHelper::writeUInt16(static_cast<quint16>(p.x())) << HDataHelper::writeUInt16(static_cast<quint16>(p.y() * 10000));
    r << HDataHelper::writeUInt16(data("[光谱拟合多项式项数]").toInt());
    r[0] = uchar(r.size() / 256);
    r[1] = uchar(r.size() % 256);
    return r;
}

bool HSpecFittingPolynom::fromBinaryData(QVector<uchar> data, int &pos)
{
    Q_D(HSpecFittingPolynom);
    int version = 0;
    if (!HDataHelper::checkHead(data, pos, version))
        return false;

    d->points.clear();
    auto size = HDataHelper::readUInt16(data, pos);
    for (int i = 0; i < size; i++)
    {
        auto x = HDataHelper::readUInt16(data, pos);
        auto y = HDataHelper::readUInt16(data, pos) / 10000.0;
        d->points << QPointF(x, y);
    }
    if (version >= 2)
        setData("[光谱拟合多项式项数]", HDataHelper::readUInt16(data, pos));
    setData("[光谱拟合取样次数]", size);
    setData("[光谱拟合有效范围]", QPointF(d->points.first().x(), d->points.last().x()));
    linear();
    return true;
}

void HSpecFittingPolynom::clear()
{
    Q_D(HSpecFittingPolynom);
    d->points.clear();
    d->ca.clear();
    d->cova.clear();
}

void HSpecFittingPolynom::setPoints(QPolygonF value)
{
    HSpecFitting::setPoints(value);
    linear();
}

void HSpecFittingPolynom::init()
{
    Q_D(HSpecFittingPolynom);
    d->ca.clear();
    d->cova.clear();
    setData("[光谱拟合多项式项数]", 7);
    HSpecFitting::init();
}

double HSpecFittingPolynom::calcRate(double value)
{
    auto range = data("[光谱拟合有效范围]").toPointF();
    if (value >= range.x() && value <= range.y())
        return linearEst(value);

    double x1, x2, y1, y2;
    if (value < range.x())
    {
        x1 = range.x();
        x2 = range.x() + 50;
    }
    else
    {
        x1 = range.y() - 50;
        x2 = range.y();
    }

    y1 = linearEst(x1);
    y2 = linearEst(x2);
    return HMath::interpolate(value, x1, y1, x2, y2);
}

void HSpecFittingPolynom::linear()
{
    Q_D(HSpecFittingPolynom);
    double chisq;
    d->ca.clear();
    d->cova.clear();
    d->ca.resize(data("[光谱拟合多项式项数]").toInt());
    HMultiFit::linear(d->points, d->ca, d->cova, &chisq);
}

double HSpecFittingPolynom::linearEst(double value)
{
    Q_D(HSpecFittingPolynom);
    if (d->ca.size() < 2)
        return 1.0;
    double y, error;
    HMultiFit::linear_est(value, d->ca, d->cova, &y, &error);
    return  y;
}

HE_END_NAMESPACE
