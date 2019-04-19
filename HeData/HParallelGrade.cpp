#include "HParallelGrade_p.h"
#include "IDataFactory.h"
#include "IGradeItem.h"
#include <QtCore/QSet>
#include <QtCore/QPoint>
#include <QtCore/QDataStream>

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

void HParallelGrade::readContent(QDataStream &s, IDataFactory *f)
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

void HParallelGrade::writeContent(QDataStream &s)
{
    Q_D(HParallelGrade);
    s << quint32(1);
    for (auto i = d->datas.constBegin(); i != d->datas.constEnd(); i++)
    {
        s << i.key() << i.value()->typeName();
        i.value()->writeContent(s);
    }
}

HE_DATA_END_NAMESPACE
