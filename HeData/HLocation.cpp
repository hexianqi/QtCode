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

QPolygon HLocation::polygon()
{
    Q_D(HLocation);
    bool b = true;
    if (d->polygon.isEmpty())
    {
        int i,j;
        auto row = data("[行数]").toInt();
        auto col = data("[列数]").toInt();
        for (j = col - 1; j >= 0; j--)
        {
            if (b)
            {
                for (i = 0; i < row; i++)
                {
                    if (d->layout.at(i).at(j) > 0)
                        d->polygon << QPoint(i + 1, j + 1);
                }
            }
            else
            {
                for (i = row - 1; i >= 0; i--)
                {
                    if (d->layout.at(i).at(j) > 0)
                        d->polygon << QPoint(i + 1, j + 1);
                }
            }
            if (!d->polygon.isEmpty())
                b = !b;
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
    if (d->layout == value)
        return;
    d->layout = value;
    d->polygon.clear();
}

HE_END_NAMESPACE
