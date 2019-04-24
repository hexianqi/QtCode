#include "HSequentialGrade_p.h"
#include "IGradeItem.h"
#include <QtCore/QSet>
#include <QtCore/QPoint>

HE_DATA_BEGIN_NAMESPACE

HSequentialGrade::HSequentialGrade() :
    HAbstractGrade(*new HSequentialGradePrivate)
{
}

HSequentialGrade::~HSequentialGrade()
{
}

QString HSequentialGrade::typeName()
{
    return "HSequentialGrade";
}

int HSequentialGrade::calcLevel(QVariantMap value, QString &text)
{
    Q_D(HSequentialGrade);
    text = "";
    if (value.isEmpty() || d->datas.isEmpty())
        return -1;

    QSet<int> set;
    for (auto i = d->datas.constBegin(); i != d->datas.constEnd(); i++)
    {
        if (!value.contains(i.key()))
            return -1;
        auto index = i.value()->indexOf(value.value(i.key()));
        set = set.isEmpty() ? index : set.intersect(index);
        if (set.isEmpty())
            return 0;
    }
    return set.toList().first();
}

HE_DATA_END_NAMESPACE

