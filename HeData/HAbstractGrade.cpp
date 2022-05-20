#include "HAbstractGrade_p.h"
#include "IDataFactory.h"
#include "IGradeItem.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"

HE_BEGIN_NAMESPACE

HAbstractGradePrivate::HAbstractGradePrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
}

HAbstractGrade::HAbstractGrade() :
    IGrade(*new HAbstractGradePrivate)
{
}

HAbstractGrade::~HAbstractGrade()
{
}

HAbstractGrade::HAbstractGrade(HAbstractGradePrivate &p) :
    IGrade(p)
{
}

void HAbstractGrade::readContent(QDataStream &s)
{
    Q_D(HAbstractGrade);
    quint32 version;
    s >> version;
    HStreamHelper::read<QString, IGradeItem>(s, d->items, [=](QString type) { return d->factory->createGradeItem(type); });
    if (version >= 2)
        s >> d->datas;
}
// 版本2 增加d->datas
void HAbstractGrade::writeContent(QDataStream &s)
{
    Q_D(HAbstractGrade);
    s << quint32(2);
    HStreamHelper::write<QString, IGradeItem>(s, d->items);
    s << d->datas;
}

void HAbstractGrade::setData(QString name, QVariant value)
{
    Q_D(HAbstractGrade);
    d->datas.insert(name, value);
}

QVariant HAbstractGrade::data(QString name)
{
    Q_D(HAbstractGrade);
    return d->datas.value(name);
}

QVariant HAbstractGrade::levels(QString type)
{
    return contains(type) ? value(type)->levels() : QVariant();
}

HE_END_NAMESPACE
