#include "HSequentialGrade_p.h"
#include "IGradeItem.h"
#include <QtCore/QSet>
#include <QtCore/QPoint>

HE_DATA_BEGIN_NAMESPACE

HSequentialGrade::HSequentialGrade() :
    HAbstractGrade(*new HSequentialGradePrivate)
{
}

QString HSequentialGrade::typeName()
{
    return "HSequentialGrade";
}

int HSequentialGrade::calcLevel(QVariantMap value, QString *text)
{
    Q_UNUSED(text);
    if (value.isEmpty() || isEmpty())
        return -1;

    QSet<int> set;
    for (const auto &i : keys())
    {
        if (!value.contains(i))
            return -1;
        auto index = item(i)->indexOf(value.value(i));
        set = set.isEmpty() ? index : set.intersect(index);
        if (set.isEmpty())
            return 0;
    }
    return set.toList().at(0);
}

HE_DATA_END_NAMESPACE

