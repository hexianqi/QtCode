#include "HParallelGrade_p.h"
#include "IGradeItem.h"
#include <QtCore/QSet>
#include <QtCore/QPoint>

HE_DATA_BEGIN_NAMESPACE

HParallelGrade::HParallelGrade() :
    HAbstractGrade(*new HParallelGradePrivate)
{
}

QString HParallelGrade::typeName()
{
    return "HParallelGrade";
}

int HParallelGrade::calcLevel(QVariantMap value, QString *text)
{
    Q_D(HParallelGrade);
    if (value.isEmpty() || isEmpty())
        return -1;

    QMap<int, QPoint> map;
    for (auto i = d->items.begin(); i != d->items.end(); i++)
    {
        if (!value.contains(i.key()))
            return -1;
        auto index = i.value()->indexOf(value.value(i.key()));
        if (index.isEmpty())
            return 0;
        auto priority = i.value()->data("[优先级]").toInt() * 100;
        while (map.contains(priority))
            priority++;
        map.insert(priority, QPoint(index.toList().first(), i.value()->count()));
    }
    int j = 0;
    int sum = 0;
    QStringList list;
    for (auto p : map)
    {
        sum = p.x() + p.y() * sum;
        list << QString("%1%2").arg(QChar('A' + j)).arg(p.x());
        j++;
    }
    *text = list.join("");
    return sum + 1;
}

HE_DATA_END_NAMESPACE
