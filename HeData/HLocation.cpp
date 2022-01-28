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
        auto width = data("[列数]").toInt();
        auto height = data("[行数]").toInt();
        for (int i = 0; i < d->layout.size() && i < width; i++)
        {
            for (int j = 0; j < d->layout.at(i).size() && j < height; j++)
            {
                if (d->layout.at(i).at(j) > 0)
                    d->polygon << QPoint(i, j);
            }
        }
    }
    return d->polygon;
}

HE_END_NAMESPACE
