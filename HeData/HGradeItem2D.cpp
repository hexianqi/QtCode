#include "HGradeItem2D_p.h"
#include "HeCore/HCore.h"
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

void HGradeItem2D::setLevels(QVariant value)
{
    Q_D(HGradeItem2D);
    d->levels = value.value<QList<QPolygonF>>();
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
    return QStringList() << "x1" << "y1" << "x2" << "y2" << "x3" << "y3" << "x4" << "y4";
}

QStringList HGradeItem2D::types()
{
    QStringList r;
    auto t = data("[项类型]").toString();
    for (int i = 0; i < 8; i++)
        r << t;
    return r;
}

QVariant HGradeItem2D::levels()
{
    Q_D(HGradeItem2D);
    return QVariant::fromValue(d->levels);
}

QStringList HGradeItem2D::level(int i)
{
    Q_D(HGradeItem2D);
    if (i < 0 || i >= d->levels.size())
        return QStringList() << "" << "" << "" << "" << "" << "" << "" << "";
    QStringList r;
    auto t = data("[项类型]").toString();
    for (int j = 0; j < 4; j++)
    {
        auto p = j < d->levels[i].size() ? d->levels[i][j] : QPointF(0,0);
        r << toString(t, p.x()) << toString(t, p.y());
    }
    return r;
}

HE_DATA_END_NAMESPACE
