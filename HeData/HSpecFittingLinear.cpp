#include "HSpecFittingLinear_p.h"
#include "HDataHelper.h"
#include "HeAlgorithm/HInterp.h"
#include "HeAlgorithm/HMath.h"
#include <QtCore/QDataStream>

HE_BEGIN_NAMESPACE

HSpecFittingLinear::HSpecFittingLinear() :
    HSpecFitting(*new HSpecFittingLinearPrivate)
{
    init();
}

HSpecFittingLinear::HSpecFittingLinear(HSpecFittingLinearPrivate &p) :
    HSpecFitting(p)
{
}

QString HSpecFittingLinear::typeName()
{
    return "HSpecFittingLinear";
}

void HSpecFittingLinear::readContent(QDataStream &s)
{
    Q_D(HSpecFittingLinear);
    quint32 version;
    s >> version;
    s >> d->datas;
    s >> d->points;
}

void HSpecFittingLinear::writeContent(QDataStream &s)
{
    Q_D(HSpecFittingLinear);
    s << quint32(1);
    s << d->datas;
    s << d->points;
}

QVector<uchar> HSpecFittingLinear::toBinaryData()
{
    Q_D(HSpecFittingLinear);
    auto r =  QVector<uchar>() << HDataHelper::writeUInt16(0)  // 大小
                               << HDataHelper::writeUInt16(1)  // 版本
                               << HDataHelper::writeUInt16(static_cast<quint16>(d->points.size()));
    for (auto p : d->points)
        r << HDataHelper::writeUInt16(quint16(p.x())) << HDataHelper::writeUInt16(quint16(p.y() * 10000));
    r[0] = uchar((r.size() / 256));
    r[1] = uchar((r.size() % 256));
    return r;
}

bool HSpecFittingLinear::fromBinaryData(QVector<uchar> data, int &pos)
{
    Q_D(HSpecFittingLinear);
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
    setData("[光谱拟合取样次数]", size);
    setData("[光谱拟合有效范围]", QPointF(d->points.first().x(), d->points.last().x()));
    return true;
}

double HSpecFittingLinear::calcRate(double value)
{
    Q_D(HSpecFittingLinear);
    if (d->points.size() < 3)
        return 1.0;

//    auto range = data("[光谱拟合有效范围]").toPointF();
//    value = qBound(range.x(), value, range.y());
    return HMath::interpolate(value, d->points);
//    return HInterp::eval(d->fittingPoints, value, HInterpType::Cspline);
}

HE_END_NAMESPACE
