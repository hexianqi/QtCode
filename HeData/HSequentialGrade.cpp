#include "HSequentialGrade_p.h"
#include "IDataFactory.h"
#include "IGradeItem.h"
#include <QtCore/QSet>
#include <QtCore/QPoint>
#include <QtCore/QDataStream>

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

void HSequentialGrade::readContent(QDataStream &s, IDataFactory *f)
{
    quint32 version;
    quint32 size;
    QString key, type;

    clear();
    s >> version;
    s >> size;
    for (quint32 i = 0; i < size; i++)
    {
        s >> key >> type;
        auto item = f->createGradeItem(type);
        item->readContent(s);
        if (s.status() != QDataStream::Ok)
        {
            clear();
            break;
        }
        insert(key, item);
    }
}

void HSequentialGrade::writeContent(QDataStream &s)
{
    Q_D(HSequentialGrade);
    s << quint32(1);
    for (auto i = d->datas.constBegin(); i != d->datas.constEnd(); i++)
    {
        s << i.key() << i.value()->typeName();
        i.value()->writeContent(s);
    }
}

HE_DATA_END_NAMESPACE

