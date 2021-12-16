#include "HSequentialGrade_p.h"
#include "IGradeItem.h"
#include <QtCore/QSet>
#include <QtCore/QPoint>

HE_BEGIN_NAMESPACE

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
    for (auto i : keys())
    {
        if (!value.contains(i))
            return -1;
        auto index = item(i)->indexOf(value.value(i));
        set = set.isEmpty() ? index : set.intersect(index);
        if (set.isEmpty())
            return 0;
    }
    auto signature = data("[特征码]").toStringList();
    auto r = set.toList().first();
    *text = r < signature.size() ? signature.at(r) : "";
    return r + 1;
}

HE_END_NAMESPACE

