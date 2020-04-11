#include "HQuality_p.h"
#include "HQualityItemCollection.h"
#include <QtCore/QDataStream>
#include <QtGui/QColor>

HE_DATA_BEGIN_NAMESPACE

HQualityPrivate::HQualityPrivate()
{
    colors.insert(HQualityReport::InvalidData, Qt::yellow);
    colors.insert(HQualityReport::Broken, Qt::gray);
    colors.insert(HQualityReport::NoPass, Qt::red);
    colors.insert(HQualityReport::Passing, Qt::green);
    damages = new HQualityItemCollection;
    criterions = new HQualityItemCollection;
}

HQuality::HQuality() :
    d_ptr(new HQualityPrivate)
{
}

HQuality::HQuality(HQualityPrivate &p) :
    d_ptr(&p)
{
}

void HQuality::initialize(QVariantMap /*param*/)
{
}

QString HQuality::typeName()
{
    return "HQuality";
}

void HQuality::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    s >> d_ptr->colors;
    d_ptr->damages->readContent(s);
    d_ptr->criterions->readContent(s);
}

void HQuality::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << d_ptr->colors;
    d_ptr->damages->writeContent(s);
    d_ptr->criterions->writeContent(s);
}

IQualityItemCollection *HQuality::itemCollection(HQualityType type)
{
    if (type == Damage)
        return d_ptr->damages;
    if (type == Criterion)
        return d_ptr->criterions;
    return nullptr;
}

void HQuality::setColor(HQualityReport type, QColor color)
{
    d_ptr->colors.insert(type, color);
}

QColor HQuality::color(HQualityReport value)
{
    return d_ptr->colors.value(value, Qt::black);
}

HQualityReport HQuality::check(QVariantMap value, QVariantMap *color)
{
    if (value.isEmpty())
        return HQualityReport::InvalidData;

    auto state = d_ptr->damages->check(value, color);
    if (state < 0)
        return HQualityReport::InvalidData;
    if (state == 0)
        return HQualityReport::Broken;

    state = d_ptr->criterions->check(value, color);
    if (state < 0)
        return HQualityReport::InvalidData;
    if (state == 0)
        return HQualityReport::NoPass;
    return HQualityReport::Passing;
}

double HQuality::drift(QString type, QVariant value)
{
    return d_ptr->criterions->drift(type, value);
}

HE_DATA_END_NAMESPACE

