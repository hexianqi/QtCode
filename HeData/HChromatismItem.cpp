#include "HChromatismItem_p.h"
#include <QtCore/QPointF>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDataStream>
#include <QtCore/QtMath>

HE_DATA_BEGIN_NAMESPACE

HChromatismItemPrivate::HChromatismItemPrivate()
{
    datas.insert("[项类型]", "Undefined");
    datas.insert("[标题]", "");
    datas.insert("[使用]", true);
    datas.insert("[相关色温]", 0.0);
    datas.insert("[标准Sdcm]", 5.0);
    datas.insert("[中心点]", QPointF(0.0, 0.0));
    datas.insert("[参数G]", QVariantList() << 0.0 << 0.0 << 0.0);
    datas.insert("[旋转角]", 0.0);
    datas.insert("[轴A]", 0.0);
    datas.insert("[轴B]", 0.0);
    datas.insert("[测试点]", QPointF(0.0, 0.0));
    datas.insert("[测试Sdcm]", 0.0);
}

HChromatismItem::HChromatismItem() :
    IChromatismItem(*new HChromatismItemPrivate)
{
}

HChromatismItem::HChromatismItem(HChromatismItemPrivate &p) :
    IChromatismItem(p)
{
}

HChromatismItem::~HChromatismItem()
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
}

void HChromatismItem::writeContent(QDataStream &s)
{
    Q_D(HChromatismItem);
    s << quint32(1);
    s << d->datas;
}

double HChromatismItem::calcSdcm(QPointF xy)
{
    QList<double> g;
    for (auto v : data("[参数G]").toList())
        g << v.toDouble();
    auto center = data("[中心点]").toPointF();
    auto x = center.x() - xy.x();
    auto y = center.y() - xy.y();
    auto sdcm = qSqrt(g[0] * x * x + 2 * g[1] * x * y + g[2] * y * y);
    setData("[测试点]", xy);
    setData("[测试Sdcm]", sdcm);
    return sdcm;
}

QJsonObject HChromatismItem::toJson()
{
    QJsonObject json;
    json.insert("title", data("[标题]").toString());
    json.insert("isUse", data("[使用]").toBool());
    json.insert("stdTc", data("[相关色温]").toDouble());
    json.insert("stdSdcm", data("[标准Sdcm]").toDouble());
    json.insert("pointCenterX", data("[中心点]").toPointF().x());
    json.insert("pointCenterY", data("[中心点]").toPointF().y());
    json.insert("stdG", QJsonArray::fromVariantList(data("[参数G]").toList()));
    json.insert("stdTheta", data("[旋转角]").toDouble());
    json.insert("stdA", data("[轴A]").toDouble());
    json.insert("stdB", data("[轴B]").toDouble());
    json.insert("pointFocusX", data("[测试点]").toPointF().x());
    json.insert("pointFocusY", data("[测试点]").toPointF().y());
    json.insert("sdcm", data("[测试Sdcm]").toDouble());
    return json;
}

HE_DATA_END_NAMESPACE
