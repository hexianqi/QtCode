#include "HChromatismItem_p.h"
#include <QtCore/QPointF>
#include <QtCore/QDataStream>
#include <QtCore/QtMath>

HE_DATA_BEGIN_NAMESPACE

HChromatismItemPrivate::HChromatismItemPrivate()
{
    // QPointF 无法转化成Json
    datas.insert("[项类型]", "Undefined");
    datas.insert("[标题]", "");
    datas.insert("[使用]", true);
    datas.insert("[相关色温]", 0.0);
    datas.insert("[标准Sdcm]", 5.0);
    datas.insert("[中心点]", QVariantList() << 0.0 << 0.0);
    datas.insert("[参数G]", QVariantList() << 0.0 << 0.0 << 0.0);
    datas.insert("[旋转角]", 0.0);
    datas.insert("[轴A]", 0.0);
    datas.insert("[轴B]", 0.0);
    datas.insert("[测试点]", QVariantList() << 0.0 << 0.0);
    datas.insert("[测试Sdcm]", 0.0);
}

HChromatismItem::HChromatismItem() :
    HAbstractDataItem(*new HChromatismItemPrivate)
{
}

HChromatismItem::HChromatismItem(HChromatismItemPrivate &p) :
    HAbstractDataItem(p)
{
}

QString HChromatismItem::typeName()
{
    return "HChromatismItem";
}

void HChromatismItem::readContent(QDataStream &s)
{
    Q_D(HChromatismItem);
    quint32 version;
    s >> version;
    s >> d->datas;
    if (version == 1)
    {
        auto c = d->datas.value("[中心点]").toPointF();
        auto t = d->datas.value("[测试点]").toPointF();
        d->datas["[中心点]"] = QVariantList() << c.x() << c.y();
        d->datas["[测试点]"] = QVariantList() << t.x() << t.y();
    }
}

// 版本2 QPointF 类型转为 QVariantList
void HChromatismItem::writeContent(QDataStream &s)
{
    Q_D(HChromatismItem);
    s << quint32(2);
    s << d->datas;
}

double HChromatismItem::calcSdcm(QPointF xy)
{
    QList<double> g,c;
    for (const auto &v : data("[参数G]").toList())
        g << v.toDouble();
    for (const auto &v : data("[中心点]").toList())
        c << v.toDouble();
    auto x = c[0] - xy.x();
    auto y = c[1] - xy.y();
    auto sdcm = qSqrt(g[0] * x * x + 2 * g[1] * x * y + g[2] * y * y);
    setData("[测试点]", QVariantList() << xy.x() << xy.y());
    setData("[测试Sdcm]", sdcm);
    return sdcm;
}

HE_DATA_END_NAMESPACE
