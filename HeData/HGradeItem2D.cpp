#include "HGradeItem2D_p.h"
#include <QtCore/QDataStream>
#include <QtCore/QSet>
#include <QtGui/QPolygonF>


HE_DATA_BEGIN_NAMESPACE

HGradeItem2D::HGradeItem2D() :
    HAbstractGradeItem(*new HGradeItem2DPrivate)
{
}

HGradeItem2D::~HGradeItem2D()
{
}

void HGradeItem2D::initialize(QVariantMap /*param*/)
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

HE_DATA_END_NAMESPACE
