#include "HLocation_p.h"
#include <QtCore/QDataStream>


HE_BEGIN_NAMESPACE

HLocationPrivate::HLocationPrivate()
{
    datas.insert("[列数]", 0);
    datas.insert("[行数]", 0);
}

HLocation::HLocation() :
    HAbstractDataItem(*new HLocationPrivate)
{
}

HLocation::HLocation(HLocationPrivate &p) :
    HAbstractDataItem(p)
{
}

QString HLocation::typeName()
{
    return "HLocation";
}

void HLocation::readContent(QDataStream &s)
{
    Q_D(HLocation);
    quint32 version;
    s >> version;
    s >> d->datas;
    s >> d->layout;
}

void HLocation::writeContent(QDataStream &s)
{
    Q_D(HLocation);
    s << quint32(1);
    s << d->datas;
    s << d->layout;
}

QRect HLocation::boundingRect()
{
    return polygon().boundingRect();
}

QPolygon HLocation::polygon()
{
    Q_D(HLocation);
    if (d->polygon.isEmpty())
    {
        int i,j;
        auto row = data("[行数]").toInt();
        auto col = data("[列数]").toInt();
        for (i = 0; i < d->layout.size() && i < row; i++)
        {
            for (j = 0; j < d->layout.at(i).size() && j < col; j++)
            {
                if (d->layout.at(i).at(j) > 0)
                    d->polygon << QPoint(i, j);
            }
        }
    }
    return d->polygon;
}

QVector<QVector<int>> HLocation::layout()
{
    Q_D(HLocation);
    return d->layout;
}

void HLocation::setLayout(QVector<QVector<int>> value)
{
    Q_D(HLocation);
    d->layout = value;
}

HE_END_NAMESPACE
