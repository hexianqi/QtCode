#include "HSpecPelsWave_p.h"
#include "IDataFactory.h"
#include "ILinearStrategy.h"
#include "HDataHelper.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QDataStream>

HE_BEGIN_NAMESPACE

HSpecPelsWavePrivate::HSpecPelsWavePrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    strategy = factory->createLinearStrategy("HPlineStrategy");
    datas["[线性策略]"] = strategy->typeName();
}

HSpecPelsWave::HSpecPelsWave() :
    HAbstractDataItem(*new HSpecPelsWavePrivate)
{
    restoreDefault();
}

HSpecPelsWave::HSpecPelsWave(HSpecPelsWavePrivate &p) :
    HAbstractDataItem(p)
{
}

QString HSpecPelsWave::typeName()
{
    return "HSpecPelsWave";
}

void HSpecPelsWave::readContent(QDataStream &s)
{
    quint32 version;
    QVariantMap datas;
    QPolygonF points;
    s >> version;
    s >> datas;
    s >> points;
    setData(datas);
    setPoints(points);
}

void HSpecPelsWave::writeContent(QDataStream &s)
{
    Q_D(HSpecPelsWave);
    s << quint32(1);
    s << d->datas;
    s << d->points;
}

QVector<uchar> HSpecPelsWave::toBinaryData()
{
    Q_D(HSpecPelsWave);
    auto r =  QVector<uchar>() << HDataHelper::writeUInt16(0)   // 大小
                               << HDataHelper::writeUInt16(1)   // 版本
                               << HDataHelper::writeUInt16(quint16(d->points.size()));
    for (auto p : d->points)
        r << HDataHelper::writeUInt16(quint16(p.x())) << HDataHelper::writeUInt16(quint16(p.y() * 10));
    r[0] = uchar(r.size() / 256);
    r[1] = uchar(r.size() % 256);
    return r;
}

bool HSpecPelsWave::fromBinaryData(const QVector<uchar> &data, int &pos)
{
    int version = 0;
    if (!HDataHelper::checkHead(data, pos, version))
        return false;

    QPolygonF points;
    auto size = HDataHelper::readUInt16(data, pos);
    for (int i = 0; i < size; i++)
    {
        auto x = HDataHelper::readUInt16(data, pos);
        auto y = HDataHelper::readUInt16(data, pos) / 10.0;
        points << QPointF(x, y);
    }
    setPoints(points);
    return true;
}

void HSpecPelsWave::restoreDefault()
{
    setData("[线性多项式项数]", 3);
    setPoints(QPolygonF() << QPointF(460, 404.7)
                          << QPointF(585, 435.8)
                          << QPointF(1030, 546.1)
                          << QPointF(1388, 632.8)
                          << QPointF(1653, 696.5)
                          << QPointF(1878, 750.4)
                          << QPointF(1933, 763.5));
}

void HSpecPelsWave::setPoints(const QPolygonF &value)
{
    Q_D(HSpecPelsWave);
    d->points = value;
    d->modified = true;
    std::sort(d->points.begin(), d->points.end(), [](QPointF p1, QPointF p2) { return p1.x() < p2.x(); });
}

QPolygonF HSpecPelsWave::points()
{
    Q_D(HSpecPelsWave);
    return d->points;
}

double HSpecPelsWave::handle(double value)
{
    Q_D(HSpecPelsWave);
    initStrategy();
    return d->strategy->estimate(value);
}

void HSpecPelsWave::initStrategy()
{
    Q_D(HSpecPelsWave);
    if (!d->modified)
        return;
    auto typeName = d->datas.value("[线性策略]").toString();
    if (d->strategy->typeName() != typeName)
    {
        auto strategy = d->factory->createLinearStrategy(typeName);
        if (strategy == nullptr)
            d->datas["[线性策略]"] = d->strategy->typeName();
        else
            d->strategy = strategy;
    }
    d->strategy->setData(d->points, d->datas);
    d->modified = false;
}

HE_END_NAMESPACE
