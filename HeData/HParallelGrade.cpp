#include "HParallelGrade_p.h"
#include "IGradeItem.h"
#include <QtCore/QSet>
#include <QtCore/QPoint>

HE_DATA_BEGIN_NAMESPACE

HParallelGrade::HParallelGrade() :
    HAbstractGrade(*new HParallelGradePrivate)
{
}

HParallelGrade::~HParallelGrade()
{
}

QString HParallelGrade::typeName()
{
    return "HParallelGrade";
}

int HParallelGrade::calcLevel(QVariantMap value, QString &text)
{
    Q_D(HParallelGrade);
    text = "";
    if (value.isEmpty() || d->datas.isEmpty())
        return -1;

    QMap<int, QPoint> map;
    for (auto i = d->datas.constBegin(); i != d->datas.constEnd(); i++)
    {
        if (!value.contains(i.key()))
            return -1;
        auto index = i.value()->indexOf(value.value(i.key()));
        if (index.size() == 0)
            return 0;
        auto priority = i.value()->data("[优先级]").toInt();
        if (map.contains(priority))
            priority++;
        map.insert(priority, QPoint(index.toList().first(), i.value()->count()));
    }
    int j = 0;
    int sum = 0;
    for (auto p : map)
    {
        sum = p.x() + p.y() * sum;
        text += QString("%1%2").arg(QChar('A' + j)).arg(p.x());
        j++;
    }
    return sum + 1;
}

HE_DATA_END_NAMESPACE
