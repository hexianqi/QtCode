#include "HSpecFitting_p.h"
#include "IDataFactory.h"
#include "ILinearStrategy.h"
#include "HDataHelper.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QDataStream>

HE_BEGIN_NAMESPACE

HSpecFittingPrivate::HSpecFittingPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    strategy = factory->createLinearStrategy("HPolynomStrategy");
    datas["[线性策略]"] = strategy->typeName();
    datas["[线性偏差]"] = 50.0;
    datas["[线性默认值]"] = 1.0;
    datas["[线性多项式项数]"] = 7;
    datas["[光谱拟合取样次数]"] = 100;
    datas["[光谱拟合基准像元]"] = 1000;
    datas["[光谱拟合积分时间范围]"] = QPointF(10, 100);
}

HSpecFitting::HSpecFitting() :
    HAbstractDataItem(*new HSpecFittingPrivate)
{

}

HSpecFitting::HSpecFitting(HSpecFittingPrivate &p) :
    HAbstractDataItem(p)
{
}

QString HSpecFitting::typeName()
{
    return "HSpecFitting";
}

/***************************************************************************************************
**      2023-03-09  版本02 删除ca,cova
***************************************************************************************************/
void HSpecFitting::readContent(QDataStream &s)
{
    quint32 version;
    QVariantMap datas;
    QPolygonF points;
    s >> version;
    s >> datas;
    s >> points;
    if (version == 1)
    {
        QVector<double> ca, cova;
        s >> ca;
        s >> cova;
    }
    setData(datas);
    setPoints(points);
}

void HSpecFitting::writeContent(QDataStream &s)
{
    Q_D(HSpecFitting);
    s << quint32(2);
    s << d->datas;
    s << d->points;
    // 版本02 删除
    // s << d->ca;
    // s << d->cova;
}

/***************************************************************************************************
**      2022-10-07  版本02    增加 [线性多项式项数]
***************************************************************************************************/
QVector<uchar> HSpecFitting::toBinaryData()
{
    Q_D(HSpecFitting);
    auto r =  QVector<uchar>() << HDataHelper::writeUInt16(0)   // 大小
                              << HDataHelper::writeUInt16(2);   // 版本
    r << HDataHelper::writeUInt16(static_cast<quint16>(d->points.size()));
    for (auto p : d->points)
        r << HDataHelper::writeUInt16(static_cast<quint16>(p.x())) << HDataHelper::writeUInt16(static_cast<quint16>(p.y() * 10000));
    r << HDataHelper::writeUInt16(data("[线性多项式项数]").toInt());
    r[0] = uchar(r.size() / 256);
    r[1] = uchar(r.size() % 256);
    return r;
}

bool HSpecFitting::fromBinaryData(QVector<uchar> data, int &pos)
{
    int version = 0;
    if (!HDataHelper::checkHead(data, pos, version))
        return false;

    QPolygonF points;
    auto size = HDataHelper::readUInt16(data, pos);
    for (int i = 0; i < size; i++)
    {
        auto x = HDataHelper::readUInt16(data, pos);
        auto y = HDataHelper::readUInt16(data, pos) / 10000.0;
        points << QPointF(x, y);
    }
    if (version >= 2)
        setData("[线性多项式项数]", HDataHelper::readUInt16(data, pos));
    setPoints(points);
    return true;
}

void HSpecFitting::clear()
{
    Q_D(HSpecFitting);
    d->points.clear();
    d->modified = true;
}

void HSpecFitting::setPoints(QPolygonF value)
{
    Q_D(HSpecFitting);
    d->points = value;
    d->modified = true;
}

QPolygonF HSpecFitting::points()
{
    Q_D(HSpecFitting);
    return d->points;
}

QPolygonF HSpecFitting::curve(double interval)
{
    Q_D(HSpecFitting);
    initStrategy();
    QPolygonF p;
    auto b = d->points.size() < 2 ? 0.0 : d->points.first().x() - 100.0;
    auto e = d->points.size() < 2 ? 65535.0 : d->points.last().x() + 100.0;
    for (double v = b; v < e; v += interval)
        p << QPointF(v, d->strategy->estimate(v));
    return p;
}

QVector<double> HSpecFitting::handle(QVector<double> value, bool abovezero)
{
    initStrategy();
    QVector<double> r;
    for (auto v : value)
        r << handle(v, abovezero);
    return r;
}

void HSpecFitting::initStrategy()
{
    Q_D(HSpecFitting);
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

double HSpecFitting::handle(double value, bool abovezero)
{
    Q_D(HSpecFitting);
    auto rate = d->strategy->estimate(value);
    value = value / rate;
    if (abovezero)
        value = qMax(0.0, value);
    return value;
}

HE_END_NAMESPACE
