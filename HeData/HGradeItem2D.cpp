#include "HGradeItem2D_p.h"
#include "HeCore/HCore.h"
#include "HeCore/HDataFormatInfo.h"
#include <QtCore/QDataStream>
#include <QtCore/QSet>
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

HGradeItem2DPrivate::HGradeItem2DPrivate()
{
    datas.insert("[项类型]", "Undefined");
    datas.insert("[优先级]", 1);
    datas.insert("[名称]", QStringList());
}

HGradeItem2D::HGradeItem2D() :
    HAbstractDataItem(*new HGradeItem2DPrivate)
{
}

HGradeItem2D::HGradeItem2D(HGradeItem2DPrivate &p) :
    HAbstractDataItem(p)
{
}

QString HGradeItem2D::typeName()
{
    return "HGradeItem2D";
}

void HGradeItem2D::readContent(QDataStream &s)
{
    Q_D(HGradeItem2D);
    quint32 version;
    s >> version;
    s >> d->datas;
    s >> d->levels;
}

void HGradeItem2D::writeContent(QDataStream &s)
{
    Q_D(HGradeItem2D);
    s << quint32(1);
    s << d->datas;
    s << d->levels;
}

void HGradeItem2D::setLevels(QVariant value)
{
    Q_D(HGradeItem2D);
    d->levels = value.value<QList<QPolygonF>>();
}

QVariant HGradeItem2D::levels()
{
    Q_D(HGradeItem2D);
    return QVariant::fromValue(d->levels);
}

QSet<int> HGradeItem2D::indexOf(QVariant value)
{
    Q_D(HGradeItem2D);
    QSet<int> r;
    if (!value.canConvert<QPointF>() || count() == 0)
        return r;
    auto v = value.toPointF();
    for (int i = 0; i < d->levels.size(); i++)
    {
        if (d->levels[i].containsPoint(v, Qt::WindingFill))
            r << i;
    }
    return r;
}

int HGradeItem2D::count()
{
    Q_D(HGradeItem2D);
    return d->levels.size();
}

QStringList HGradeItem2D::headers()
{
    return QStringList() << "x0" << "y0" << "x1" << "y1" << "x2" << "y2" << "x3" << "y3";
}

QStringList HGradeItem2D::types()
{
    QStringList r;
    auto t = data("[项类型]").toString();
    for (int i = 0; i < 8; i++)
        r << t;
    return r;
}

QStringList HGradeItem2D::level(int i)
{
    Q_D(HGradeItem2D);
    if (i >= d->levels.size())
        return QStringList() << "" << "" << "" << "" << "" << "" << "" << "";

    QPolygonF ploy;
    QStringList r;
    auto t = data("[项类型]").toString();
    if (i < 0)
    {
        auto f = HCore::toFormatInfo(t);
        ploy << QPointF(f->min(), f->max()) << QPointF(f->min(), f->min()) << QPointF(f->max(), f->min()) << QPointF(f->max(), f->max());
    }
    else
        ploy = d->levels[i];

    for (int j = 0; j < 4; j++)
    {
        auto p = j < ploy.size() ? ploy[j] : QPointF(0, 0);
        r << HCore::toString(t, p.x()) << HCore::toString(t, p.y());
    }
    return r;
}

HE_END_NAMESPACE
